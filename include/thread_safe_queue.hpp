#include<mutex>
#include<queue>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue {
 private:
    mutable std::mutex m_;
    std::condition_variable cv_;
    std::queue<T> data_queue_;
 public:
    ThreadSafeQueue() {}
    ThreadSafeQueue(ThreadSafeQueue const& other) {
        std::lock_guard<std::mutex> lk(other.m_);
        data_queue_ = other.data_queue_;
    }
    void push(T new_value) {
        std::lock_guard<std::mutex> lk(m_);
        data_queue_.push(new_value);
        cv_.notify_all();
    }

    bool try_pop(T& value) {
        std::unique_lock<std::mutex> lk(m_);
        if (data_queue_.empty()) return false;
        value = data_queue_.front();
        data_queue_.pop();
        return true;
    }

    std::shared_ptr<T> try_pop() {
        std::unique_lock<std::mutex> lk(m_);
        if (data_queue_.empty()) return std::shared_ptr<T>();
        std::shared_ptr<T> res(std::make_shared<T>(data_queue_.front()));
        data_queue_.pop();
        return res;
    }
    
    //option2, user define var
    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lk(m_);
        cv_.wait(lk,[&] {return !data_queue_.empty();} );

        value = std::move(data_queue_.front());
        data_queue_.pop();
        // return true;
    }
    //option3 return smart ptr
    std::shared_ptr<T> wait_and_pop() {
        std::unique_lock<std::mutex> lk(m_);
        cv_.wait(lk, [this]{return !data_queue_.empty();});
        std::shared_ptr<T> res(std::make_shared<T>(data_queue_.front()));
        data_queue_.pop();
        return res;
    }

    bool empty() {
        std::lock_guard<std::mutex> lk(m_);
        return data_queue_.size();
    }
};