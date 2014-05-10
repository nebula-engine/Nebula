#ifndef NEBULA_UTIL_FACTORY_HPP
#define NEBULA_UTIL_FACTORY_HPP

namespace Neb {
	/** @brief Factory
	 * the app shall hold instances of Factory for the various types and use cases
	 */
	template<class T> class Factory {
		private:
			struct invalid_key: std::exception {
				char *	what() {
					return "invalid key";
				}
			};
			struct invalid_args: std::exception {
				char *	what() {
					return "invalid args";
				}
			};

			struct __base_function {
	                        virtual ~__base_function() {}
	                };
	                template<class... A> struct __function: __base_function {
	                        __function(std::function<T*(A...)> f): f_(f) {}
				std::function<T*(A...)>              f_;
	                };
		public:
			Factory() {}
			virtual ~Factory() = 0;
			
			template<class... Args> void	add(long int hash_code, std::function<T*(Args...)> f) {
				std::shared_ptr<__base_function> b(new __function<Args...>(f));
				
				map_.emplace(hash_code, b);
			}
			
			template<class... Args> T*      alloc(long hash_code, Args&&... args) {
	                        auto it = map_.find(hash_code);
	                        if(it == map_.cend()) {
					throw invalid_key();
	                        } else {
	                                std::shared_ptr< __function<Args...> > f = std::dynamic_pointer_cast< __function<Args...> >(it->second);
	
	                                if(f == NULL) {
						throw invalid_args();
	                                }
	
	                                return (f->f_)(std::forward<Args>(args)...);
	                        }
	                }

		private:
			std::map< long int, std::shared_ptr<__base_function> >         	map_;

	};
}
	
#endif
