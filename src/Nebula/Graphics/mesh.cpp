
#include <Nebula/Math/geo/polyhedron.hpp>

#include <Nebula/Graphics/mesh.hpp>

Neb::mesh::mesh():
	vertices_(NULL),
	indices_(NULL)
{
	printf("%s\n",__PRETTY_FUNCTION__);
}
void	Neb::mesh::construct(math::geo::polyhedron* poly) {

	printf("%s\n",__PRETTY_FUNCTION__);

	fh_.len_vertices_ = 3 * poly->nt_ + 4 * poly->nq_;
	fh_.len_indices_ = 3 * poly->nt_ + 6 * poly->nq_;

	printf("vertices: %i elements\n",fh_.len_vertices_);
	printf("indices:  %i elements\n",fh_.len_indices_);

	vertices_ = new Neb::vertex[fh_.len_vertices_];
	indices_ = new GLushort[fh_.len_indices_];

	int m = 3 * poly->nt_;

	Neb::vertex* v = vertices_;

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

	// quads
	for(int i = 0; i < poly->nq_; i++)
	{
		for(int j = 0; j < 4; ++j)
		{
			v[i*4 + j].position = poly->quads_[i].v_[j].p;
			v[i*4 + j].normal = poly->quads_[i].v_[j].n;
		}

		int n = 0;
		for(int l = 0; l < 2; ++l)
		{
			for(int k = 0; k < 3; ++k)
			{	
				int j = (k+n) % 4;

				indices_[m + i*6 + l*3 + k] = m + i*4 + j;

				printf("% 3i ", m + i*4 + j);
			}
			printf("\n");
			n += 2;
		}
	}

}
void Neb::mesh::load(const char * name){

	printf("%s\n",__PRETTY_FUNCTION__);

	char filename[256];
	filename[0] = '\0';

	strcat(filename, GLUTPP_OBJECT_DIR"/");
	strcat(filename, name);

	FILE * fp;

	printf("load file '%s'\n",filename);

	fp = fopen(filename, "rb");

	if (fp <= 0) 
	{
		perror("fopen");
		exit(0);
	}

	// read header
	fread(&fh_, sizeof(file_header), 1, fp);

	//printf("vertices: %i elements\n",fh_.len_vertices_);
	//printf("indices:  %i elements\n",fh_.len_indices_);

	// allocate
	vertices_ = new Neb::vertex[fh_.len_vertices_];
	indices_ = new GLushort[fh_.len_indices_];

	fread(vertices_, sizeof(Neb::vertex), fh_.len_vertices_, fp);
	fread(indices_,  sizeof(GLushort),       fh_.len_indices_,  fp);

	fclose(fp);

	// print
	//for(int i = 0; i < fh_.len_vertices_; ++i) vertices_[i].print();

}
void Neb::mesh::save(const char * filename){
	
	printf("%s\n",__PRETTY_FUNCTION__);
	
	FILE * fp;
	
	fp = fopen(filename, "wb");
	
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
	for(int i = 0; i < fh_.len_vertices_; ++i)
	{
		//vertices_[i].print();
	}
	printf("'%s' saved\n",filename);
	
	// close
	fclose(fp);
}







