#ifndef NEBULA_TYPED_HPP
#define NEBULA_TYPED_HPP

#include <map>

#include <boost/function.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/nvp.hpp>

#include <Nebula/Memory/smart_ptr.hpp>

namespace Neb {
	/** @brief Typed */
	class Typed {
		public:
			/** @brief Destructor */
			virtual ~Typed() {}
			/** @brief Hash Code */
			long int &		hash_code() { return hash_code_; }
		private:
			/** @brief Hash Code */
			static long int		hash_code_;
	};
	/** @brief Factory
	 * the app shall hold instances of Factory for the various types and use cases
	 */
	template<class T> class Factory {
		private:
			struct __base_function {
	                        virtual ~__base_function() {}
	                };
	                template<class... A> struct __function: __base_function {
	                        __function(function<T*(A...)> f): f_(f) {}
	                        function<T*(A...)>              f_;
	                };
		public:

			Factory() {}
			virtual ~Factory() = 0;
			
			template<class... Args> void	add(hash_code, std::function<T*(Args...)> f) {
				std::shared_ptr<__base_function> b(new __function<Args...>(f));
				
				map_.emplace(hash_code, b)
			}
			
			template<class... Args> T*      alloc(long hash_code, Args&&... args) {
	                        auto it = map_.find(hash_code);
	                        if(it == map_.cend()) {
	                                cout << "no alloc for " << hash_code << endl;
	                                return 0;
	                        } else {
	                                std::shared_ptr< __function<Args...> > f = std::dynamic_pointer_cast< __function<Args...> >(it->second);
	
	                                if(f == NULL) {
	                                        cout << "wrong arg list" << endl;
	                                        return 0;
	                                }
	
	                                return (f->f_)(forward<Args>(args)...);
	                        }
	                }

			static std::shared_ptr< Factory<T> >		global() {
				if(!global_) {
					throw 0;
				}
				return global_;
			};
		private:
			//static std::shared_ptr< Factory<T> >		global_;
			std::map<long int, __base_function*>         	map_;

	};
	/** @brief WrapperTyped */
	template<class T> class WrapperTyped {
		public:
			/** @brief Destructor */
			virtual ~WrapperTyped() {}
			/** @brief Serialize */
			template<class Archive> void		load(Archive & ar, unsigned int const & version) {
				long int hash_code;
				ar >> boost::serialization::make_nvp("hash_code", hash_code);
				ptr_.reset((T*)Neb::Factory<T>::global()->alloc(hash_code));
				ar >> boost::serialization::make_nvp("object", *ptr_);
			}
			template<class Archive> void		save(Archive & ar, unsigned int const & version) const {
				ar << boost::serialization::make_nvp("hash_code", ptr_->hash_code());
				ar << boost::serialization::make_nvp("object", *ptr_);
			}
			BOOST_SERIALIZATION_SPLIT_MEMBER();
		public:
			/** @brief Object */
			Neb::unique_ptr<T>			ptr_;
	};
}

#endif



