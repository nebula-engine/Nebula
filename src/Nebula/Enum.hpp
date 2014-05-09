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

namespace Neb {
	namespace Enum {
		template <typename enum_type> struct Maps {
			std::map<std::string,enum_type>		map_string_enum_;
			std::map<enum_type,std::string>		map_enum_string_;
			
			std::string		toString(enum_type val) {
				auto it = map_enum_string_.find(val);
				if(it == map_enum_string_.cend()) throw 0;
				return it->second;
			}
			enum_type		toEnum(std::string str) {
				auto it = map_string_enum_.find(str);
				if(it == map_string_enum_.cend()) throw 0;
				return it->second;
			}

		};	
		template <typename enum_type> struct MapsFlag: Neb::Enum::Maps<enum_type> {
			std::vector<std::string>	toStringVec(enum_type val) {
				enum_type e = 0;
				std::vector<std::string> vec;
				for(int b = 0; b < (sizeof(enum_type) * 8); ++b) {
					e = 1 << b;
					if(e & val) {
						vec.push_back(toString(e));
					}
				}
				return vec;
			}
			enum_type			toEnum(std::vector<std::string> vec) {
				enum_type e = 0;
				for(auto it = vec.cbegin(); it != vec.cend(); ++it) {
					e |= toEnum(*it);
				}
				return e;
			}
		};
	}
}



#define DEFINE_TYPE(name, values)\
	struct name {\
		public:\
			enum E: short {\
				BOOST_PP_SEQ_FOR_EACH(DEFINE_ENUM_VALUE, , values)\
			};\
			name(): val_((E)0) {}\
			name(E e): val_(e) {}\
			\
															\
			void				save(boost::archive::xml_oarchive & ar, unsigned int const & version) {		\
				std::string str = maps_.maps_.toString(val_);						\
				ar << boost::serialization::make_nvp("value",str);					\
			}												\
			void				load(boost::archive::xml_iarchive & ar, unsigned int const & version) {		\
				std::string str;									\
				ar >> boost::serialization::make_nvp("value",str);					\
				val_ = (E)maps_.maps_.toEnum(str);								\
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
					Neb::Enum::Maps<short> maps_;\
				};\
				static Maps maps_;\
			public:\
			       E	val_;\
	};\





#define DEFINE_FLAG(name, values)\
	struct name {\
		public:\
			enum E: unsigned long {\
				BOOST_PP_SEQ_FOR_EACH(DEFINE_ENUM_VALUE, , values)\
			};\
			name(): val_((E)0) {}\
			name(E e): val_(e) {}\
			\
			void		set(flag_type fl)	{ val_ |= fl} }\
			void		unset(flag_type fl)	{ val_ &= !fl; }\
			void		toggle(flag_type fl)	{ val_ ^= fl; }\
			bool		all(flag_type fl)	{ return ( ( val_ & fl ) == fl ); }\
			bool		any(flag_type fl)	{ return ( val_ & fl ); }\
			flag_type	mask(flag_type fl)	{ return ( val_ & fl ); }\
			\
			\
			void				save(boost::archive::xml_oarchive & ar, unsigned int const & version) {\
				std::vector<std::string> vec = maps_.maps_.toStringVec(val_);\
				ar << boost::serialization::make_nvp("value",vec);\
			}\
			void				load(boost::archive::xml_iarchive & ar, unsigned int const & version) {		\
				std::vector<std::string> vec;\
				ar >> boost::serialization::make_nvp("value",vec);\
				val_ = maps_.maps_.toEnum(vec);\
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
					Neb::Enum::MapsFlag<unsigned long> maps_;\
				};\
				static Maps maps_;\
			public:\
			       E	val_;\
	};\







#define DEFINE_TYPE_STATICS(name)\
	name::Maps name::maps_;

#define DEFINE_ENUM_VALUE(r, data, elem)\
	BOOST_PP_SEQ_HEAD(elem) = BOOST_PP_SEQ_TAIL(elem) BOOST_PP_COMMA()

#define DEFINE_MAP_STRING_ENUM_VALUE(r, data, elem)\
	maps_.map_string_enum_[BOOST_PP_STRINGIZE(BOOST_PP_SEQ_HEAD(elem))] = (E)BOOST_PP_SEQ_TAIL(elem);

#define DEFINE_MAP_ENUM_STRING_VALUE(r, data, elem)\
	maps_.map_enum_string_[(E)BOOST_PP_SEQ_TAIL(elem)] = BOOST_PP_STRINGIZE(BOOST_PP_SEQ_HEAD(elem));





#endif












