#ifndef NEBULA_ENUM_HPP
#define NEBULA_ENUM_HPP

#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/seq.hpp>

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

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


#define DEFINE_TYPE(name, values)\
	struct name {\
		public:\
			enum E: short {\
				BOOST_PP_SEQ_FOR_EACH(DEFINE_ENUM_VALUE, , values)\
			};\
			name(): val_((E)0) {}\
			name(E e): val_(e) {}\
			\
			static std::string		toString(E val) {\
				auto it = maps_.map_enum_string_.find(val);\
				if(it == maps_.map_enum_string_.cend()) throw 0;\
				return it->second;\
			}\
			static E			toEnum(std::string str) {\
				auto it = maps_.map_string_enum_.find(str);\
				if(it == maps_.map_string_enum_.cend()) throw 0;\
				return it->second;\
			}												\
			void				save(boost::archive::xml_oarchive & ar, unsigned int const & version) {		\
				std::string str = toString(val_);						\
				ar << boost::serialization::make_nvp("value",str);					\
			}												\
			void				load(boost::archive::xml_iarchive & ar, unsigned int const & version) {		\
				std::string str;									\
				ar >> boost::serialization::make_nvp("value",str);					\
				val_ = toEnum(str);								\
			}												\
			template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {		\
				ar & boost::serialization::make_nvp("value",val_);					\
			}												\
			private:\
				struct Maps {\
					Maps() {\
						BOOST_PP_SEQ_FOR_EACH(DEFINE_MAP_STRING_ENUM_VALUE, , values)\
						BOOST_PP_SEQ_FOR_EACH(DEFINE_MAP_ENUM_STRING_VALUE, , values)\
					}\
					std::map<std::string,E>		map_string_enum_;\
					std::map<E,std::string>		map_enum_string_;\
				};\
				static Maps maps_;\
			public:\
			       E	val_;\
	};\

#define DEFINE_TYPE_STATICS(name) name::Maps name::maps_;

#define DEFINE_ENUM_VALUE(r, data, elem)\
	BOOST_PP_SEQ_HEAD(elem) = BOOST_PP_SEQ_TAIL(elem) BOOST_PP_COMMA()

#define DEFINE_MAP_STRING_ENUM_VALUE(r, data, elem)\
	map_string_enum_[BOOST_PP_STRINGIZE(BOOST_PP_SEQ_HEAD(elem))] = (E)BOOST_PP_SEQ_TAIL(elem);

#define DEFINE_MAP_ENUM_STRING_VALUE(r, data, elem)\
	map_enum_string_[(E)BOOST_PP_SEQ_TAIL(elem)] = BOOST_PP_STRINGIZE(BOOST_PP_SEQ_HEAD(elem));


#define DEFINE_ENUM_FORMAT(r, data, elem)             \
		case BOOST_PP_SEQ_HEAD(elem):                       \
			return BOOST_PP_STRINGIZE(BOOST_PP_SEQ_HEAD(elem));




#endif












