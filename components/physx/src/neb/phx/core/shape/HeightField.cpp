#include <iostream>
#include <fstream>
#include <climits>
#include <ctime>

#include <neb/core/rand.hpp>
#include <neb/core/util/cast.hpp>
#include <neb/core/math/geo/vertex.hpp>

#include <neb/gfx/mesh/tri1.hpp>

#include <neb/phx/core/shape/HeightField.hpp>
#include <neb/phx/core/actor/rigidactor/base.hpp>
#include <neb/phx/app/base.hpp>

#include <neb/core/math/HeightField.hpp>

typedef neb::phx::core::shape::HeightField THIS;


typedef neb::phx::core::shape::HeightField THIS;

neb::phx::core::shape::HeightField::HeightField()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}
void				neb::phx::core::shape::HeightField::init(THIS::parent_t * const & p)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	setParent(p);

	neb::core::core::shape::base::init(p);
	neb::gfx::core::shape::base::init(p);
	neb::phx::core::shape::base::init(p);

	create_physics();
}
void				neb::phx::core::shape::HeightField::release()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	neb::core::core::shape::base::release();
	neb::gfx::core::shape::base::release();
	neb::phx::core::shape::base::release();


}
void				neb::phx::core::shape::HeightField::step(gal::etc::timestep  const & ts)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

}
void				neb::phx::core::shape::HeightField::create_physics()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	auto actor = neb::could_be<parent_t, neb::phx::core::actor::base>(getParent());
	assert(actor);

	if(px_shape_) return;

	if(actor) {
		auto rigidactor = actor->isPxActorRigidActorBase();//std::dynamic_pointer_cast<neb::core::actor::Rigid_Actor>(parent_.lock());

		assert(rigidactor);

		if(rigidactor) {
			assert(rigidactor->px_actor_);

			auto px_rigidactor = rigidactor->px_actor_->isRigidActor();
			assert(px_rigidactor);

			physx::PxMaterial* px_mat[2];
			px_mat[0] = phx::app::base::global()->px_physics_->createMaterial(1,1,1);
			px_mat[1] = phx::app::base::global()->px_physics_->createMaterial(1,1,1);

			px_shape_ = px_rigidactor->createShape(*(to_geo()), px_mat, 2);
		}
	}

}


float scale(float x, float oa, float ob, float na, float nb)
{
	return (x - oa) / (ob - oa) * (nb - na) + na;
}

