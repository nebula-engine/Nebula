#ifndef NEBULA_ACTOR_BASE_HH
#define NEBULA_ACTOR_BASE_HH

#include <memory>

#include <boost/signals2.hpp>

#include <boost/archive/polymorphic_xml_iarchive.hpp>
#include <boost/archive/polymorphic_xml_oarchive.hpp>
#include <boost/serialization/map.hpp>

#include <neb/core/pose.hpp>
#include <neb/core/filter.hpp>
#include <neb/core/core/actor/__base.hpp>
#include <neb/core/core/actor/util/decl.hpp>
#include <neb/core/core/actor/util/flag.hpp>
#include <neb/core/core/actor/util/parent.hpp>
#include <neb/core/core/shape/base.hpp>
#include <neb/core/core/shape/util/parent.hpp>
#include <neb/core/core/shape/cuboid/desc.hpp>
//#include <neb/core/core/shape/HeightField/desc.hpp>
#include <neb/core/math/Serialization/glm.hpp>

#include <neb/core/game/weapon/util/parent.hpp>

namespace neb {

	namespace core { namespace core {

		namespace shape { namespace HeightField {
			class desc;
		}}

		namespace actor {

			/** @brief %base */
			class base:
				virtual public neb::core::core::actor::__base,
				virtual public neb::core::core::actor::util::parent,
				virtual public neb::core::core::shape::util::parent,
				virtual public neb::game::weapon::util::parent
			{
				public:
					typedef neb::util::parent<neb::core::core::actor::__base, neb::core::core::actor::util::parent>		actors;
					typedef neb::util::parent<neb::core::core::shape::base, neb::core::core::shape::util::parent>		shapes;

				public:
					//typedef neb::core::core::actor::__base> parent_t;
					/** @brief default constructor */
					base();
					/** @brief constructor */
					//base(std::shared_ptr<parent_t> parent);
					virtual ~base();
				public:
					virtual void						init(parent_t * const &) = 0;
					virtual void						release();
				public:
					virtual void						step(gal::etc::timestep const & ts);
				public:
					virtual neb::core::pose					getPose() const;
					virtual neb::core::pose					getPoseGlobal() const;

					bool							hasScene() const;
					neb::core::core::scene::base*				getScene() const;
					//std::shared_ptr<neb::core::core::actor::util::parent>		get_parent();
					/** @brief set pose
					 *
					 * virtual because actor::local will add self to active transform list
					 */
					virtual void						setPose(neb::core::pose const & pose);
				public:
					virtual std::weak_ptr<neb::core::core::shape::base>		createShapeBase(
							neb::core::pose pose) = 0;
					virtual std::weak_ptr<neb::core::core::shape::base>		createShapeCuboid(
							neb::core::core::shape::cuboid::desc) = 0;
					virtual std::weak_ptr<neb::core::core::shape::base>		createShapeCube(
							neb::core::pose pose, double size);
					virtual std::weak_ptr<neb::core::core::shape::base>		createShapeHeightField(
							neb::core::core::shape::HeightField::desc const &) = 0;
					virtual std::weak_ptr<neb::core::core::shape::base>		createShapeLightSpot(
							neb::core::pose pose, glm::vec3 direction);
				public:

					template<class Archive> void					__serialize(
							Archive & ar,
							unsigned int const & version)
					{
						ar & boost::serialization::make_nvp("flag",flag_);
						//ar & boost::serialization::make_nvp("name",name_);
						ar & boost::serialization::make_nvp("pose",pose_);
						ar & boost::serialization::make_nvp("velocity",velocity_);
						ar & boost::serialization::make_nvp("density",density_);

						ar & boost::serialization::make_nvp(
								"actors", neb::core::core::actor::util::parent::map_);
						ar & boost::serialization::make_nvp(
								"shapes", neb::core::core::shape::util::parent::map_);
					}

					virtual void	load(ba::polymorphic_iarchive & ar, unsigned int const &);
					virtual void	save(ba::polymorphic_oarchive & ar, unsigned int const &) const;
					BOOST_SERIALIZATION_SPLIT_MEMBER();

				public:
					neb::core::core::actor::util::flag			flag_;
					neb::core::pose						pose_;
					glm::vec3						velocity_;
					float							density_;
					double							health_;
					neb::phx::filter::data					simulation_;
					neb::phx::filter::data					scene_query_;

				public:
					/** @brief Parent */
					//weak_ptr<neb::core::core::actor::util::parent>		parent_;
			};
		}}}}

#endif

