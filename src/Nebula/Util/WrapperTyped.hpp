#ifndef NEBULA_TYPED_HPP
#define NEBULA_TYPED_HPP

#include <map>

#include <boost/function.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/nvp.hpp>

#include <Nebula/Memory/smart_ptr.hpp>

namespace Neb {
	/** @brief WrapperTyped
	 * class T must be derived from and registered with Neb::Util::Typed or exceptions will be thrown
	 */
	template<class T> class WrapperTyped {
		public:
			/** @brief Constructor */
			WrapperTyped(std::weak_ptr< Neb::Factory<T> > factory): factory_(factory) {}
			/** @brief Destructor */
			virtual ~WrapperTyped() {}
			/** @brief Serialize */
			
			template<class Archive> void		load(Archive & ar, unsigned int const & version) {
				// get the code
				long int hash_code;
				ar >> boost::serialization::make_nvp("hash_code", hash_code);
				
				// get the factory
				auto fs = factory_.lock();
				assert(fs);

				// allocate the object
				ptr_.reset((T*)fs->alloc(hash_code));

				// read objcet data
				ar >> boost::serialization::make_nvp("object", *ptr_);
			}
			template<class Archive> void		save(Archive & ar, unsigned int const & version) const {
				ar << boost::serialization::make_nvp("hash_code", ptr_->hash_code());
				ar << boost::serialization::make_nvp("object", *ptr_);
			}
			void		load(boost::archive::xml_iarchive & ar, unsigned int const & version) {
				// get the code
				std::string name;
				ar >> boost::serialization::make_nvp("name", name);
				Neb::Typed::hash_type hash = Neb::Typed::to_hash_code(name);
				
				// get the factory
				auto fs = factory_.lock();
				assert(fs);

				// allocate the object
				ptr_.reset((T*)fs->alloc(hash));

				// read objcet data
				ar >> boost::serialization::make_nvp("object", *ptr_);
			}
			void		save(boost::archive::xml_oarchive & ar, unsigned int const & version) const {
				std::string name = Neb::Typed::to_string(ptr_->hash_code());
				ar << boost::serialization::make_nvp("name", name);
				ar << boost::serialization::make_nvp("object", *ptr_);
			}
			
			
			
			BOOST_SERIALIZATION_SPLIT_MEMBER();
		public:
			/** @brief Object */
			std::shared_ptr< T >				ptr_;
			std::weak_ptr< Neb::Factory<T> >		factory_;
	};
}

#endif



