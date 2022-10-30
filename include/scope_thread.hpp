#include<thread>
class scope_thread {
 public:
    template <typename... Arg>
    scope_thread(Arg&&... arg) 
    : thread_(std::forward<Arg>(arg)...) 
    {}

    scope_thread( scope_thread&& other) : thread_( std::move(other.thread_)) {}
    scope_thread(const scope_thread& ) = delete;
    ~scope_thread() {
        if (thread_.joinable()) {
            thread_.join();
        }
    }
 private:
 std::thread thread_;
};