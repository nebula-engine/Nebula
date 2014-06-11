#include <iostream>
#include <iomanip>

#include <Galaxy-Log/log.hpp>

#include <Nebula/Math/geo/polyhedron.hh>

#include <Nebula/Graphics/mesh.hh>

Neb::mesh::mesh():
	vertices_(NULL),
	indices_(NULL)
{
	printf("%s\n",__PRETTY_FUNCTION__);
}
void	Neb::mesh::construct(math::geo::polyhedron* poly) {

	auto tris = poly->triangles();
	
	printf("%s\n",__PRETTY_FUNCTION__);
	
	fh_.len_vertices_ = 3 * tris.size();
	fh_.len_indices_ =  3 * tris.size();
	
	
	printf("vertices: %i elements\n",fh_.len_vertices_);
	printf("indices:  %i elements\n",fh_.len_indices_);

	vertices_ = new Neb::vertex[fh_.len_vertices_];
	indices_  = new GLushort[fh_.len_indices_];
	
	
	
	
	Neb::vertex* v = vertices_;
	
	for(size_t i = 0; i < (3 * tris.size()); ++i) {
		indices_[i] = i;
	}
	
	
	for(auto t : tris) {
		assert(t);
		for(int i = 0; i < 3; ++i) {
			assert(t->v_[i]);
			v->position = t->v_[i]->p;
			v->normal   = t->v_[i]->n;
		}
		v++;
	}
	
/*	
	// tris
	for(int i = 0; i < poly->nt_; i++)
	{
		for(int j = 0; j < 3; ++j)
		{
			int k = i*3 + j;
			printf("% 2i ",k);

			v[i*3+j].position = poly->tris_[i].v_[j].p;
			v[i*3+j].normal = poly->tris_[i].v_[j].n;

			indices_[i*3+j] = i*3+j;
		}
		printf("\n");
	}

	v = vertices_ + m;
	auto ind = indices_ + m;
	
	// quads
	for(int i = 0; i < poly->nq_; i++)
	{
		for(int j = 0; j < 3; ++j)
		{
			v[i*4 + j].position = poly->quads_[i].tri_[0].v_[j].p;
			v[i*4 + j].normal   = poly->quads_[i].tri_[0].v_[j].n;
		}
		int j = 3;
		v[i*4 + j].position = poly->quads_[i].tri_[0].v_[2].p;
		v[i*4 + j].normal   = poly->quads_[i].tri_[0].v_[2].n;
		
		
		int n = 0;
		for(int l = 0; l < 2; ++l)
		{
			for(int k = 0; k < 3; ++k)
			{	
				int j = (k+n) % 4;

				ind[i*6 + l*3 + k] = m + i*4 + j;

				printf("% 3i ", m + i*4 + j);
			}
			printf("\n");
			n += 2;
		}
	}
*/
}
void Neb::mesh::load(std::string name)	{

	printf("%s\n",__PRETTY_FUNCTION__);

	std::string filename = std::string(GLUTPP_OBJECT_DIR) + "/" + name;
	
	FILE * fp;
	
	std::cout << "load file " << filename << std::endl;
	
	fp = fopen(filename.c_str(), "rb");

	if (fp <= 0) {
		perror("fopen");
		abort();
	}
	
	// read header
	fread(&fh_, sizeof(file_header), 1, fp);

	printf("vertices: %i elements\n",fh_.len_vertices_);
	printf("indices:  %i elements\n",fh_.len_indices_);

	// allocate
	vertices_ = new Neb::vertex[fh_.len_vertices_];
	indices_ = new GLushort[fh_.len_indices_];

	fread(vertices_, sizeof(Neb::vertex), fh_.len_vertices_, fp);
	fread(indices_,  sizeof(GLushort),       fh_.len_indices_,  fp);

	fclose(fp);

	// print
	//for(int i = 0; i < fh_.len_vertices_; ++i) vertices_[i].print();

}
void		Neb::mesh::save(std::string filename){
	
	printf("%s\n",__PRETTY_FUNCTION__);
	
	FILE * fp;
	
	fp = fopen(filename.c_str(), "wb");
	
	if (!fp) 
	{
		perror("fopen");
		exit(0);
	}
	
	// read header
	fwrite(&fh_, sizeof(file_header), 1, fp);
	fwrite(vertices_, sizeof(Neb::vertex), fh_.len_vertices_, fp);
	fwrite(indices_, sizeof(GLushort), fh_.len_indices_, fp);
	
	// print

	std::cout << "saved " << filename << std::endl;
	
	// close
	fclose(fp);
}
void		Neb::mesh::print(int sl) {
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", (severity_level)sl) << "mesh";
	
	if(vertices_) {
		for(int i = 0; i < fh_.len_vertices_; ++i)
		{
			vertices_[i].print(sl);
		}	
	}
}

void		Neb::vertex::print(int sl) {
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", (severity_level)sl)
		<< std::setw(8) << " "
		<< std::setw(8) << "p"
		<< std::setw(8) << position[0]
		<< std::setw(8) << position[1]
		<< std::setw(8) << position[2];

}



