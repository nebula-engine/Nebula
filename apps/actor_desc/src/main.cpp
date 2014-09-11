
#include <iostream>
#include <fstream>

#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/export.hpp>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

/*

#include <glm/gtc/matrix_transform.hpp>

#include <gal/console/base.hpp>

#include <gal/etc/stopwatch.hpp>

#include <neb/core/util/cast.hpp>
#include <neb/core/app/__base.hpp>
#include <neb/core/core/actor/base.hpp>
#include <neb/core/util/wrapper.hpp>
#include <neb/core/core/light/base.hpp>
#include <neb/core/core/scene/base.hpp>
#include <neb/core/core/shape/base.hpp>
#include <neb/core/core/shape/cuboid/desc.hpp>
#include <neb/core/core/actor/base.hpp>
*/

#include <gal/stl/wrapper.hpp>

#include <neb/core/core/actor/rigidbody/desc.hpp>

#include <neb/gfx/util/io.hpp>
/*
#include <neb/gfx/core/light/util/decl.hpp>
#include <neb/gfx/core/light/directional.hpp>
*/
#include <neb/gfx/core/light/spot.hpp>
/*#include <neb/gfx/Context/Window.hpp>
#include <neb/gfx/Context/fbo.hpp>
#include <neb/gfx/Context/fbo_multi.hpp>
#include <neb/gfx/environ/two.hpp>
#include <neb/gfx/environ/shadow/point.hpp>
#include <neb/gfx/environ/shadow/directional.hpp>
#include <neb/gfx/environ/SceneDefault.hpp>
#include <neb/gfx/environ/vis_depth.hpp>
#include <neb/gfx/gui/object/terminal.hh>
#include <neb/gfx/camera/view/ridealong.hh>
#include <neb/gfx/camera/view/shadow/point.hpp>
#include <neb/gfx/camera/proj/perspective.hpp>

#include <neb/core/game/map/base.hpp>
#include <neb/core/game/trigger/ActorEx1.hpp>

//#include <neb/ext/maze/game/map/maze2.hpp>

#include <neb/phx/app/base.hpp>
#include <neb/phx/core/scene/base.hpp>
#include <neb/phx/game/weapon/SimpleProjectile.hpp>
#include <neb/phx/game/game/base.hpp>
#include <neb/phx/core/actor/control/rigidbody/base.hpp>
#include <neb/phx/test.hpp>

//#include <neb/ext/maze/game/map/maze2.hpp>

#include <neb/fin/gfx_phx/app/base.hpp>
#include <neb/fin/gfx_phx/core/scene/base.hpp>
*/
#include <neb/fin/gfx_phx/core/actor/rigiddynamic/base.hpp>
/*#include <neb/fin/gfx_phx/core/actor/rigidstatic/base.hpp>
*/
#include <neb/fin/gfx_phx/core/shape/base.hpp>

template<typename B, typename D> void	makeDefaultFunc()
{

	gal::itf::shared::register_type(std::type_index(typeid(B)));
	gal::itf::shared::register_type(std::type_index(typeid(D)));


	std::function< std::shared_ptr<B>() > f(
			[]() { return std::shared_ptr<D>(new D(), gal::stl::deleter<D>()); }
			);

	gal::stl::factory<B>::default_factory_->add(typeid(D).hash_code(), f);
}


//BOOST_CLASS_EXPORT_GUID(neb::core::core::actor::base, "base")
//BOOST_CLASS_EXPORT_GUID(neb::fin::gfx_phx::core::actor::rigiddynamic::base, "derived")

void			s1()
{
	{
		typedef neb::core::core::actor::base T;
		typedef neb::fin::gfx_phx::core::actor::rigiddynamic::base D;

		std::ofstream ofs;
		ofs.open("actor.xml");
		assert(ofs.is_open());
		boost::archive::polymorphic_xml_oarchive ar(ofs);

		//ar.template register_type<T>();
		//ar.template register_type<D>();


		std::shared_ptr<D> d(new D(), gal::stl::deleter<D>());

		d->createShapeLightSpot(neb::core::pose(), glm::vec3(0,0,-1));



		gal::stl::wrapper<T> w(d);
		w.save(ar,0);
		
		//d->save(ar,0);

		//D* dp = d.get();

		//ar & dp;
	}

	{
		typedef neb::core::core::actor::base T;
		typedef neb::fin::gfx_phx::core::actor::rigiddynamic::base D;

		std::ifstream ifs;
		ifs.open("actor.xml");
		assert(ifs.is_open());

		boost::archive::polymorphic_xml_iarchive ar(ifs);
		//ar.template register_type<T>();
		//ar.template register_type<D>();


		gal::stl::wrapper<T> w;
		w.load(ar,1);
	
		auto d = w.ptr_;

		auto r = std::dynamic_pointer_cast<D>(d);
		assert(r);
		
		auto s = r->neb::core::core::shape::util::parent::map_.front();
		assert(s);

		//std::shared_ptr<D> d(0, gal::stl::deleter<D>());
			
		//T* tp;

		//d.load(ar,0);
		//ar & tp;


	}

}
void			s2()
{
	{
		typedef neb::core::core::actor::rigidbody::desc D;

		std::ofstream ofs;
		ofs.open("actor.xml");
		assert(ofs.is_open());
		boost::archive::polymorphic_xml_oarchive ar(ofs);

		std::shared_ptr<D> d(new D(neb::core::pose(glm::vec3(4,5,6))));

		gal::stl::wrapper<neb::core::core::actor::desc> w(d);
		w.save(ar,0);
	}

	{
		typedef neb::core::core::actor::rigidbody::desc D;

		std::ifstream ifs;
		ifs.open("actor.xml");
		assert(ifs.is_open());
		boost::archive::polymorphic_xml_iarchive ar(ifs);


		gal::stl::wrapper<neb::core::core::actor::desc> w;
		w.load(ar,0);

		auto d = w.ptr_;

		std::cout << "pos = " << d->pose.pos_ << std::endl;

		auto r = std::dynamic_pointer_cast<D>(d);
		assert(r);

		std::cout << "foo = " << r->foo << std::endl;

	}

}



int			main()
{
	makeDefaultFunc<neb::core::core::actor::desc, neb::core::core::actor::desc>();
	makeDefaultFunc<neb::core::core::actor::desc, neb::core::core::actor::rigidbody::desc>();

	makeDefaultFunc<neb::core::core::actor::base, neb::fin::gfx_phx::core::actor::rigiddynamic::base>();

	makeDefaultFunc<neb::core::core::shape::base, neb::fin::gfx_phx::core::shape::base>();

	makeDefaultFunc<neb::core::light::__base, neb::gfx::core::light::spot>();


	s1();

	return 0;

}





