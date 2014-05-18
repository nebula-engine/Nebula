#ifndef NEBULA_APP_BASE_FACTORY_HH
#define NEBULA_APP_BASE_FACTORY_HH

#include <memory>

#include <Nebula/Types.hh>

#include <Nebula/Util/Factory.hh>

#include <Nebula/Graphics/Types.hh>

#include <Nebula/Scene/Util/Types.hh>
#include <Nebula/Actor/Util/Types.hh>
#include <Nebula/Shape/Util/Types.hh>


namespace Neb {
	namespace App {
		class BaseFactory {
			public:
				template<typename T> using pointer = std::shared_ptr<T>;

				typedef pointer< Neb::Factory<Neb::Graphics::GUI::Object::object> >		GUI_Object;
				typedef pointer< Neb::Factory<Neb::Actor::Base> >				Factory_Actor_Base;
				typedef pointer< Neb::Factory<Neb::Shape::Base> >				Shape_Base;
				typedef pointer< Neb::Factory<Neb::Light::light> >				Light_Base;
				typedef pointer< Neb::Factory<Neb::Graphics::Window::Base> >			Window_Base;
				typedef pointer< Neb::Factory<Neb::Scene::Base> >				Scene_Base;
				
			public:
				virtual ~BaseFactory() {}

				static void								init();
				
				
				template<class T> std::shared_ptr< Neb::Factory<T> >		getFactoryDefault();
				
				static BaseFactory_s						global();
				
				/** @brief Factories */
				struct {

					GUI_Object			gui_object_;
					Factory_Actor_Base		actor_base_;
					Shape_Base			shape_base_;
					Light_Base			light_base_;
					Window_Base			window_base_;
					Scene_Base			scene_base_;
				} factories_;
			protected:
				/** %brief global app object */
				static Neb::App::BaseFactory_s					g_app_;

		};

		template<> std::shared_ptr< Neb::Factory<Neb::Actor::Base> >	BaseFactory::getFactoryDefault<Neb::Actor::Base>() {
			return factories_.actor_base_;
		}
	}
}

#endif



