#ifndef __BOX_KERNEL_FACTORY_HPP__
#define __BOX_KERNEL_FACTORY_HPP__

//#include <NebulaAPI.h>

#include <nebula/kernel/factory.hpp>

#include <box_client/ns.hpp>

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
				virtual std::shared_ptr<ker::module::module>		create(ker::module::type type )
				{
					switch ( type )
					{
						default:
							return nebula::kernel::factory::create( type );
							break;
					}
				}
		};
	}
}


#endif



