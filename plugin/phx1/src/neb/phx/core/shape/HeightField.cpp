#include <iostream>
#include <fstream>
#include <climits>
#include <ctime>

#include <neb/fnd/app/Base.hpp>
#include <neb/fnd/util/cast.hpp>
#include <neb/fnd/math/geo/vertex.hpp>
#include <neb/fnd/core/shape/HeightField.hpp>

//#include <neb/gfx/mesh/tri1.hpp>

#include <neb/phx/core/shape/HeightField/Base.hpp>
#include <neb/phx/core/actor/rigidactor/base.hpp>
#include <neb/phx/app/base.hpp>

#include <neb/fnd/math/HeightField.hpp>

typedef neb::phx::core::shape::HeightField::Base THIS;

THIS::Base()
{
	printv_func(DEBUG);
}
void				THIS::__init(THIS::parent_t * const & p)
{
	printv_func(DEBUG);

	create_physics();
}
void				THIS::step(gal::etc::timestep  const & ts)
{
	printv_func(DEBUG);

}
void				THIS::create_physics()
{
	printv_func(DEBUG);

	auto fnd_app = get_fnd_app();
	
	if(!fnd_app->is_valid()) return;

	auto actor = neb::could_be<parent_t, neb::phx::core::actor::base>(getParent());
	assert(actor);

	if(px_shape_) return;

	if(actor) {
		auto rigidactor = actor->isPxActorRigidActorBase();//std::dynamic_pointer_cast<neb::fnd::actor::Rigid_Actor>(parent_.lock());

		assert(rigidactor);

		if(rigidactor) {
			if(!rigidactor->px_actor_) rigidactor->create_physics();
			assert(rigidactor->px_actor_);

			auto px_rigidactor = rigidactor->px_actor_->isRigidActor();
			assert(px_rigidactor);

			physx::PxMaterial* px_mat[2];

			auto app = dynamic_cast<neb::phx::app::base*>(get_fnd_app());
			assert(app);

			px_mat[0] = app->px_physics_->createMaterial(1,1,1);
			px_mat[1] = app->px_physics_->createMaterial(1,1,1);

			px_shape_ = px_rigidactor->createShape(*(to_geo()), px_mat, 2);
		}
	}
}
float scale(float x, float oa, float ob, float na, float nb)
{
	return (x - oa) / (ob - oa) * (nb - na) + na;
}
physx::PxGeometry*		THIS::to_geo()
{
	auto parent = dynamic_cast<neb::fnd::core::shape::HeightField::Base*>(getParent());
	
	unsigned int r = parent->desc_.r;
	unsigned int c = parent->desc_.c;

	float rowScale = parent->desc_.w / float(r-1);
	float colScale = parent->desc_.h / float(c-1);

	unsigned int nbVerts = r * c;
	
	assert(nbVerts <= (std::numeric_limits<unsigned short>::max() + 1));

	auto app = dynamic_cast<neb::phx::app::base*>(get_fnd_app());
	
	auto thePhysics = app->px_physics_;
	assert(thePhysics);

	// create heightfield short data

	neb::fnd::math::HeightField::Base hf(r, c);
	hf.createRandom();

	//for(float f : desc_.fc)
	//	hf.filterc(f);

	hf.normalize(-parent->desc_.hs, parent->desc_.hs);

	//assert(0);
	//
	// create physx data

	physx::PxHeightFieldSample* samples = new physx::PxHeightFieldSample[r * c];

	for(unsigned int i = 0; i < r; i++)
	{
		for(unsigned int j = 0; j < c; j++)
		{
			samples[i * c + j].height = (short)scale(hf.get(i,j), -parent->desc_.hs, parent->desc_.hs, float(SHRT_MIN), float(SHRT_MAX));
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
			parent->desc_.hs / float(SHRT_MAX),
			rowScale,
			colScale);

	//PxShape* aHeightFieldShape = aHeightFieldActor->createShape(hfGeom, aMaterialArray, nbMaterials);

	// testing heightfield mipmap
	//neb::math::HeightField* hf2 = hf.mipmap(2);
	//mesh_from_heightfield(hf2, rowScale * 4, colScale * 4);


	//mesh_from_heightfield(&hf, rowScale, colScale);

	return hfGeom;

}
void	THIS::load(ba::polymorphic_iarchive & ar, unsigned int const &)
{
}
void	THIS::save(ba::polymorphic_oarchive & ar, unsigned int const &) const
{
}



