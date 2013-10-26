#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_ACTOR_HPP__

#include <nebula/content/actor/admin/base.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace admin
			{
				/** \brief rigid dynamic
				*/
				class actor:
					public n34100::base
				{
					protected:
						/** \breif copy ctor
						*/
						actor( actor const & ) = default;
						/** \brief assignment
						*/
						actor&							operator=( actor const & ) = default;
						/** \brief ctor
						*/
						actor( n32100::base::shared_t );
					public:
						/** \brief dtor
						*/
						virtual ~actor();
						/** \brief init
						*/
						virtual	void						init();
						/** \brief shutdown
						*/
						virtual	void						shutdown();
						/** \brief update
						*/
						virtual	void						update();
						/** \brief step
						*/
						virtual	void						step( float );
						/** \brief render
						*/
						virtual	void						render( n23000::base::shared_t );
				};
			}
		}
	}
}

#endif


