#ifndef NEB_FIN_GFX_PHX_CORE_SHAPE_BASE_HPP
#define NEB_FIN_GFX_PHX_CORE_SHAPE_BASE_HPP

#include <neb/phx/core/shape/base.hpp>

#include <neb/gfx/core/shape/base.hpp>

#include <neb/fin/gfx_phx/core/shape/util/decl.hpp>

namespace neb {
	namespace fin {
		namespace gfx_phx {
			namespace core {
				namespace shape {
					class base:
						virtual public neb::gfx::core::shape::base,
						virtual public phx::core::shape::base
					{
						public:
							base(std::shared_ptr<neb::fin::gfx_phx::core::shape::util::parent> parent);
							virtual void				init();
							virtual void				release();
							virtual void				step(
									gal::etc::timestep const & ts);
					};
				}
			}
		}
	}
}

#endif

