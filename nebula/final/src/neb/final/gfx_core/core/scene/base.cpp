

sp::weak_ptr<neb::core::actor::rigidstatic::base>	phx::core::scene::local::createActorRigidStaticUninitialized() {

	auto actor(sp::make_shared<phx::core::actor::rigidstatic::local>(isPxSceneLocal()));

	neb::core::actor::util::parent::insert(actor);

	actor->simulation_.word0 = phx::filter::filter::type::STATIC;
	actor->simulation_.word1 = phx::filter::filter::RIGID_AGAINST;
	actor->simulation_.word2 = phx::filter::filter::type::STATIC;
	actor->simulation_.word3 = phx::filter::filter::type::PROJECTILE;

	return actor;
}


