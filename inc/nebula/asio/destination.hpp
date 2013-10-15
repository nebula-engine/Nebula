#ifndef _FRAMEWORK_COMMUNICATION_MESSAGE_H
#define _FRAMEWORK_COMMUNICATION_MESSAGE_H

#include <memory>
#include <queue>

#include <utilities/Types/Utilities.h>

#include <framework/Communication/Message/FR_COM_MSG_Data.h>

using namespace std;

namespace Framework
{
	namespace Communication
	{
		namespace Message
		{
			/// Destination Type
			struct DestType
			{
				/// enum
				enum e
				{
					eCO_AC_AD_ACTORBASE
				};
			};
			
			/// Address
			struct Addr_CO_AC_AD_ActorBase
			{
				/// %Universe no
				int universe;
				/// %Scene no
				int scene;
				/// %ActorBase no
				int actor_base;
			};

			/// Destination
			/** 
			Data used to route the %Message to its final destination.
			If icomm is NULL, addr is used instead.
			If the message is sent over a network, the sending object is responible for setting icomm to NULL.
			*/
			struct Dest
			{
				/// Destination Type
				int type;
				
				/// %IComm pointer
				FR_COM_IComm* icomm;

				/// Address
				union
				{
					Addr_CO_AC_AD_ActorBase		co_ac_ad_actor_base;
				} addr;
			};
		}
	}
}



#endif



