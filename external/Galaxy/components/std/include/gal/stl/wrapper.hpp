#ifndef NEBULA_UTIL_WRAPPERTYPED_HH
#define NEBULA_UTIL_WRAPPERTYPED_HH

#include <map>
#include <exception>

//#include <boost/function.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

//#include <Nebula/App/BaseFactory.hh>

#include <gal/itf/shared.hpp>
#include <gal/stl/factory.hpp>
#include <gal/dll/helper.hpp>

namespace ba = boost::archive;

namespace gal {
	namespace stl {
		/** @brief wrapper
		 * class T must be derived from and registered with gal::std::Typed or exceptions will be thrown
		 */

		struct InvalidVersion
		{
			InvalidVersion(unsigned int const & nversion): version(nversion) {}
			virtual const char *	what()
			{
				char* buffer = new char[50];
				sprintf(buffer, "invalid version %i", version);
				return buffer;
			}
			unsigned int	version;
		};
		struct HashCode
		{
			HashCode(): hc(0) {}
			HashCode(gal::itf::hash_type nhc): hc(nhc) {}

			template<class Archive> void	load(Archive & ar, unsigned int const & version)
			{
				if(version == 0)
				{
					std::string name;

					ar >> boost::serialization::make_nvp("name", name);

					hc = gal::itf::shared::to_hash_code(name);
				}
				else if(version == 1)
				{
					ar >> hc;
				}
				else throw InvalidVersion(version);
			}
			template<class Archive> void	save(Archive & ar, unsigned int const & version) const
			{
				if(version == 0)
				{
					std::string name = gal::itf::shared::to_string(hc);

					ar << boost::serialization::make_nvp("name", name);
				}
				else if(version == 1)
				{
					ar << hc;
				}
				else throw InvalidVersion(version);
			}
			void		load(
					ba::xml_iarchive & ar,
					unsigned int const & version)
			{
				std::string name;

				ar >> boost::serialization::make_nvp("name", name);

				hc = gal::itf::shared::to_hash_code(name);
			}
			void		save(
					ba::xml_oarchive & ar,
					unsigned int const & version) const
			{
				std::string name = gal::itf::shared::to_string(hc);

				ar << boost::serialization::make_nvp("name", name);
			}
			void		load(
					ba::binary_iarchive & ar,
					unsigned int const & version)
			{
				ar >> hc;
			}
			void		save(
					ba::binary_oarchive & ar,
					unsigned int const & version) const
			{
				ar << hc;
			}

			BOOST_SERIALIZATION_SPLIT_MEMBER();

			gal::itf::hash_type	hc;
		};

		struct wrapper_load_type
		{
			enum e
			{
				STATIC,
				DYNAMIC
			};
		};

		template<typename T> class wrapper {
			public:
				struct nullptrException: std::exception
			{
				virtual const char *	what()
				{
					return "null ptr";
				}
			};

				typedef std::weak_ptr< factory<T> >			factory_weak;
				typedef std::shared_ptr<T>				shared;
				/** */
				wrapper(): 
					factory_(factory<T>::default_factory_)
			{
				std::cout << "wrapper default ctor" << std::endl;
				assert(!factory_.expired());
			}
				/** */
				wrapper(shared ptr):
					ptr_(ptr),
					factory_(factory<T>::default_factory_)
			{
				std::cout << "wrapper ctor 1" << std::endl;
				assert(ptr_);
			}

				wrapper(wrapper<T> const & w):
					ptr_(w.ptr_),
					factory_(w.factory_)
			{
				std::cout << "wrapper copy ctor" << std::endl;
				assert(ptr_);
			}

				wrapper(wrapper<T>&& w):
					ptr_(std::move(w.ptr_)),
					factory_(std::move(w.factory_))
			{
				std::cout << "wrapper move ctor" << std::endl;
				assert(ptr_);
			}
			public:
				/** @brief Destructor */
				virtual ~wrapper()
				{
					std::cout << __PRETTY_FUNCTION__ << std::endl;
				}
				/** @brief %Load */
				template<class Archive> void		save(Archive & ar, unsigned int const & version) const
				{
					if(!ptr_) throw nullptrException();

					// determine if created statically or by dll
					auto del = std::get_deleter<gal::dll::deleter>(ptr_);

					std::cout << "del = " << del << std::endl;

					int load_type;
					if(del)
					{
						std::cout << "dynamic" << std::endl;

						load_type = 1;					
						ar << BOOST_SERIALIZATION_NVP(load_type);

						auto hi = del->getHelperInfo();

						ar << boost::serialization::make_nvp("helper", hi);
					}
					else
					{
						std::cout << "static" << std::endl;

						load_type = 0;
						ar << BOOST_SERIALIZATION_NVP(load_type);

						HashCode hc(ptr_->hash_code());
						ar << boost::serialization::make_nvp("hashcode", hc);
					}


					ar << boost::serialization::make_nvp("object", *ptr_);
				}
				template<class Archive> void		load(Archive & ar, unsigned int const & version)
				{
					int load_type;
					ar >> BOOST_SERIALIZATION_NVP(load_type);

					if(load_type == 1) // dll
					{
						gal::dll::helper_info hi;
						ar >> boost::serialization::make_nvp("helper", hi);

						// get the factory
						auto fs = factory_.lock();
						assert(fs);

						// allocate the object
						ptr_ = fs->template alloc<gal::dll::helper_info&>(hi.hc, hi);
					}
					else
					{

						HashCode hc;
						ar >> boost::serialization::make_nvp("hashcode", hc);

						// get the factory
						auto fs = factory_.lock();
						assert(fs);

						// allocate the object
						ptr_ = fs->template alloc<>(hc.hc);
					}
					// read objcet data
					ar >> boost::serialization::make_nvp("object", *ptr_);
				}

				/** */
				BOOST_SERIALIZATION_SPLIT_MEMBER();
				static gal::itf::index_type const &			static_get_index(gal::stl::wrapper<T> const & wrap) {
					if(wrap.ptr_->_M_index == -1) {
						std::cout << "warning: gal::itf::shared object is uninitialized" << ::std::endl;
						throw 0;
					}
					return wrap.ptr_->i_;
				}

			public:
				/** @brief Pointer */
				shared				ptr_;
				factory_weak			factory_;
			private:
		};


	}
}

#endif



