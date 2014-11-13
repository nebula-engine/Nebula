
#include <neb/gfx/Context/Util/Parent.hh>
#include <neb/gfx/Context/fbo.hpp>
#include <neb/gfx/Context/fbo_multi.hpp>
#include <neb/gfx/environ/vis_depth.hpp>

typedef neb::gfx::context::fbo		C_FBO;
typedef neb::gfx::context::fbo_multi	C_FBOM;
typedef neb::gfx::context::window	C_W;

void					neb::gfx::context::util::parent::render() {

	auto lamb = [&] (pointer p) {
		p->render();
	};

	map_.for_each(lamb);

}
std::weak_ptr<C_W>			neb::gfx::context::util::parent::createContextWindow()
{
	//auto self = isWindowBase();
	//assert(self);
	
	return create<C_W>();
	/*
	std::shared_ptr<C_W> context(new C_W());
	
	insert(context);
	
	context->init();
	
	return context;*/
}
std::weak_ptr<C_FBO>			neb::gfx::context::util::parent::createContextFBO() {

	return create<C_FBO>();
/*
	auto self = isWindowBase();
	assert(self);

	std::shared_ptr<C_FBO> context(new C_FBO(self));
	
	insert(context);

	context->init();

	return context;*/
}
std::weak_ptr<C_FBOM>			neb::gfx::context::util::parent::createContextFBOMulti() {

	return create<C_FBOM>();

	/*
	auto self = isWindowBase();
	assert(self);

	std::shared_ptr<C_FBOM> context(new C_FBOM(self));
	
	insert(context);

	context->init();

	return context;*/
}
std::weak_ptr<C_W>			neb::gfx::context::util::parent::createContextVisDepth() {

	return create<C_W>();
/*
	auto self = isWindowBase();
	assert(self);
	
	std::shared_ptr<C_W> context(new C_W(self));
	insert(context);
	
	auto environ = context->createEnvironVisDepth().lock();

	context->init();
	
	return context;
	*/
}


