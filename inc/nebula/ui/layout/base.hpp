#ifndef __NEBULA_UI_LAYOUT_BASE_HPP__
#define __NEBULA_UI_LAYOUT_BASE_HPP__

#include <jess/map.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace ui
	{
		namespace layout
		{
			/// base
			class base
			{
				public:
					/// init
					virtual void			init();
					/// load xml
					void				load_xml( std::string );
					/// render
					void				render( jess::shared_ptr<n23000::base> );

					/// objects
					jess::map<ui::object::base>	objects_;
			};
		}
	}
}

#endif
