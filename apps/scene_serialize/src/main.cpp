
#include <iostream>
#include <fstream>

#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/export.hpp>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include <cxxabi.h>

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
#include <gal/stl/deleter.hpp>
#include <gal/dll/helper.hpp>

#include <neb/core/core/actor/rigiddynamic/desc.hpp>

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
*/
#include <neb/fin/gfx_phx/core/scene/base.hpp>
#include <neb/fin/gfx_phx/core/actor/rigiddynamic/base.hpp>
/*#include <neb/fin/gfx_phx/core/actor/rigidstatic/base.hpp>
*/
#include <neb/fin/gfx_phx/core/shape/base.hpp>
#include <neb/fin/gfx_phx/core/shape/box.hpp>

template<typename B, typename D> void	makeDefaultFunc()
{

	gal::itf::shared::register_type(std::type_index(typeid(B)));
	gal::itf::shared::register_type(std::type_index(typeid(D)));


	std::function< std::shared_ptr<B>() > f(
			[]() { return std::shared_ptr<D>(new D(), gal::stl::deleter<D>()); }
			);

	gal::stl::factory<B>::default_factory_->add(typeid(D).hash_code(), f);
}
template<typename B, typename D> void	makeDLLFunc()
{

	gal::itf::shared::register_type(std::type_index(typeid(B)));
	gal::itf::shared::register_type(std::type_index(typeid(D)));
	
	//typedef neb::fin::gfx_phx::core::scene::base		D;
	typedef gal::dll::helper<D>				H;
	//typedef gal::dll::deleter				DEL;
	
	auto lamb = [](gal::dll::helper_info& hi) {
		
		std::shared_ptr<H> h(new H(hi.file_name, hi.object_name));
		
		h->open();
		
		std::shared_ptr<B> d = h->make_shared();

		return d;
	};

	std::function< std::shared_ptr<B>(gal::dll::helper_info&) > f(lamb);

	gal::stl::factory<B>::default_factory_->add(typeid(D).hash_code(), f);
}
template<typename B, typename D> gal::stl::wrapper<B>		loadDLL(std::string file_name, std::string object_name)
{
	std::cout << "B " << typeid(B).name() << " " << typeid(B).hash_code() << std::endl;
	std::cout << "D " << typeid(D).name() << " " << typeid(D).hash_code() << std::endl;

	typedef gal::dll::helper<D>	H;
	
	std::shared_ptr<H> h(new H(file_name, object_name));

	h->open();
	
	std::shared_ptr<D> p = h->make_shared();
	
	gal::stl::wrapper<B> w(p);
	
	return w;
}


namespace ba = boost::archive;

void			s1()
{
	{
		typedef neb::core::core::scene::base B;
		typedef neb::fin::gfx_phx::core::scene::base D;
		
		std::ofstream ofs;
		ofs.open("scene.xml");
		assert(ofs.is_open());
		ba::polymorphic_xml_oarchive ar(ofs);

		//ar.template register_type<T>();
		//ar.template register_type<D>();
		
		auto w = loadDLL<B,D>("../../components/ext/hf/libnebula_ext_hf_0_so_db.so", "scene");
		
		auto scene = w.ptr_;

		typedef neb::core::core::actor::rigiddynamic::desc actor_desc;
		actor_desc* ad = new actor_desc;
		auto actor = scene->createActorRigidDynamic(ad).lock();


		auto shape = actor->createShapeCuboid(neb::core::core::shape::cuboid::desc(
					glm::vec3(1)
					)).lock();


		/*

		// create actor
		std::shared_ptr<D> d(new D(), gal::stl::deleter<D>());

		auto s = d->createShapeCuboid(neb::core::core::shape::cuboid::desc(
					glm::vec3(1)
					)).lock();

		s->createLightSpot(glm::vec3(0,0,-1));

		*/

		w.save(ar,0);

		//d->save(ar,0);

		//D* dp = d.get();

		//ar & dp;
	}

	{
		typedef neb::core::core::scene::base B;
		typedef neb::fin::gfx_phx::core::scene::base D;

		std::ifstream ifs;
		ifs.open("scene.xml");
		assert(ifs.is_open());

		boost::archive::polymorphic_xml_iarchive ar(ifs);
		//ar.template register_type<T>();
		//ar.template register_type<D>();


		gal::stl::wrapper<B> w;
		w.load(ar,0);

		/*
		   auto d = w.ptr_;

		   auto r = std::dynamic_pointer_cast<D>(d);
		   assert(r);

		   auto s = r->neb::core::core::shape::util::parent::map_.front();
		   assert(s);
		   */
		//std::shared_ptr<D> d(0, gal::stl::deleter<D>());

		//T* tp;

		//d.load(ar,0);
		//ar & tp;


	}

}



int			main()
{
	//makeDefaultFunc<neb::core::core::scene::base, neb::fin::gfx_phx::core::scene::base>();
	makeDLLFunc<neb::core::core::scene::base, neb::fin::gfx_phx::core::scene::base>();

	makeDefaultFunc<neb::core::core::actor::base, neb::fin::gfx_phx::core::actor::rigiddynamic::base>();

	makeDefaultFunc<neb::core::core::shape::base, neb::fin::gfx_phx::core::shape::base>();
	makeDefaultFunc<neb::core::core::shape::base, neb::fin::gfx_phx::core::shape::box>();

	makeDefaultFunc<neb::core::light::__base, neb::gfx::core::light::spot>();



	int status;

	char const * name1 = "N3gal3stl7funcmapIN3neb4core4core5scene4baseEE10__functionIINS_3dll11helper_infoEEEE";
	char const * name2 = "N3gal3stl7funcmapIN3neb4core4core5scene4baseEE10__functionIIRNS_3dll11helper_infoEEEE";
	
	char* realname1 = abi::__cxa_demangle(name1, 0, 0, &status);
	char* realname2 = abi::__cxa_demangle(name2, 0, 0, &status);

	std::cout << "name1 = " << realname1 << std::endl;
	std::cout << "name2 = " << realname2 << std::endl;

	s1();

	return 0;

}





