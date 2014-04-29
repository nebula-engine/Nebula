#ifndef NEBULA_FILTER_HPP
#define NEBULA_FILTER_HPP

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

namespace gru {
	namespace Filter {
		struct Filter {
			enum Type: unsigned int {
				NONE			= 0,
				STATIC			= 1 << 0,
				DYNAMIC			= 1 << 1,
				PROJECTILE		= 1 << 2,
				UNDRIVABLE_SURFACE	= 1 << 3,
			};

			static unsigned int const RIGID_AGAINST		= Type::STATIC | Type::DYNAMIC;
			static unsigned int const DRIVABLE_SURFACE	= Type::STATIC | Type::DYNAMIC;
			static unsigned int const PROJECTILE_AGAINST	= Type::STATIC | Type::DYNAMIC;

			static unsigned int const COLLISION_FLAG_WHEEL			= 0;
			static unsigned int const COLLISION_FLAG_WHEEL_AGAINST		= 0;
			static unsigned int const COLLISION_FLAG_CHASSIS		= Type::DYNAMIC;
			static unsigned int const COLLISION_FLAG_CHASSIS_AGAINST	= RIGID_AGAINST;

			static std::map<unsigned int, std::string>	map_int_string;
			static std::map<std::string, unsigned int>	map_string_int;

			static unsigned int		Convert(std::string str) {
				auto it = map_string_int.find(str);
				if(it == map_string_int.cend()) throw 0;
				return it->second;
			}
			static std::string		Convert(unsigned int i) {
				auto it = map_int_string.find(i);
				if(it == map_int_string.cend()) throw 0;
				return it->second;
			}
		};

		class Word {
			public:
				void		save(boost::archive::xml_oarchive & ar, unsigned int const & version) {
					std::string str = Filter::Convert(word);
					ar << boost::serialization::make_nvp("word",word);
				}
				void		load(boost::archive::xml_iarchive & ar, unsigned int const & version) {
					std::string str;
					ar >> boost::serialization::make_nvp("word",word);
					word = Filter::Convert(str);
				}
				template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {

				}


				unsigned int word;
		};
		class Data {
			public:
				template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("word0",word0);
					ar & boost::serialization::make_nvp("word1",word1);
					ar & boost::serialization::make_nvp("word2",word2);
					ar & boost::serialization::make_nvp("word3",word3);
				}

				unsigned int word0;
				unsigned int word1;
				unsigned int word2;
				unsigned int word3;
		};
	}
}




#endif


