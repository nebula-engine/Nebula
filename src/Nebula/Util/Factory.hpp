#ifndef NEBULA_UTIL_FACTORY_HPP
#define NEBULA_UTIL_FACTORY_HPP

namespace Neb {
	/** @brief FuncMap
	 * A map containing @c std::function objects with arbitrary signatures
	 * Motivation: See Factory and Initializer classes
	 */
	class FuncMap {
		private:
			/** */
			struct invalid_key: std::exception {
				char *	what() {
					return "invalid key";
				}
			};
			/** */
			struct invalid_args: std::exception {
				char *	what() {
					return "invalid args";
				}
			};
			/** */
			struct __base_function {
	                        virtual ~__base_function() {}
	                };
	                /** */
	                template<class R, class... A>
	                struct __function: __base_function {
	                	/** */
	                        __function(std::function<R(A...)> f): f_(f) {}
	                        /** */
				std::function<R(A...)>		f_;
	                };
		public:
			Factory() {}
			virtual ~Factory() = 0;
			/** */
			template<class R, class... Args>
			void		add(long int hash_code, std::function<R(Args...)> f) {
				std::shared_ptr<__base_function> b(new __function<R, Args...>(f));
				
				map_.emplace(hash_code, b);
			}
			/** */
			template<class R, class... Args>
			std::shared_ptr< __function<R, Args...> >		find(long hash_code) {
				auto it = map_.find(hash_code);
				
	                        if(it == map_.cend()) throw invalid_key();
	                        
	                        std::shared_ptr< __function<R, Args...> > f = std::dynamic_pointer_cast< __function<R, Args...> >(it->second);
				
				if(!f) throw invalid_args();
				
	                        return f;
			}
		private:
			std::map< long int, std::shared_ptr<__base_function> >         	map_;

	};
	/** @brief Factory.
	 * Store and use allocator functions
	 * 
	 * @par Motivation:
	 * create an object who type is unknown but identified by a has_code.
	 * 
	 * @note the app shall hold instances of Factory for the various types and use cases
	 */
	template <class T>
	class Factory: public FuncMap {
		public:
			/** */
			template<class... Args>
			T*      					alloc(long hash_code, Args&&... args) {
	                        auto f = find<T*, Args...>(hash_code);
	                        
	                        return (f->f_)(std::forward<Args>(args)...);
	                }
	};
	/** @brief Initializer.
	 * Store and use initializer functions.
	 * Allocate an object with arbitrary alloc function stored in the FuncMap
	 * and call the object's @c init method with arbitrary arguments
	 * 
	 * @par Motivation:
	 * create an object guaranteeing virtual initialization
	 * 
	 * @warning @c T must have an @c init member with arguments passed to @c alloc
	 * which must be accessible from @c Initializer
	 * 
	 */
	template <class T>
	class Initializer: public FuncMap {
		public:
			typedef std::shared_ptr<T> shared;
			/** */
			template<class... AllocArgs, class... InitArgs>
			shared			alloc(
					long hash_code,
					std::tuple<AllocArgs...>&& allocargs,
					std::tuple<InitArgs...>&& initargs) {
				callAlloc(
						hash_code,
						allocargs,
						initargs,
						typename gens<sizeof...(AllocArgs)>::type(),
						typename gens<sizeof...(InitArgs)>::type());
			}
			template<class... AllocArgs, class... InitArgs, int... SA, int... SB>
			shared			callAlloc(
					long hash_code,
					std::tuple<AllocArgs...>&& allocargs,
					std::tuple<InitArgs...>&& initargs,
					seq<SA...>,
					seq<SB...>) {
				
	                        auto f = find<shared,AllocArgs...>(hash_code);
	                        
	                        shared s = (f->f_)(get<SA>(allocargs)...);
	                        
	                        // call (possibly) virtual initialization method
				s->init(get<SB>(initargs)...);
				
				return s;
	                }
	                
	                
	};
}

#endif
