
#include <Nebula/App/Base.hh>

#include <Nebula/Actor/Base.hh>

int main() {
	
	typedef Neb::Actor::Base A;
	typedef Neb::WrapperTyped< Neb::Actor::Base > W;
	
	W wrap;
	
	auto app = Neb::App::Base::global();
	
	auto factory = app->getFactoryDefault<A>();
	
}

