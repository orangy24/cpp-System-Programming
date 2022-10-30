#include <memory>
#include <mutex>
#include<stack>
template<typename T>
class thread_safe_stack {
 public:
    thread_safe_stack() {

    }
    thread_safe_stack(const thread_safe_stack& other) {
        std::lock_guard<std::mutex> lock(other.m);
        // data = other.data;
    }
    thread_safe_stack& operator=(const thread_safe_stack&) = delete;

    void push(T new_value) {
        std::lock_guard<std::mutex> lock(m);
        data.push(new_value);
    }
    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty()) throw;
        std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
        data.pop();
        return res;

        
    }
    void pop(T& value) {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty()) throw;
        value = data.top();
        data.pop();
    }
    bool empty() {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
    int size() {
        std::lock_guard<std::mutex> lock(m);
        return data.size();
    }
 private:
    std::mutex m;
    std::stack<T> data;

};

std::mutex some_mutex;