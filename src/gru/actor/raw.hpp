#ifndef __GLUTPP_ACTOR_RAW_H__
#define __GLUTPP_ACTOR_RAW_H__

//#include <math/transform.hpp>
//#include <math/raw/raw.hpp>

#include <boost/serialization/nvp.hpp>

#include <PxPhysicsAPI.h>

//#include <galaxy/network/serial.hpp>
//#include <galaxy/util.hpp>

#include <gru/config.hpp> // gru/config.hpp.in
#include <gru/shape/desc.hpp>
#include <gru/Filter.hpp>

//template void gal::reset<glutpp::actor::raw>(std::shared_ptr<glutpp::actor::raw>&);

namespace glutpp {
	namespace actor {

		class raw {
			public:
				friend class glutpp::actor::raw_factory;

				//template<typename T> friend void gal::reset(std::shared_ptr<T>&);

				enum
				{
					max_name_length = 31
				};
			protected:
				raw();
			public:
				//virtual void			load(tinyxml2::XMLElement*);
				virtual void			load(boost::shared_ptr<glutpp::actor::actor>);

				raw&				operator=(raw const & r);

				//void				plane(tinyxml2::XMLElement*);
				//void				controller(tinyxml2::XMLElement*);

				unsigned int			parse_filter_word(tinyxml2::XMLElement*, unsigned int);
				void				parse_filter(tinyxml2::XMLElement*);
				void				parse_type(std::string);

				template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {

					ar & boost::serialization::make_nvp("type",type_);
					ar & boost::serialization::make_nvp("mode_create",mode_create_);
					ar & boost::serialization::make_nvp("flag",flag_);
					ar & boost::serialization::make_nvp("name",name_);
					ar & boost::serialization::make_nvp("pose",pose_);
					ar & boost::serialization::make_nvp("normal",n_);
					ar & boost::serialization::make_nvp("distance",d_);
					ar & boost::serialization::make_nvp("velocity",velocity_);
					ar & boost::serialization::make_nvp("density",density_);
					ar & boost::serialization::make_nvp("filter_data_simulation",simulation_);
					ar & boost::serialization::make_nvp("filter_data_scene_query",scene_query_);





					/*
					   void glutpp::actor::raw::load(tinyxml2::XMLElement* element) {
					   GLUTPP_DEBUG_0_FUNCTION;

					   assert(element);

					// type
					const char* buf = element->Attribute("type");
					assert(buf);
					if( strcmp(buf, "rigid_dynamic") == 0)
					{
					type_ = glutpp::actor::type::e::RIGID_DYNAMIC;
					}
					else if( strcmp(buf, "rigid_static") == 0)
					{
					type_ = glutpp::actor::type::e::RIGID_STATIC;
					}	
					else if( strcmp(buf, "plane") == 0)
					{
					type_ = glutpp::actor::type::e::PLANE;
					}	
					else if(strcmp(buf, "controller") == 0)
					{
					type_ = glutpp::actor::type::e::CONTROLLER;
					}
					else if(strcmp(buf, "empty") == 0)
					{
					type_ = glutpp::actor::type::e::EMPTY;
					}
					else
					{
					printf("unknown actor type\n");
					abort();
					}

					// mode create
					buf = element->Attribute("mode_create");
					if(buf != NULL)
					{
					if(strcmp(buf, "deferred") == 0)
					{
					printf("DEFERRED\n");
					mode_create_ = glutpp::actor::mode_create::e::DEFERRED;
					}
					else if(strcmp(buf, "now") == 0)
					{
					printf("NOW\n");
					mode_create_ = glutpp::actor::mode_create::e::NOW;
					}
					else
					{
					printf("invalid mode\n");
					abort();
					}
					}

					// name
					buf = element->Attribute("name");
					if(buf != NULL)
					{
					int len = std::min(strlen(buf), (size_t)max_name_length);

					memcpy(name_, buf, len);
					name_[len] = 0;
					}

					// pose
					pose_ = math::Xml::parse_transform<float>(element->FirstChildElement("pose"), def);

					// velocity
					tinyxml2::XMLElement* e = element->FirstChildElement("velocity");
					if(e != NULL) velocity_ = gru::Xml::parseVec3(e);


					// flags
					e = element->FirstChildElement("flag");
					while(e != NULL) {
						buf = e->GetText();
						if(strcmp(buf, "DESTRUCTIBLE") == 0)
						{
							flag_ |= glutpp::actor::actor::flag::e::DESTRUCTIBLE;
						}
						else if(strcmp(buf, "DESTRUCTIBLE") == 0)
						{

						}
						else
						{
							printf("unknwon flag '%s'\n", buf);
							abort();
						}

						e = e->NextSiblingElement("flag");
					}

					// filtering
					parse_filtering(element);
					*/






				}

				glutpp::actor::type::e		type_;
				glutpp::actor::mode_create::e	mode_create_;
				unsigned int			flag_;
				char				name_[32];

				physx::PxTransform		pose_;

				/** @brief Normal for planes. */
				physx::PxVec3		n_;
				/** @brief Distance for planes. */
				float				d_;

				//physx::PxVec3		velocity_;
				physx::PxVec3			velocity_;
				float				density_;

				gru::Filter::Data		simulation_;
				gru::Filter::Data		scene_query_;

				};
		}
	}
#endif








