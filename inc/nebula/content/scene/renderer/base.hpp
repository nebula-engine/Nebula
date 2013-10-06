#ifndef _SCENE_H
#define _SCENE_H

#include <time.h>
#include <stdio.h>
#include <memory>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace scene
		{
			namespace renderer
			{
				/// base
				class base
				{
				public:
					/// ctor
					base() {}
					/// copy ctor
					base( base const & ) {}
					/// dtor
					virtual	~base() {}
					/// assignment
					base&						operator=( const base& scene ) { return *this; }
					
					///@name standard functions
					///@{
					/// Initialize
					virtual	void					init( jess::shared_ptr<nc_sc_a::base> );
					/// ShutDown
					virtual	void					shutdown();
					/// Update
					virtual	void					update();
					/// step
					void						step( float dt );
					/// render
					void						render( jess::shared_ptr<npr::base> );
					///@}

					/*
					///@name create functions
					///@{
					/// RigidDynamicBox
					void						CreateRigidDynamicBox( CoCO_AC_AD_RigidDynamicBox*& rigidDynamicBox );
					/// CharacterController
					void						CreateController( CoCO_AC_AD_Controller*& controller );
					///@}



					///@name register functions
					///@{
					/// RigidDynamic
					void							RegisterRigidDynamic( ::CO_AC_AD_RigidDynamic* rigidDynamic );
					///@}


					///@name Fetch
					///@{
					/// %PhysicsScene
					Physics::PhysicsScene*	GetPhysicsScene() { return m_physicsScene; }
					///@}


					///@name MapPtr ActorBase operations
					///@{
					/// render ActorBase objects
					int						ActorBaseRender_For( Platform::Renderer::Renderer* render );
					/// step ActorBase objects
					int						ActorBaseStep_For( float dt );
					///@}

					*/

					///@name Individual ActorBase operations
					///@{
					/// step ActorBase
					//void					ActorBaseStep( ::CO_AC_AD_ActorBase* actorBase );
					/**
					 * Render \a actorBase using \a render
					 * @param [in] actorBase ActorBase object to render
					 * @param [in] render Render object to use
					 */
					//void					ActorBaseRender( ::CO_AC_AD_ActorBase* actorBase, Platform::Renderer::Renderer* render );
					///@}



					///@name individual view functions
					///@{
					/// update view
					//void					ViewUpdate( View* view );
					///@}



					/**
					 * Create a ViewHuman object
					 @param [out] viewHuman reference to pointer to new object
					 */
					//void					CreateViewHuman( ::Content::ViewHuman*& viewHuman );
					/*
					protected:
					/// global app
					FR_App*		m_app;


					///@name Children
					///@{
					/// %Physics %CO_SC_AD_Scene
					Physics::PhysicsScene*	m_physicsScene;
					///@}



					///@name maps
					///@{
					/// ActorBase
					MapPtr<CO_AC_AD_ActorBase>	m_actorBase;
					/// View
					MapPtr<View>			m_view;
					///@}



					///@name time
					///@{
					/// time since last step
					float	m_accumulator;
					/// step size
					float	m_stepSize;
					/// time of last update
					time_t	m_last;
					///@}
				
					*/
				};
			}
		}
	}
}

/*
/// functionoid to step ActorBase
class Funct_ActorBase_Step: public Funct<CO_AC_AD_ActorBase,CO_SC_AD_Scene> {
public:
/// Constructor
Funct_ActorBase_Step( CO_SC_AD_Scene* scene ): Funct<CO_AC_AD_ActorBase,CO_SC_AD_Scene>(scene) {}
/// doit
void	doit( CO_AC_AD_ActorBase* actorBase );
};

/// functionoid to render ActorBase
class Funct_ActorBase_Render: public Funct<CO_AC_AD_ActorBase,CO_SC_AD_Scene> {
public:
/// Constructor
Funct_ActorBase_Render( CO_SC_AD_Scene* scene, Platform::Renderer::Renderer* render ): Funct<CO_AC_AD_ActorBase,CO_SC_AD_Scene>(scene), m_render(render) {}
/// doit
void	doit( CO_AC_AD_ActorBase* actorBase );

/// renderer
Platform::Renderer::Renderer*	m_render;
};

/// functionoid to update View
class Funct_View_Update: public Funct<Content::View,CO_SC_AD_Scene> {
public:
/// Constructor
Funct_View_Update( CO_SC_AD_Scene* scene ): Funct<Content::View,CO_SC_AD_Scene>(scene) {}
/// doit
void	doit( Content::View* actorBase );
};
 */

#endif












