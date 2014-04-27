#ifndef __GLUTPP_ACTOR_RAW_H__
#define __GLUTPP_ACTOR_RAW_H__

#include <math/transform.hpp>
//#include <math/raw/raw.hpp>


#include <galaxy/network/serial.hpp>
#include <galaxy/util.hpp>

#include <gru/config.hpp>
#include <gru/shape/desc.hpp>

template void gal::reset<glutpp::actor::raw>(std::shared_ptr<glutpp::actor::raw>&);

namespace glutpp {
	namespace actor {
		struct filter_data {
			unsigned int word0;
			unsigned int word1;
			unsigned int word2;
			unsigned int word3;
		};
		class raw: public gal::network::serial<glutpp::actor::raw, gal::network::base> {
			public:
				friend class glutpp::actor::raw_factory;
				
				//friend void gal::reset<glutpp::actor::raw>(glutpp::actor::raw_s&);
				template<typename T> friend void gal::reset(std::shared_ptr<T>&);
				
				enum
				{
					max_name_length = 31
				};

			protected:
				raw();
			public:
				virtual void			load(tinyxml2::XMLElement*);
				virtual void			load(glutpp::actor::actor_s);
				
				void				plane(tinyxml2::XMLElement*);
				void				controller(tinyxml2::XMLElement*);

				unsigned int			parse_filter(tinyxml2::XMLElement*, unsigned int);
				void				parse_filtering(tinyxml2::XMLElement*);


				glutpp::actor::type::e		type_;
				glutpp::actor::mode_create::e	mode_create_;
				unsigned int			flag_;
				char				name_[32];

				math::transform<float>		pose_;

				/** @brief Normal for planes. */
				math::vec3<float>		n_;
				/** @brief Distance for planes. */
				float				d_;

				math::vec3<float>		velocity_;
				float				density_;

				struct {
					filter_data		simulation_;
					filter_data		scene_query_;
				} filter_data_;
		};
	}
}

#endif