physx::PxGeometry*		neb::phx::core::shape::HeightField::to_geo() {

	unsigned int r = desc_.r;
	unsigned int c = desc_.c;

	float rowScale = desc_.w / float(r-1);
	float colScale = desc_.h / float(c-1);

	unsigned int nbVerts = r * c;

	typedef neb::gfx::mesh::tri1 mesh_type;

	assert(nbVerts <= (std::numeric_limits<mesh_type::index_type>::max() + 1));

	auto thePhysics = phx::app::base::global()->px_physics_;
	assert(thePhysics);

	// create heightfield short data

	neb::math::HeightField hf(r, c);
	hf.createRandom();


	for(float f : desc_.fc)
		hf.filterc(f);

	hf.normalize(-desc_.hs, desc_.hs);


	//assert(0);
	//
	// create physx data

	physx::PxHeightFieldSample* samples = new physx::PxHeightFieldSample[r * c];

	for(unsigned int i = 0; i < r; i++)
	{
		for(unsigned int j = 0; j < c; j++)
		{
			samples[i * c + j].height = (short)scale(hf.get(i,j), -desc_.hs, desc_.hs, float(SHRT_MIN), float(SHRT_MAX));
			samples[i * c + j].materialIndex0 = physx::PxBitAndByte(0,0);
			samples[i * c + j].materialIndex1 = physx::PxBitAndByte(1,0);
		}
	}

	physx::PxHeightFieldDesc hfDesc;
	hfDesc.format             = physx::PxHeightFieldFormat::eS16_TM;
	hfDesc.nbColumns          = c;
	hfDesc.nbRows             = r;
	hfDesc.thickness          = -10.0f;
	hfDesc.samples.data       = samples;
	hfDesc.samples.stride     = sizeof(physx::PxHeightFieldSample);

	physx::PxHeightField* aHeightField = thePhysics->createHeightField(hfDesc);


	physx::PxHeightFieldGeometry* hfGeom = new physx::PxHeightFieldGeometry(
			aHeightField,
			physx::PxMeshGeometryFlags(),
			desc_.hs / float(SHRT_MAX),
			rowScale,
			colScale);

	//PxShape* aHeightFieldShape = aHeightFieldActor->createShape(hfGeom, aMaterialArray, nbMaterials);

	// testing heightfield mipmap
	//neb::math::HeightField* hf2 = hf.mipmap(2);
	//mesh_from_heightfield(hf2, rowScale * 4, colScale * 4);

	mesh_from_heightfield(&hf, rowScale, colScale);

	return hfGeom;

}
void	THIS::mesh_from_heightfield(neb::math::HeightField* hf, float rowScale, float colScale)
{
	unsigned int r = hf->_M_r;
	unsigned int c = hf->_M_c;
	unsigned int nbVerts = r * c;

	typedef neb::gfx::mesh::tri1 mesh_type;

	unsigned int nbTriangles = (r - 1) * (c - 1) * 2;
	unsigned int nbIndices = nbTriangles * 3;
	::math::geo::vertex* vertices = new ::math::geo::vertex[nbVerts];
	mesh_type::index_type* indices = new mesh_type::index_type[nbIndices];
	
	
	min_y_ = hf->min();
	max_y_ = hf->max();
	
	hf->slope(rowScale, colScale);

	for(unsigned int i = 0; i < r; i++)
	{
		for(unsigned int j = 0; j < c; j++)
		{
			int ind = hf->at(i,j);

			if(1) {
				vertices[hf->at(i,j)].p = glm::vec3(
						(float)i * rowScale,
						(float)j * colScale,
						hf->get(i,j)
						);

				vertices[ind].tc = glm::vec2(
						(float)i / (float)(r-1),
						(float)j / (float)(c-1)
						);

				vertices[hf->at(i,j)].n = glm::vec3(
						-hf->_M_dzdx[hf->at(i,j)],
						-hf->_M_dzdy[hf->at(i,j)],
						2.0 * rowScale
						);
			} else {
				vertices[hf->at(i,j)].p = glm::vec3(
						(float)i * rowScale,
						hf->get(i,j),
						(float)j * colScale
						);

				vertices[ind].tc = glm::vec2(
						(float)i / (float)(r-1),
						(float)j / (float)(c-1)
						);

				vertices[hf->at(i,j)].n = glm::vec3(
						hf->_M_dzdx[hf->at(i,j)],
						2.0 * rowScale,
						hf->_M_dzdy[hf->at(i,j)]
						);
			}
		}
	}


	for(unsigned int i = 0; i < (r-1); i++)
	{
		for(unsigned int j = 0; j < (c-1); j++)
		{
			unsigned int d = (i * (c-1) + j) * 6;

			assert((d+5) < nbIndices);

			if(1) {
				indices[d+0] = hf->at(i    , j    );
				indices[d+1] = hf->at(i + 1, j    );
				indices[d+2] = hf->at(i    , j + 1);

				indices[d+3] = hf->at(i + 1, j    );
				indices[d+4] = hf->at(i + 1, j + 1);
				indices[d+5] = hf->at(i    , j + 1);
			} else {
				// reversed
				indices[d+0] = hf->at(i    , j    );
				indices[d+1] = hf->at(i    , j + 1);
				indices[d+2] = hf->at(i + 1, j    );

				indices[d+3] = hf->at(i + 1, j    );
				indices[d+4] = hf->at(i    , j + 1);
				indices[d+5] = hf->at(i + 1, j + 1);
			}
		}
	}

	mesh_.reset(new neb::gfx::mesh::tri1);

	mesh_->setVerts(vertices, nbVerts);
	mesh_->setIndices(indices, nbIndices);

	// testing generated normal map
	//mesh_->normal_map_ = neb::gfx::texture::makePNG("test.png");

}
void	THIS::load(ba::polymorphic_iarchive & ar, unsigned int const &)
{
}
void	THIS::save(ba::polymorphic_oarchive & ar, unsigned int const &) const
{
}
void			THIS::draw(
		neb::gfx::glsl::program::base const * const & p,
		neb::core::pose const & pose)
{}
void			THIS::drawHF(
		neb::gfx::glsl::program::base const * const & p,
		neb::core::pose const & pose)
{
	auto npose = pose * pose_;

	p->use();

	// load texture height range
	neb::gfx::ogl::glUniform(p->uniform_table_[neb::gfx::glsl::uniforms::HF_MIN], min_y_);
	neb::gfx::ogl::glUniform(p->uniform_table_[neb::gfx::glsl::uniforms::HF_MAX], max_y_);


	draw_elements(p, npose);

	
}



