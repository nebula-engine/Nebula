
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
#include <gal/dll/helper.hpp>

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
	typedef gal::dll::deleter<H>				DEL;
	
	auto lamb = [](std::string dll_name) {

		std::shared_ptr<H> h(new H);

		h->open(dll_name, "object");
		
		std::shared_ptr<D> d(h->create(), DEL(h));
	};

	std::function< std::shared_ptr<B>(std::string) > f(lamb);

	gal::stl::factory<B>::default_factory_->add(typeid(D).hash_code(), f);
}


//BOOST_CLASS_EXPORT_GUID(neb::core::core::actor::base, "base")
//BOOST_CLASS_EXPORT_GUID(neb::fin::gfx_phx::core::actor::rigiddynamic::base, "derived")

namespace ba = boost::archive;

class xml_oarchive: public ba::polymorphic_xml_oarchive
{
	public:
		//typedef ba::polymorphic_xml_oarchive base;
		typedef ba::polymorphic_oarchive_impl base;

		xml_oarchive(std::ofstream& ofs): ba::polymorphic_xml_oarchive(ofs) {}

		template<class T> void	save_override(T & t, BOOST_PFTO int){
			base::save_override(boost::serialization::make_nvp(NULL, t), 0);
		}
		template<class T> void	save_override(const boost::serialization::nvp< T > & t, int){
			// this is here to remove the "const" requirement.  Since
			// this class is to be used only for output, it's not required.
			base::save_override(t, 0);
		}


		void		save_override(const gal::stl::HashCode & t, int)
		{
			std::cout << "hello!" << std::endl;
			abort();
		}
		void			operator&(gal::stl::HashCode const & t)
		{
			std::cout << "hello!" << std::endl;
			abort();
		}
};

void			s1()
{
	{
		typedef neb::core::core::scene::base B;
		typedef neb::fin::gfx_phx::core::scene::base D;
		
		std::ofstream ofs;
		ofs.open("scene.xml");
		assert(ofs.is_open());
		xml_oarchive ar(ofs);

		//ar.template register_type<T>();
		//ar.template register_type<D>();

		
		std::shared_ptr<B> scene(new D, gal::stl::deleter<D>);
		
		
		/*

		// create actor
		std::shared_ptr<D> d(new D(), gal::stl::deleter<D>());

		auto s = d->createShapeCuboid(neb::core::core::shape::cuboid::desc(
					glm::vec3(1)
					)).lock();

		s->createLightSpot(glm::vec3(0,0,-1));

		*/

		gal::stl::wrapper<T> w(scene);
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



int			main()
{
	makeDefaultFunc<neb::core::core::actor::base, neb::fin::gfx_phx::core::actor::rigiddynamic::base>();

	makeDefaultFunc<neb::core::core::actor::base, neb::fin::gfx_phx::core::actor::rigiddynamic::base>();

	makeDefaultFunc<neb::core::core::shape::base, neb::fin::gfx_phx::core::shape::base>();
	makeDefaultFunc<neb::core::core::shape::base, neb::fin::gfx_phx::core::shape::box>();

	makeDefaultFunc<neb::core::light::__base, neb::gfx::core::light::spot>();


	s1();

	return 0;

}





