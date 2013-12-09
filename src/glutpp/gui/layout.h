#ifndef __NEBULA_UI_LAYOUT_BASE_HPP__
#define __NEBULA_UI_LAYOUT_BASE_HPP__

#include <memory>
#include <map>

#include <glutpp/gui/object/object.h>

namespace glutpp
{
namespace gui
{
	class layout
	{
		public:
			/// init
			virtual void			init();
			/// load xml
			void							load_xml( std::string );
			/// render
			void							Display();

			/// objects
			std::map<__s32,std::shared_ptr<GUL::object::object> >	objects_;
	};
}
}

#endif
