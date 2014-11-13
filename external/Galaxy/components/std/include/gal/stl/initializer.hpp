#ifndef NEBULA_UTIL_FACTORY_HPP
#define NEBULA_UTIL_FACTORY_HPP

#include <map>
#include <memory>

#include <Galaxy-Standard/decl.hpp>
#include <Galaxy-Standard/helper.hpp>
#include <Galaxy-Standard/typedef.hpp>

namespace sp = std;

namespace gal {
	namespace stl {

		/** @brief FuncMap
		 *
		 * A map containing @c ::std::function objects with arbitrary signatures
		 * Motivation: See factory and Initializer classes
		 */
		class FuncMap {
			private:
				typedef std::shared_ptr<gal::itf::shared>				shared_type;
				/** */
				struct __base_function {
					virtual ~__base_function() {}
				};
				/** */
				template<class... A> struct __function: __base_function {
					/** */
					__function(::std::function< shared_type(A...) > f): f_(f) {}
					/** */
					::std::function< shared_type(A...) >		f_;
				};
				typedef ::std::map< long int, ::std::shared_ptr<__base_function> >	map_type;
				/** */
				struct invalid_key: ::std::exception {
					char const *	what() {
						return "invalid key";
					}
				};
				/** */
				struct invalid_args: ::std::exception {
					char const *	what() {
						return "invalid args";
					}
				};

			public:
				FuncMap() {}
				virtual ~FuncMap() {}
				/** */
				template<class... Args> void											add(
						gal::itf::hash_type hash_code,
						::std::function< shared_type(Args...)> f)
				{
					::std::shared_ptr<__base_function> b(new __function< Args...>(f));

					//map_.emplace(hash_code, b);
					map_[hash_code] = b;
				}
				/** */
				template<class... Args> std::shared_ptr< __function< Args... > >		find(
						gal::itf::hash_type hash_code)
				{
					auto it = map_.find(hash_code);

					if(it == map_.cend()) throw invalid_key();

					//::std::shared_ptr< __function<return_type, Args...> >
					auto f = ::std::dynamic_pointer_cast< __function< Args... > >(it->second);

					if(!f) throw invalid_args();

					return f;
				}
			private:
				map_type         	map_;

		};
		/** @brief factory.
		 *
		 * Store and use allocator functions
		 * 
		 * @par Motivation:
		 * create an object who type is unknown but identified by a has_code.
		 * 
		 * @note the app shall hold instances of factory for the various types and use cases
		 */
		class factory: public FuncMap {
			public:
				/** */
				template<class... Args> std::shared_ptr<gal::itf::shared>		alloc(gal::itf::hash_type hash_code, Args&&... args) {
					auto f = find<Args...>(hash_code);

					return (f->f_)(::std::forward<Args>(args)...);
				}

			public:
				static std::shared_ptr<factory>					default_factory_;
		};
		/** @brief Initializer
		 *
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
		template <class T> class Initializer: public FuncMap {
			public:
				typedef ::std::shared_ptr<T> shared;
				/** */
				template<class... AllocArgs, class... InitArgs> shared						alloc(
						long hash_code,
						::std::tuple<AllocArgs...>&& allocargs,
						::std::tuple<InitArgs...>&& initargs) {
					// callAlloc
					callAlloc(
							hash_code,
							allocargs,
							initargs,
							typename gens<sizeof...(AllocArgs)>::type(),
							typename gens<sizeof...(InitArgs)>::type());
				}
				template<class... AllocArgs, class... InitArgs, int... SA, int... SB> shared			callAlloc(
						long hash_code,
						::std::tuple<AllocArgs...>&& allocargs,
						::std::tuple<InitArgs...>&& initargs,
						seq<SA...>,
						seq<SB...>) {

					auto f = find<shared,AllocArgs...>(hash_code);

					shared s = (f->f_)(::std::get<SA>(allocargs)...);

					// call (possibly) virtual initialization method
					s->init(::std::get<SB>(initargs)...);

					return s;
				}
		};
	}
}

#endif





