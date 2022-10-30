#include<thread>
#include<iostream>
#include "thread_safe_stack.hpp"
#include "thread_safe_queue.hpp"
using namespace std;
void do_some_work() {
    puts("hello background");
}
class background_task {
public:
    void operator() () const {
        do_some_work();
    }
};
struct expire_func
{
    int& i_;
    expire_func(int& i) : i_(i) {}
    void operator() () {
        for (int j = 0; j < 100000; j++) {
            // printf("%d", i_);
        }
        std::cout<<"finish expire function"<<std::endl;
    }
    /* data */
};

struct expire_func_with_copy
{
    int i_;
    expire_func_with_copy(int i) : i_(i) {}
    void operator() () {
        for (int j = 0; j < 100000; j++) {
            printf("%d", i_);
        }
    }
    /* data */
};
class X {
    public:
    void hello() {
        puts("hello class X");
    }
};

class thread_guard {
 private:
    std::thread& thread_;
 public:
    explicit thread_guard(std::thread& t_) : thread_(t_){}
    ~thread_guard() {
        if (thread_.joinable()) {
            std::cout<<"thread guard work, join itself"<<std::endl;
            thread_.join();
        }
    }
    thread_guard(thread_guard const&) = delete;
    thread_guard& operator=(thread_guard const&) = delete;

};
void test_function_pararm(const char* name1, std::unique_ptr<X> p) {

    puts("two inputs name");
    p->hello();
    puts(name1);
    // int buffer = int(*buf);
}


void oops() {
    int local_value = 0;
    expire_func func(local_value);
    // std::thread thread1(func);
    // thread1.detach();

    expire_func_with_copy func2(local_value);
    std::thread thread2(func);
    thread_guard g(thread2);

    std::cout<<"doing something else"<<std::endl;
    // throw;
    std::unique_ptr<X> ptr1(new X);
    std::thread th3(test_function_pararm, "AB", std::move(ptr1));
    th3.detach();
    X my_x;
    std::thread th4(&X::hello, &my_x);
    th4.detach();
    // std::cout<<"doing something else2"<<std::endl;
    // thread2.detach();
}

void test_thread_safe_stack() {
    thread_safe_stack<int> my_stack;
	my_stack.push(5);
	cout<<my_stack.size()<<endl;
}

void prepare_data () {
    puts("prepare data");
}

std::unique_lock<std::mutex> get_lock() {
    extern std::mutex some_mutex;
    std::unique_lock<std::mutex> lk(some_mutex);
    prepare_data();
    return lk;
}

void process_data() {
    std::unique_lock<std::mutex> lk(get_lock());
    puts("do something on data");
}
class res {

};

std::once_flag init_flag;
std::shared_ptr<res> res_ptr;
void init_res() {
    puts("init once");
    res_ptr.reset(new res());
}

void other_try_init() {
    std::call_once(init_flag, init_res);
    puts("do sth");
}

ThreadSafeQueue<int> q;

void produce() {
    for (int i = 0; i <= 100; i++) {
        int data = i;
        q.push(data);
        // this_thread::sleep_for(10ms);
    }
}

void comsume() {
    while (true) {
        int value;
        q.wait_and_pop(value);
        std::cout<<"first queue value"<<value<<endl;
        if (value == 100) break;
        

    }
    std::cout<<"finished"<<std::endl;
}

void comsume2() {
    while (true) {
        int value;
        q.try_pop(value);
        std::cout<<"seoncd queue value"<<value<<endl;
        if (value == 100) break;

    }
    std::cout<<"finished second comsumer"<<std::endl;
}