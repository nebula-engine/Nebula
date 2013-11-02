#ifndef _PLATFORM_WINDOW_WINDOW_H
#define _PLATFORM_WINDOW_WINDOW_H

#include <map>
#include <memory>

#include <jess/signal/signal.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace platform
	{
		namespace window
		{
			/// base
			class base:
				public std::enable_shared_from_this<n22000::base>
			{
				public:
					///@name Constructor and Destructor
					///@{
					/// Constructor
					base();
					/// Destructor
					virtual	~base();
					///@}



					///@name Initialization and ShutDown
					///{
					/// initialize
					virtual	void					init( std::shared_ptr<n21000::base> );
					/// shutdown
					virtual	void					shutdown();
					/// update
					virtual void					update();
					///}

					virtual int					lookup_key( int );
					/** \brief parent
					 */
					std::weak_ptr<n21000::base>			parent_;
					int						no_;
					bool						m_hasFocus;
					/** \brief keys
					 */
					std::map<int,int>				keys_;
					///@name signals
					///@{
					/// key down
					jess::signal::signal<int>			sig_key_down_;
					/// key up
					jess::signal::signal<int>			sig_key_up_;
					/// pointer motion
					jess::signal::signal<int,int>			sig_pointer_motion_;
					///@}
					//protected:
					unsigned int					width_;
					unsigned int					height_;
					/// focus
					bool						has_focus_;
					/// x
					int						center_x_;
					/// y
					int						center_y_;
					/** \brief renderer
					 */
					std::shared_ptr<n23000::base>			renderer_;
			};
		}
	}
}


#endif














