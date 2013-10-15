#ifndef __NEBULA_FRAMEWORK_COMMUNICATION_MESSAGE_DATA_H
#define __FRAMEWORK_COMMUNICATION_MESSAGE_DATA_H

#include <memory>
#include <queue>

#include <nebula/asio/message.hpp>

namespace nebula
{
	namespace asio
	{
		namespace data
		{
			/** \brief types
			*/
			struct types
			{
				enum
				{
					invalid = 0,
					key_event,
					pointer_motion,
					flag,
					controller_state
				};
			};
			/** \brief data
			*/
			struct base
			{
				int	type_;
			};
			/** \brief key event
			*/
			struct key_event:
				n40000::data::base
			{
				/** key
				*/
				int key_;
				/** window
				*/
				int window_;
			};
			/** \brief pointer motion
			*/
			struct pointer_motion:
				n40000::data::base
			{
				/// x
				int x_;
				/// y
				int y_;
			};
			/** \brief %flag
			*/
			struct flag:
				n40000::data::base
			{
				/** %flag
				*/
				unsigned int	flag_;
			};
			/** \brief %controller state
			*/
			struct controller_state:
				n40000::data::base
			{
				/** %flag
				*/
				unsigned int	flag_;
				/** %pitch
				*/
				float		pitch_;
				/** %yaw
				*/
				float		yaw_;
			};
		}
	}
}


#endif



