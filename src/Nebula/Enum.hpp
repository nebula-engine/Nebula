#ifndef NEBULA_ENUM_HPP
#define NEBULA_ENUM_HPP

#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/seq.hpp>

#include <map>

/*
namespace gru {
	template<typename enum_type> class Enum {

	static std::map<enum_type, std::string>	map_int_string;
	static std::map<std::string, enum_type>	map_string_int;

	static enum_type		Convert(std::string str) {
	auto it = map_string_int.find(str);
	if(it == map_string_int.cend()) throw 0;
	return it->second;
	}
	static std::string		Convert(enum_type i) {
	auto it = map_int_string.find(i);
	if(it == map_int_string.cend()) throw 0;
	return it->second;
	}

	};
	}
	*/

#define DEFINE_ENUM(name, type, values)					\
	struct name {								\
		public:							\
									enum E: type {							\
										BOOST_PP_SEQ_FOR_EACH(DEFINE_ENUM_VALUE, , values)	\
									};								\
		name(): val_((E)0) {}										\
		name(E e): val_(e) {}										\
		static std::string to_string(E val) {								\
			switch (val) {										\
				BOOST_PP_SEQ_FOR_EACH(DEFINE_ENUM_FORMAT, , values)				\
				default:									\
														return 0;	\
			}											\
		}												\
		static E	to_type(std::string str) {							\
			auto it = map_.find(str);								\
			if(it == map_.cend()) throw 0;							\
			return it->second;							\
		}												\
		void		save(boost::archive::xml_oarchive & ar, unsigned int const & version) {		\
			std::string str = to_string(val_);						\
			ar << boost::serialization::make_nvp("value",str);					\
		}												\
		void		load(boost::archive::xml_iarchive & ar, unsigned int const & version) {		\
			std::string str;									\
			ar >> boost::serialization::make_nvp("value",str);					\
			val_ = to_type(str);								\
		}												\
		template<class Archive> void serialize(Archive & ar, unsigned int const & version) {		\
			ar & boost::serialization::make_nvp("value",val_);					\
		}												\
		private:											\
														static std::map<std::string,E>	map_;								\
		public:												\
														E	val_;											\
	};													\

#define DEFINE_ENUM_VALUE(r, data, elem)				\
	BOOST_PP_SEQ_HEAD(elem)						\
BOOST_PP_IIF(BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(elem), 2),      \
		= BOOST_PP_SEQ_TAIL(elem), )                     \
BOOST_PP_COMMA()

#define DEFINE_ENUM_FORMAT(r, data, elem)             \
	case BOOST_PP_SEQ_HEAD(elem):                       \
		return BOOST_PP_STRINGIZE(BOOST_PP_SEQ_HEAD(elem));




#endif












