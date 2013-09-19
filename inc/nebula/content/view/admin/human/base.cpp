
#include <nebula/platform/platform/base.hpp>

#include <nebula/platform/window/base.hpp>

#include <Platform/Renderer/PL_RE_Renderer.h>

#include <content/Scene/Admin/CO_SC_AD_Scene.h>

#include <content/CO_Camera.h>

#include <content/View/Admin/Human/CO_VI_AD_HU_View.h>

		CO_VI_AD_HU_View::View() {
	
}
		CO_VI_AD_HU_View::~View() {
	
}
void	CO_VI_AD_HU_View::VInit( Void* data ) {
	PRINTSIG;
	CO_VI_AD_View::VInit( data );

	m_app->GetPlatform()->VCreateWindow( m_window );
	
	m_camera = new Camera();
}
void	CO_VI_AD_HU_View::VUpdate() {
	Render();
}
void	CO_VI_AD_HU_View::Render() {
	//PRINTSIG;
	
	if ( !m_window ) throw Except("m_window is null");

	PL_RE_Renderer* renderer = m_window->GetRender();
	
	if (!renderer) throw Except("renderer is null");
	if (!m_camera) throw Except("m_camera is null");
	if (!m_scene)  throw Except("m_scene is null");



	AR_Render r;
	r.renderer = renderer;





	renderer->VBeginRender();

	m_camera->Render( &r );

	renderer->VLight();

	m_scene->Render( &r );

	renderer->VEndRender();
	
}



/*

void NbScene::render()
{
    if (!pxScene)
    {
        fatalError();
        return;
    }
    
    //NbActor* actor;
    
    PxActor** userBuffer = NULL;
    PxU32 bufferSize = 0;
    PxU32 nbActors = 0;
    
    if ( bufferSize = pxScene->getNbActors( NbActorTypes::eRENDER ) )
    {
        userBuffer = new PxActor*[bufferSize];
        
        nbActors = pxScene->getActors( NbActorTypes::eRENDER, userBuffer, bufferSize, 0 );
        
        for ( int i = 0; i < nbActors; i++ )
        {
            switch( userBuffer[i]->getType() )
            {
                case eRIGID_STATIC:
                    render( reinterpret_cast<PxRigidActor>(userBuffer[i]) );
                    break;
                case eRIGID_DYNAMIC:
                    render( reinterpret_cast<PxRigidActor>(userBuffer[i]) );
                    break;
                case ePARTICLE_SYSTEM:
                    render( reinterpret_cast<PxParticleSystem>(userBuffer[i]) );
                    break;
                case ePARTICLE_FLUID:
                    render( reinterpret_cast<PxParticleFluid>(userBuffer[i]) );
                    break;
                case eARTICULATION_LINK:
                    render( reinterpret_cast<PxArticulationLink>(userBuffer[i]) );
                    break;
                case eCLOTH:
                    render( reinterpret_cast<PxCloth>(userBuffer[i]) );
                    break;
                default:
                    break;
            }
        }
    }
}

void NbScene::render( PxRigidActor* pxRigidActor )
{
    PxShape** userBuffer = NULL;
    PxU32 bufferSize = 0;
    PxU32 nbShapes = 0;
    
    if ( bufferSize = pxRigidActor->getNbShapes() )
    {
        userBuffer = new PxShape*[bufferSize];
        
        nbShapes = pxRigidActor->getShapes( userBuffer, bufferSize, 0 );
        
        for ( int i = 0; i < nbShapes; i++ )
        {
            switch( userBuffer[i]->getGeometryType() )
            {
                case eSPHERE:
                    render( userBuffer[i]->getGeometry().sphere(), userBuffer[i] );
                    break;
                case ePLANE:
                    render( userBuffer[i]->getGeometry().plane(), userBuffer[i] );
                    break;
                case eCAPSULE:
                    render( userBuffer[i]->getGeometry().capsule(), userBuffer[i] );
                    break;
                case eBOX:
                    render( userBuffer[i]->getGeometry().box(), userBuffer[i] );
                    break;
                case eCONVEXMESH:
                    render( userBuffer[i]->getGeometry().convexMesh(), userBuffer[i] );
                    break;
                case eTRIANGLEMESH:
                    render( userBuffer[i]->getGeometry().triangleMesh(), userBuffer[i] );
                    break;
                case eHEIGHTFIELD:
                    render( userBuffer[i]->getGeometry().heightField(), userBuffer[i] );
                    break;
                default:
                    break;
            }
        }
    }
}



void NbScene::render( PxParticleSystem* pxParticleSystem )
{
    PxParticleReadData* pxParticleReadData = pxParticleSystem->lockParticleReadData();
    
    
}

void NbScene::render( PxParticleFluid* pxParticleFluid )
{
    
}

void NbScene::render( PxArticulationLink* pxArticulationLink )
{
    
}

void NbScene::render( PxCloth* pxCloth )
{
    
}




// render geometry




void NbScene::render( PxSphereGeometry* PxSphereGeometry, PxShape* pxShape )
{
    
}

void NbScene::render( PxPlaneGeometry* PxPlaneGeometry, PxShape* pxShape )
{
    
}

void NbScene::render( PxCapsuleGeometry* PxCapsuleGeometry, PxShape* pxShape )
{
    
}

void NbScene::render( PxBoxGeometry* PxBoxGeometry, PxShape* pxShape )
{
    
}

void NbScene::render( PxConvexMeshGeometry* PxConvexMeshGeometry, PxShape* pxShape )
{
    
}

void NbScene::render( PxTriangleMeshGeometry* PxTriangleMeshGeometry, PxShape* pxShape )
{
    
}

void NbScene::render( PxHeightFieldGeometry* PxHeightFieldGeometry, PxShape* pxShape )
{
    
}

*/



