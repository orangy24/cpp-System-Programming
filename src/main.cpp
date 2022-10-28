#include <iostream>
#include <shared_pointer.hpp>
#include <shape.hpp>
int main(int argc, char *argv[])
{
	std::cout << "Hello world!" << std::endl;
	// int* p = new int(5);
	// shared_pointer<int> ptr = shared_pointer(p);
	shape* item = new shape();
	shape* item2 = new shape();
	shape* item3 = new shape();
	smart_pointer<shape> shape_ptr1{item};
	/* unqiue pointer
	// shared_pointer<shape> shape_ptr2 = shape_ptr1;  error, copy constructor is implicit delete
	// shared_pointer<shape> shape_ptr2{shape_ptr1}; error
	// shape_ptr2 = std::move(shape_ptr1);
	*/

	smart_pointer<shape> shape_ptr2 = std::move(shape_ptr1);
	// shape_ptr1->get_shape();
	// shape_ptr2->get_shape();
	smart_pointer<shape> shape_ptr3{std::move(shape_ptr2)};
	smart_pointer<shape> shape_ptr4 = smart_pointer<shape>(item2);
	// shape_ptr1{}
	// ptr->get();
	shared_ptr<circle> ptr1(new circle());
	std::cout<<"ptr 1 reference count"<<ptr1.use_count()<<std::endl;

	shared_ptr<circle> ptr2 = ptr1;
	std::cout<<"ptr 1 reference count"<<ptr1.use_count()<<std::endl;
	// other type
	{
	shared_ptr<shape> ptr3 = ptr1;
	std::cout<<"ptr 1 reference count"<<ptr3.use_count()<<std::endl;
	}
	std::cout<<"ptr 1 reference count"<<ptr1.use_count()<<std::endl;
}