#include <iostream>
#include <iomanip>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <Galaxy-Log/log.hpp>

#include <Nebula/math/geo/polyhedron.hh>

#include <Nebula/gfx/mesh.hh>



neb::gfx::mesh::mesh() {
	printf("%s\n",__PRETTY_FUNCTION__);
}
neb::gfx::mesh::~mesh() {
	printf("%s\n",__PRETTY_FUNCTION__);
}
void	neb::gfx::mesh::construct(math::geo::polyhedron* poly) {

	auto tris = poly->triangles();
	
	printf("%s\n",__PRETTY_FUNCTION__);
	
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", info) << "tris: " << tris.size();


	
	for(size_t i = 0; i < (3 * tris.size()); ++i) {
		indices_.push_back(i);
	}
	
	
	for(auto t : tris) {
		assert(t);
		for(int i = 0; i < 3; ++i) {
			assert(t->v_[i]);
			vertices_.push_back(*(t->v_[i]));
		}
	}

	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", info) << "vertices: " << vertices_.size();
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", info) << "indices:  " << indices_.size();


}
void		neb::gfx::mesh::serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
	
	printf("%s\n",__PRETTY_FUNCTION__);
	
	/*std::string filename = std::string(GLUTPP_OBJECT_DIR) + "/" + name;
	
	FILE * fp;
	
	std::cout << "load file " << filename << std::endl;

	fp = fopen(filename.c_str(), "rb");

	if (fp <= 0) {
		perror("fopen");
		abort();
	}*/
	
	ar & vertices_;
	ar & indices_;
	
	
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", info) << "vertices: " << vertices_.size();
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", info) << "indices:  " << indices_.size();

}
void		neb::gfx::mesh::serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {

	printf("%s\n",__PRETTY_FUNCTION__);
	
	ar & vertices_;
	ar & indices_;
	
	
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", info) << "vertices: " << vertices_.size();
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", info) << "indices:  " << indices_.size();

}
void		neb::gfx::mesh::print(int sl) {
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", (severity_level)sl) << "mesh";

	for(auto v : vertices_) {
		v.print(sl);
	}	
}





