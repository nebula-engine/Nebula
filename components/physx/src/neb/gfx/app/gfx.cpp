
#include <neb/gfx/util/log.hpp>
#include <neb/gfx/app/__gfx.hpp>
#include <neb/gfx/window/Base.hh>
#include <neb/gfx/gui/layout/base.hpp>

void					neb::gfx::app::__gfx::init()
{

	std::vector<std::string> fontfiles({
		"/usr/share/fonts/msttcorefonts/cour.ttf",
		"/usr/share/fonts/truetype/msttcorefonts/cour.ttf"});

	// font
	//FT_Library ft;
	if(FT_Init_FreeType(&ft_))
	{
		printf("could not find freetype library\n");
		exit(0);
	}

	int result = 1;
	for(auto s : fontfiles) {
		result = FT_New_Face(ft_, s.c_str(), 0, &face_);
		if(result) {
			::std::cout << "Could not open font " << s << ::std::endl;
		} else {
			break;
		}
	}

	if(result) {
		printf("Count not open any fonts\n");
		abort();
	}


}
void				neb::gfx::app::__gfx::release()
{
}
void				neb::gfx::app::__gfx::step(gal::etc::timestep const & ts) {

	//neb::gfx::window::util::parent::step(ts);

	//neb::gfx::context::util::parent::step(ts);

	//neb::gfx::gui::layout::util::parent::step(ts);
}
void				neb::gfx::app::__gfx::render()
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	//neb::gfx::window::util::parent::render();

	//neb::gfx::context::util::parent::render();

}

//void							neb::gfx::app::__gfx::release() {
//}
std::weak_ptr<neb::gfx::app::__gfx>				neb::gfx::app::__gfx::global() {
	auto app(std::dynamic_pointer_cast<neb::gfx::app::__gfx>(g_app_));
	assert(app);
	return app;
}
/*std::weak_ptr<neb::gfx::gui::layout::base>		neb::gfx::app::__gfx::createLayout()
{
		auto self(dynamic_pointer_cast<neb::gfx::app::__gfx>(shared_from_this()));

		typedef neb::gfx::gui::layout::base T;

		std::shared_ptr<T> layout(new T(self), gal::stl::deleter<T>());

		neb::gfx::gui::layout::util::parent::insert(layout);

		layout->init();

		return layout;
		
	//return neb::util::parent<neb::gfx::gui::layout::base>::create<neb::gfx::gui::layout::base>();
}*/
/*std::weak_ptr<neb::gfx::window::base>			neb::gfx::app::__gfx::createWindow()
{
	auto self(std::dynamic_pointer_cast<neb::gfx::app::__gfx>(shared_from_this()));

	auto window = std::make_shared<neb::gfx::window::base>(self);

	neb::gfx::window::util::parent::insert(window);

	window->__init();

	return window;
}*/













