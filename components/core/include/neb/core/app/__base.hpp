#ifndef __NEBULA_APP___BASE_H__
#define __NEBULA_APP___BASE_H__

#include <boost/asio/io_service.hpp>

#include <gal/etc/timestep.hpp>

#include <gal/console/console.hpp>

#include <neb/core/app/util/Flag.hh>

<<<<<<< HEAD
using namespace std;
=======
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

namespace neb {
	namespace core {
		namespace app {
			/** @brief %base */
			class __base {
				public:
					typedef gal::console::temp<
						gal::console::frontend::store,
						gal::console::backend::python> console_type;
<<<<<<< HEAD
					virtual ~__base() {};
				protected:
					void							__init();
				public:
					static std::shared_ptr<neb::core::app::__base>		global();
				public:
					boost::asio::io_service					ios_;
					neb::core::app::util::flag				flag_;
					static ::std::shared_ptr<neb::core::app::__base>	g_app_;
					gal::etc::timestep					ts_;
					shared_ptr<console_type>				console_;
					
					std::string						share_dir_;
=======
					virtual ~__base();
				protected:
					virtual void						init();
				public:
					static std::shared_ptr<neb::core::app::__base>		global();
					static bool						is_valid();
				public:
					boost::asio::io_service					ios_;
					neb::core::app::util::flag				flag_;
					gal::etc::timestep					ts_;
					std::shared_ptr<console_type>				console_;
					
					std::string						share_dir_;

					static std::shared_ptr<neb::core::app::__base>		g_app_;
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
			};
		}
	}
}

#endif



