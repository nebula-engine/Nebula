
#include <iostream>

#include <neb/gfx/util/array_continuous.hpp>

template<typename T> void print_array(T* t, int size)
{
	for(int i = 0; i < size; i++) std::cout << t[i] << " ";
	std::cout << std::endl;
}

template<typename... T> void print_info(std::shared_ptr< neb::gfx::array_continuous<T...> >& arr)
{
	std::cout
		<< "size         " << arr->size() << std::endl
		<< "update begin " << arr->update_begin_ << std::endl
		<< "update end   " << arr->update_end_ << std::endl;


}



int main() {

	typedef neb::gfx::array_continuous<int> arr_t;

	std::shared_ptr<arr_t> arr(new arr_t);

	print_info(arr);

	arr->alloc(16);

	print_info(arr);

	std::shared_ptr<arr_t::slot> s1;

	{
		auto s0 = arr->reg(0);

		print_info(arr);

		arr->reset_update();

		print_info(arr);

		s1 = arr->reg(1);

		print_info(arr);

		print_array(arr->get<0,int>(), arr->size());

	}


	arr->update_slots();

	print_info(arr);
	
	print_array(arr->get<0,int>(), arr->size());
}


