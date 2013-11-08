#ifndef __NEBULA_KERNEL_FACTORY_HPP__
#define __NEBULA_KERNEL_FACTORY_HPP__

#include <ker/factory.hpp>

#include <nebula/framework/app.hpp>
#ifdef __LIN__
#include <nebula/platform/platform/lin/base.hpp>
#elif defined(__WIN__)
#include <nebula/platform/platform/win/base.hpp>
#endif
#include <nebula/platform/window/lin/base.hpp>
#include <nebula/content/base.hpp>
#include <nebula/content/camera.hpp>


namespace nebula
{
	namespace kernel
	{
		/** \brief
		 * factory
		 */
		class factory:
			public ker::factory
		{
			public:
				/** \brief ctor
				*/
				factory()
				{}
				/** \brief dtor
				*/
				virtual ~factory()
				{}
				/** \brief create
				*/
				virtual std::shared_ptr<ker::module::module >		create( std::shared_ptr<ker::module::desc> desc )
				{
					NEB_LOG_FUNC;
					NEB_ASSERT( desc );

					std::shared_ptr<ker::module::module> mod;

					nebula::kernel::module::type type = (nebula::kernel::module::type)desc->type_;

					switch ( type )
					{
						case nebula::kernel::module::type::N10000_APP:
							mod.reset( new n10000::app );
							break;
#ifdef __LIN__
						case nebula::kernel::module::type::N21100_BASE:
							mod.reset( new n21100::base );
							break;
#elif defined(__WIN__)
						case nebula::kernel::module::type::N21200_BASE:
							mod.reset( new n21200::base );
							break;
#endif
						case nebula::kernel::module::type::N22100_BASE:
							mod.reset( new n22100::base );
							break;

						case nebula::kernel::module::type::N30000_BASE:
							mod.reset( new n30000::base );
							break;
						case nebula::kernel::module::type::N30000_CAMERA:
							mod.reset( new n30000::camera );
							break;
						default:
							mod = ker::factory::create( desc );
							break;
					}
					return mod;
				}
		};
	}
}


#endif



