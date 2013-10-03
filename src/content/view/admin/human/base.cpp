#include <jess/free.hpp>

#include <nebula/platform/platform/base.hpp>
#include <nebula/platform/window/base.hpp>
#include <nebula/platform/renderer/base.hpp>

#include <nebula/framework/app.hpp>
#include <nebula/content/base.hpp>
#include <nebula/content/universe/admin/base.hpp>
#include <nebula/content/scene/admin/base.hpp>

#include <nebula/content/camera.hpp>

#include <nebula/content/view/admin/human/base.hpp>

ncvah::base::base()
{
	
}
ncvah::base::~base()
{
	
}
void	ncvah::base::init( const boost::shared_ptr<nc_sc_a::base>& parent )
{
	ncva::base::init( parent );
	
	parent->parent_.lock()->parent_.lock()->parent_.lock()->get_platform()->create_window( window_ );
	
	camera_.create<nebula::content::camera>();
}
void	ncvah::base::update()
{
	render();
}
void	ncvah::base::render()
{
	jess::assertion( bool( window_ ) );
	
	boost::shared_ptr<npr::base> rnd = window_->renderer_;
	
	//if (!renderer) throw Except("renderer is null");
	//if (!m_camera) throw Except("m_camera is null");
	//if (!m_scene)  throw Except("m_scene is null");





	rnd->begin_render();

	camera_.pointer_->render( rnd );
	
	rnd->light();
	
	parent_.lock()->render( rnd );
	
	rnd->end_render();
	
}
void	ncvah::base::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	ncvah::base::create_camera()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	camera_.create<nc::camera>();
}


/*

void NbScene::render()
{
    if (!pxScene)
    {
        fatalError();
        return;
    }
    
    //Nbactor* actor;
    
    Pxactor** userBuffer = NULL;
    PxU32 bufferSize = 0;
    PxU32 nbactors = 0;
    
    if ( bufferSize = pxScene->getNbactors( NbactorTypes::eRENDER ) )
    {
        userBuffer = new Pxactor*[bufferSize];
        
        nbactors = pxScene->getactors( NbactorTypes::eRENDER, userBuffer, bufferSize, 0 );
        
        for ( int i = 0; i < nbactors; i++ )
        {
            switch( userBuffer[i]->getType() )
            {
                case eRIGID_STATIC:
                    render( reinterpret_cast<Pxrigid_actor>(userBuffer[i]) );
                    break;
                case eRIGID_DYNAMIC:
                    render( reinterpret_cast<Pxrigid_actor>(userBuffer[i]) );
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

void NbScene::render( Pxrigid_actor* pxrigid_actor )
{
    PxShape** userBuffer = NULL;
    PxU32 bufferSize = 0;
    PxU32 nbShapes = 0;
    
    if ( bufferSize = pxrigid_actor->getNbShapes() )
    {
        userBuffer = new PxShape*[bufferSize];
        
        nbShapes = pxrigid_actor->getShapes( userBuffer, bufferSize, 0 );
        
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



