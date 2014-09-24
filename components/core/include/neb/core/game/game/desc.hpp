#ifndef NEBULA_GAME_GAME_DESC_HPP
#define NEBULA_GAME_GAME_DESC_HPP

#include <neb/core/game/game/util/decl.hpp>

namespace neb {
	namespace app {
		class __core;
	}

	namespace game {
		namespace game {

			struct desc: gal::itf::shared
			{
				desc() {}
				virtual ~desc() {}

				virtual void				release() {}

				template<class Archive> void		__load(Archive & ar, unsigned int const & version)
				{
					ar & boost::serialization::make_nvp("sceneDllFile",sceneDllFile);
				}

				template<class Archive> void		__save(Archive & ar, unsigned int const & version) const
				{
					ar & boost::serialization::make_nvp("sceneDllFile",sceneDllFile);
				}

				virtual void				load(
						boost::archive::xml_iarchive & ar,
						unsigned int const & version) {}

				virtual void				save(
						boost::archive::xml_oarchive & ar,
						unsigned int const & version) const {}

				virtual std::shared_ptr<neb::game::game::base>		visit(
						neb::app::__core * const
						) const { return std::shared_ptr<neb::game::game::base>(); }

				BOOST_SERIALIZATION_SPLIT_MEMBER();

					std::string		sceneDllFile;

			};



		}
	}
}

#endif

