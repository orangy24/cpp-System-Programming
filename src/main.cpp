#include <iostream>
#include <shared_pointer.hpp>
#include <shape.hpp>
#include <thread>
#include <chrono>
#include <mutex>
#include <thread_manage.hpp>

using namespace std;
mutex output_lock;
void func(const char* name) {
	std::this_thread::sleep_for(100ms);
	// lock_guard<mutex> lk{output_lock};
	cout<<"i am a thread"<<name<<endl;

}
int main(int argc, char *argv[])
{

	oops();
	background_task f;
	std::thread my_thread(f);
	std::thread my_thread2([](){
		do_some_work();
	});

	my_thread.join();
	my_thread2.join();


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


	test_thread_safe_stack();
	process_data();

	other_try_init();
	other_try_init();

	std::thread t1(produce);
	// produce();

	// thread t1
	std::thread t3(comsume);
	std::thread t2(comsume);
	

	t1.detach();
	t2.detach();
	t3.detach();
}