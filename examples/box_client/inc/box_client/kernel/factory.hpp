#ifndef __BOX_KERNEL_FACTORY_HPP__
#define __BOX_KERNEL_FACTORY_HPP__

#include <nebula/kernel/factory.hpp>

#include <box_client/ns.hpp>
#include <box_client/kernel/module/type.hpp>

#include <box_client/framework/app.hpp>

#include <box_client/content/universe/admin/base.hpp>
#include <box_client/content/scene/admin/base.hpp>
#include <box_client/content/view/admin/base.hpp>

namespace box_client
{
	namespace kernel
	{
		/** \brief factory
		*/
		class factory:
			public nebula::kernel::factory
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
				virtual std::shared_ptr<ker::module::module>		create( std::shared_ptr<ker::module::desc> desc )
				{
					NEB_LOG_FUNC;
					NEB_ASSERT( desc );

					std::shared_ptr<ker::module::module> mod;

					switch ( desc->type_ )
					{
						case box_client::kernel::module::type::BC10000_APP:
							mod.reset( new bc10000::app );
							break;
						case box_client::kernel::module::type::BC31100_BASE:
							mod.reset( new bc31100::base );
							break;
						case box_client::kernel::module::type::BC32100_BASE:
							mod.reset( new bc32100::base );
							break;
						case box_client::kernel::module::type::BC33100_BASE:
							mod.reset( new bc33100::base );
							break;
						default:
							mod = nebula::kernel::factory::create( desc );
							break;
					}

					return mod;
				}
		};
	}
}


#endif



