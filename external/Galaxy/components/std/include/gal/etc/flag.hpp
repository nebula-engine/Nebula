#ifndef GALAXY_STD_FLAG_HPP
#define GALAXY_STD_FLAG_HPP

#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/seq.hpp>

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

#include <boost/serialization/vector.hpp>

#include <map>

namespace gal {
	namespace etc {
		template <typename enum_type> struct enum_map {
			std::map< std::string, enum_type >		map_string_enum_;
			std::map< enum_type, std::string >		map_enum_string_;

			std::string		toString(enum_type val)
			{
				auto it = map_enum_string_.find(val);
				if(it == map_enum_string_.cend()) throw 0;
				return it->second;
			}
			enum_type		toEnum(::std::string str)
			{
				auto it = map_string_enum_.find(str);
				if(it == map_string_enum_.cend()) throw 0;
				return it->second;
			}

			::std::vector< ::std::string >		toStringVec(enum_type val) {
				enum_type e = 0;
				::std::vector< ::std::string > vec;
				for(size_t b = 0; b < (sizeof(enum_type) * 8); ++b) {
					e = 1 << b;
					if(e & val) {
						vec.push_back(toString(e));
					}
				}
				return vec;
			}
			enum_type				toEnum(::std::vector< ::std::string > vec) {
				enum_type e = 0;
				for(auto it = vec.cbegin(); it != vec.cend(); ++it) {
					e |= toEnum(*it);
				}
				return e;
			}
		};
	}
}



#define DEFINE_FLAG(name, values)\
	struct name {\
		public:\
			typedef unsigned int		flag_type;\
			enum E: flag_type\
			{\
				BOOST_PP_SEQ_FOR_EACH(DEFINE_ENUM_VALUE, , values)\
			};\
			name(): val_((E)0) {}\
			name(E e): val_(e) {}\
			name(unsigned int e): val_((E)e) {}\
			\
			void		set(flag_type fl)	{ val_ = (E)(val_ | fl); }\
			void		unset(flag_type fl)	{ val_ = (E)(val_ & ~fl); }\
			void		toggle(flag_type fl)	{ val_ = (E)(val_ ^ fl); }\
			bool		all(flag_type fl)	{ return ( ( val_ & fl ) == fl ); }\
			bool		any(flag_type fl)	{ return bool( val_ & fl ); }\
			flag_type	mask(flag_type fl)	{ return bool( val_ & fl ); }\
			operator flag_type()			{ return (flag_type)val_; }\
			\
			void		save(boost::archive::xml_oarchive & ar, unsigned int const & version) {\
				std::vector< ::std::string > vec = maps_.maps_.toStringVec(val_);\
				ar << boost::serialization::make_nvp("value",vec);\
			}\
			void				load(boost::archive::xml_iarchive & ar, unsigned int const & version) {\
				::std::vector< ::std::string > vec;\
				ar >> boost::serialization::make_nvp("value",vec);\
				val_ = (E)maps_.maps_.toEnum(vec);\
			}\
			template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {\
				ar & boost::serialization::make_nvp("value",val_);\
			}\
		private:\
			struct Maps {\
				Maps() {\
					BOOST_PP_SEQ_FOR_EACH(DEFINE_MAP_STRING_ENUM_VALUE, , values)\
					BOOST_PP_SEQ_FOR_EACH(DEFINE_MAP_ENUM_STRING_VALUE, , values)\
				}\
				gal::etc::enum_map<flag_type>		maps_;\
			};\
			static Maps	maps_;\
		public:\
			E		val_;\
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












