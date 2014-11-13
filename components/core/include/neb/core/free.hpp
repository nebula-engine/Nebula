#ifndef NEB_CORE_FREE_HPP
#define NEB_CORE_FREE_HPP

#include <gal/stl/wrapper.hpp>

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
template<typename T> std::shared_ptr<T>		loadXML(std::string filename)
{
	std::ifstream ifs;
	ifs.open(filename);
	if(!ifs.is_open())
	{
		std::cout << "file error: " << filename << std::endl;
		abort();
	}

	gal::stl::wrapper<T> w;

	boost::archive::polymorphic_xml_iarchive ar(ifs);

	w.load(ar,0);

	return w.ptr_;
}

#endif
