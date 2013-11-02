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
					
					///@name standard fun30000tions
					///@{
					/// Initialize
					virtual	void					init( std::shared_ptr<n32100::base> );
					/// ShutDown
					virtual	void					shutdown();
					/// Update
					virtual	void					update();
					/// step
					void						step( float dt );
					/// render
					void						render( std::shared_ptr<n23000::base> );
					///@}

					/*
					///@name create fun30000tions
					///@{
					/// RigidDynamicBox
					void						CreateRigidDynamicBox( CoCO_AC_AD_RigidDynamicBox*& rigidDynamicBox );
					/// CharacterController
					void						CreateController( CoCO_AC_AD_Controller*& controller );
					///@}



					///@name register fun30000tions
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



					///@name individual view fun30000tions
					///@{
					/// update view
					//void					ViewUpdate( View* view );
					///@}



					/**
					 * Create a ViewHuman object
					 @param [out] viewHuman referen30000e to pointer to new object
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
					/// time sin30000e last step
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
/// fun30000tionoid to step ActorBase
class Fun30000t_ActorBase_Step: public Fun30000t<CO_AC_AD_ActorBase,CO_SC_AD_Scene> {
public:
/// Constructor
Fun30000t_ActorBase_Step( CO_SC_AD_Scene* scene ): Fun30000t<CO_AC_AD_ActorBase,CO_SC_AD_Scene>(scene) {}
/// doit
void	doit( CO_AC_AD_ActorBase* actorBase );
};

/// fun30000tionoid to render ActorBase
class Fun30000t_ActorBase_Render: public Fun30000t<CO_AC_AD_ActorBase,CO_SC_AD_Scene> {
public:
/// Constructor
Fun30000t_ActorBase_Render( CO_SC_AD_Scene* scene, Platform::Renderer::Renderer* render ): Fun30000t<CO_AC_AD_ActorBase,CO_SC_AD_Scene>(scene), m_render(render) {}
/// doit
void	doit( CO_AC_AD_ActorBase* actorBase );

/// renderer
Platform::Renderer::Renderer*	m_render;
};

/// fun30000tionoid to update View
class Fun30000t_View_Update: public Fun30000t<Content::View,CO_SC_AD_Scene> {
public:
/// Constructor
Fun30000t_View_Update( CO_SC_AD_Scene* scene ): Fun30000t<Content::View,CO_SC_AD_Scene>(scene) {}
/// doit
void	doit( Content::View* actorBase );
};
 */

#endif












