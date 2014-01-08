#include <glutpp/scene/scene.h>
#include <glutpp/actor/actor.h>

void glutpp::actor::addr::write(gal::network::message_shared msg) {
	
	assert(!actor_.expired());
	
	auto a = actor_.lock();
	
	if(!a->actor_.expired())
	{
		a->actor_.lock()->write_addr(msg);
	}
	else
	{
		a->scene_.lock()->write_addr(msg);
	}
	
	msg->write(&a->i_, sizeof(int));
	
	int i = -1;
	msg->write(&a, sizeof(int));
}
void glutpp::actor::addr::read(gal::network::message_shared msg) {

	vec_.clear();
	
	int i;
	while(1)
	{
		msg->read(&i, sizeof(int));

		if(i == -1) break;

		vec_.push_back(i);
	}
	
	
}
size_t glutpp::actor::addr::size() {

}


