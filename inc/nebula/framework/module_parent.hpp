#ifndef __NEBULA_FRAMEWORK_KERNEL_HPP__
#define __NEBULA_FRAMEWORK_KERNEL_HPP__

namespace nebula { namespace framework {
	/** \brief module parent
	*/
	class module_parent
	{
		protected:
			/** \brief request
			*/
			std::shared_ptr<n10000::module>		request( std::shared_ptr<n10000::module>, std::shared_ptr<n10000::module_desc> );
			/** \brief modules
			*/
			std::vector<n10000::module>		modules_;
	};
}}

#endif
