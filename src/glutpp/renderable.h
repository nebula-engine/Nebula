#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

#include <memory>

#include <gal/flag.h>

#include <glutpp/gui/layout.h>
#include <glutpp/window.h>
#include <glutpp/scene.h>

namespace glutpp
{
	class renderable: public gal::flag, public std::enable_shared_from_this<glutpp::renderable>
	{
		public:
			renderable();
			renderable&				operator=(renderable const &);
			void					init(std::shared_ptr<window>);
			void					render(double);
			void					resize(int,int);


			struct
			{
				std::shared_ptr<program>	text_;
			} programs_;

			std::weak_ptr<window>			window_;

			std::shared_ptr<scene>			scene_;
			std::shared_ptr<glutpp::gui::layout>	layout_;
	};
}

#endif
