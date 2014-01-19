#ifndef __GLUTPP_ACTOR_H__
#define __GLUTPP_ACTOR_H__
#include <memory>
#include <vector>
#include <map>

#include <gal/flag.h>
#include <gal/network/message.h>
#include <gal/network/vector.h>

#include <math/vec4.h>
#include <math/vec3.h>
#include <math/vec2.h>
#include <math/geo/polyhedron.h>
#include <math/transform.h>

#include <glutpp/config.h>

#include <glutpp/actor/addr.h>
#include <glutpp/actor/raw.h>

#include <glutpp/texture.h>
#include <glutpp/material.h>
#include <glutpp/shape/shape.h>

namespace glutpp {
	namespace actor {
		template<typename RAW> class actor: public glutpp::parent, public gal::flag<unsigned int> {
			public:
				typedef std::shared_ptr<actor> SHARED;
				
				actor(glutpp::parent_s parent)
					: glutpp::parent(parent)
				{
					printf("%s\n",__PRETTY_FUNCTION__);

					assert(parent);
				}
				void i(int ni) {
					i_ = ni;
				}
				int i() {
					return i_;
				}
				void init(glutpp::actor::desc_s desc) {
					raw_ = *desc->get_raw();
				}
				unsigned int f() {
					return raw_.flag_;
				}
				void f(unsigned int flag) {
					raw_.flag_ = flag;
				}
				void cleanup() {

					//printf("%s\n",__PRETTY_FUNCTION__);

					auto it = actors_.begin();
					while(it != actors_.end())
					{
						std::shared_ptr<glutpp::actor::actor<RAW>> actor = it->second;

						actor->cleanup();

						if(actor->any(glutpp::actor::flag::e::SHOULD_RELEASE))
						{
							actor->release();

							actors_.erase(it);
						}
						else
						{
							++it;
						}
					}

					auto s = shapes_.begin();
					while(s != shapes_.end())
					{
						std::shared_ptr<glutpp::shape::shape> shape = s->second;

						shape->cleanup();

						if(shape->any(glutpp::shape::flag::e::SHOULD_RELEASE))
						{
							shape->release();

							shapes_.erase(s);
						}
						else
						{
							++s;
						}
					}

				}
				void release() {
					printf("%s\n",__PRETTY_FUNCTION__);

					for(auto it = actors_.begin(); it != actors_.end(); ++it)
					{
						it->second->release();
					}

					actors_.clear();
				}
				void step(double time) {

					shapes_.foreach<glutpp::shape::shape>(std::bind(
								&glutpp::shape::shape::step,
								std::placeholders::_1,
								time));

				}
				math::mat44 get_pose() {
					return raw_.pose_;
				}
				void set_pose(math::transform pose) {
					raw_.pose_ = pose;

					set(glutpp::actor::flag::e::SHOULD_UPDATE);

					notify_foundation_change_pose();
				}
				void notify_foundation_change_pose() {
				
					SHARED actor;
					glutpp::shape::shape_s shape;

					for(auto it = actors_.end(); it != actors_.end(); ++it)
					{
						actor = it->second;
						actor->notify_foundation_change_pose();
					}

					for(auto it = shapes_.end(); it != shapes_.end(); ++it)
					{
						shape = it->second;
						shape->notify_foundation_change_pose();
					}
				}
				void load_lights(int& i, math::mat44 space) {
					GLUTPP_DEBUG_1_FUNCTION;

					space *= raw_.pose_;

					for(auto it = actors_.begin(); it != actors_.end(); ++it)
					{
						it->second->load_lights(i, space);
					}

					for(auto it = shapes_.begin(); it != shapes_.end(); ++it)
					{
						it->second->load_lights(i, space);
					}
				}
				template<typename SCENE> std::shared_ptr<SCENE> get_scene() {
					GLUTPP_DEBUG_1_FUNCTION;

					auto parent = get_parent();
					assert(parent);

					auto scene = std::dynamic_pointer_cast<glutpp::scene::scene>(parent);

					if(scene) return scene;

					auto actor = std::dynamic_pointer_cast<glutpp::actor::actor>(parent);

					if(actor) return actor->get_scene();

					abort();
				}
				void draw(glutpp::window::window_s window, math::mat44 space) {
					GLUTPP_DEBUG_1_FUNCTION;

					space = space * raw_.pose_;

					for(auto it = shapes_.begin(); it != shapes_.end(); ++it)
					{
						it->second->draw(window, space);
					}
				}
			public:

				glutpp::shape::shape_m			shapes_;
				gal::map<glutpp::actor::actor<RAW>>	actors_;
			public:
				int		i_;
				raw		raw_;
		};
	}
}

#endif
