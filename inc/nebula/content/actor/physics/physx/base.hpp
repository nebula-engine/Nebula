#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_BASE_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_BASE_HPP__




namespace nebula
{
namespace content
{
	namespace actor
	{
		namespace admin
		{
			/// rigid dynamic
			class base:
				public nebula::content::actor::admin::rigid_body
			{
			public:
				///@name ctor and dtor
				///@{
				// Ctor
				rigid_body();
				/// Copy Ctor
				rigid_body(const rigid_body&);
				/// Dtor
				~rigid_body();
				///@}

				///@name operator
				///@{
				/// assignment
				rigid_body&								operator=(const rigid_body&);
				///@}

				

				/// init
				virtual	void								init(const boost::shared_ptr<nebula::content::scene::admin::base>&);
				/// shutdown
				virtual	void								shutdown();
				/// update
				virtual	void								update();
				/// step
				virtual	void								step();
				/// render
				virtual	void								render(const boost::shared_ptr<nebula::platform::renderer::base>&);
				
				
				
				
				/// create shapes
				virtual	void								create_shape();
			};
		};
	};
};

#endif








