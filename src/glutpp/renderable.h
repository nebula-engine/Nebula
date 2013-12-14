#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

namespace glutpp
{
	class scene;
	namespace gui
	{
		class layout;
	}
	class renderable
	{
		public:
			renderable();
			void					init(std::shared_ptr<window>);
			void					resize();


			std::shared_ptr<scene>			scene_;
			std::shared_ptr<glutpp::gui::layout>	layout_;
	};
}

#endif
