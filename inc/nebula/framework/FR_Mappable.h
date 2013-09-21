#ifndef _FRAMEWORK_MAPPABLE_H
#define _FRAMEWORK_MAPPABLE_H

#include <utilities/Types/Utilities.h>

#include <core/Core.h>

namespace Framework {
	/// %Mappable
	class Mappable {
		
	public:
		friend class MapPtr<CO_UN_AD_Universe>;
		friend class MapPtr<CO_SC_AD_Scene>;
		friend class MapPtr<CO_VI_AD_View>;
		friend class MapPtr<CO_AC_AD_ActorBase>;
		friend class MapPtr<CO_AC_PH_Material>;
		friend class MapPtr<CO_SH_AD_Shape>;
		friend class MapPtr<PL_WI_Window>;

		/// Ctor
			Mappable(): m_no(-1) {
		}
	protected:
		/// Identification Number
		int	m_no;
	};
}

#endif








