#ifndef __NEBULA_FRAMEWORK_MODULE_HPP__
#define __NEBULA_FRAMEWORK_MODULE_HPP__

namespace nebula { namespace framework {
	/** \brief module
	*/
	class module:
		public n10000::module_parent
	{
		public:
			typedef std::weak_ptr<n10000::module_parent> parent_t;
			/** \brief type
			*/
			enum type
			{
				invalid = 0
			};
		protected:
			/** \brief ctor
			*/
			module( parent_t );
			/** \brief dtor
			*/
			virtual ~module();
			/** \brief parent
			*/
			parent_t	parent_;
	};
}}

#endif
