#ifndef NEB_GFX_ARRAY_SLOT_HPP
#define NEB_GFX_ARRAY_SLOT_HPP

#include <iostream>
#include <vector>
#include <memory>

#include <neb/gfx/util/array_basic_double_buffered.hpp>

namespace neb { namespace gfx {

	template<class ARR> struct slot
	{
		slot(std::shared_ptr<ARR> array, int index):
			array_(array),
			index_(index),
			count_(0) {}
		template<int I, typename U> void	set(U const & u) {
			auto arr = array_.lock();
			if(arr) {
				//std::cout << __PRETTY_FUNCTION__ << " index=" << index_ << std::endl;
				arr->set<I>(index_, u);
				count_++;
			}
		}
		std::weak_ptr< ARR >		array_;
		int				index_;
		int				count_;

	};
}}

#endif

