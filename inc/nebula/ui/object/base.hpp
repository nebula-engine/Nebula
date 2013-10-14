#ifndef __NEBULA_UI_OBJECT_BASE_HPP__
#define __NEBULA_UI_OBJECT_BASE_HPP__

#include <jess/shared_ptr.hpp>

#include <nebula/define.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace ui
	{
		namespace object
		{
			/** \brief base
			*/
			class base
			{
				public:
					/// render
					virtual void						render( jess::shared_ptr<n23000::base> ) = 0;
					/// x
					unsigned int						x_;
					/// y
					unsigned int						y_;
					/// w
					unsigned int						w_;
					/// h
					unsigned int						h_;
					/** \brief active
					*/
					bool							active_;
					///@name signal
					///@{
					/***/
					/// key down
					std::shared_ptr< jess::signal::connection<int> >	connection_key_down_;
					/// key up
					std::shared_ptr< jess::signal::connection<int> >	connection_key_up_;
					/// key_down
					virtual bool						key_down( int ) = 0;
					/// key_up
					virtual bool						key_up( int ) = 0;
					/** \brief key down mask
					*/
					int							key_down_mask_;
					/** \brief key up mask
					*/
					int							key_up_mask_;
					///@}
			};
		}
	}
}


#endif

