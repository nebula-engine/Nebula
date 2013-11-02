#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_BASE_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_BASE_HPP__

#include <jess/map.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace physics
			{
				/** \brief base
				 */
				class base
				{
					public:
						friend class n36000::base;
					protected:
						/** \brief copy ctor
						 */
						base( base const & ) = default;
						/** \brief assignment
						 */
						base&							operator=( base const & ) = default;
						/** \brief ctor
						 */
						base( std::shared_ptr<n34100::base> );
					public:
						/** \brief dtor
						 */
						~base();
						/** \brief init
						 */
						virtual	void						init();
						/** \brief shutdown
						 */
						virtual	void						shutdown();
						/** \brief update
						 */
						virtual	void						update();
						virtual void						refresh() = 0;
						/** \brief step
						 */
						virtual	void						step( float );
						/** \brief render
						 */
						virtual void						render( std::shared_ptr<n23000::base> );
						/** \brief create shapes
						 */
						virtual	void						create_shapes();
					protected:
						/** \brief parent
						 */
						std::weak_ptr<n34100::base>				parent_;
						/** \brief materials
						 */
						std::shared_ptr<n34200::material>			material_;
				};
			}
		}
	}
}


#endif








