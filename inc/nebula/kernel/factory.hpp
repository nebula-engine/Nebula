#ifndef __NEBULA_KERNEL_FACTORY_HPP__
#define __NEBULA_KERNEL_FACTORY_HPP__

#include <ker/factory.hpp>

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
				virtual std::shared_ptr<ker::module::module >		create( ker::module::type type )
				{
					switch ( type )
					{
						default:
							return kernel::factory::create( type );
							break;
					}
				}
		};
	}
}


#endif



