#include<iostream>

template<typename T>
class smart_pointer
{
private:
    /* data */
    T* m_ptr;
public:
    explicit smart_pointer(T* ptr) : m_ptr(ptr) {

        std::cout<<"default constructor "<<std::endl;
    }
    //copy constructor
    smart_pointer(smart_pointer&& other) {
        std::cout<<"move constructor "<<std::endl;
        m_ptr = other.release();
    }
    smart_pointer& operator=(smart_pointer rhs) { // trigger default constructor
        
        rhs.swap(*this); //rhs.swap(*this)
        std::cout<<"equal constructor "<<std::endl;
        return *this;
    } 
    ~smart_pointer() {
        std::cout<<"destructor"<<std::endl;
        delete m_ptr;
    };

    T* release() {
        T* ptr = m_ptr;
        m_ptr = nullptr;
        return ptr;
    }

    void swap(smart_pointer& rhs) {
        using std::swap;
        swap(m_ptr, rhs);
    }

    T* operator->() const {
        std::cout<<"get instance"<<std::endl;
        return m_ptr;
    }
    T& operator*() {
        std::cout<<"de-reference"<<std::endl;
        return *m_ptr;
    }
    T* get() const {
        return m_ptr;
    }


};

class shared_count {
 public:
    shared_count() : m_count(1) {}
    void add_count() {
        m_count++;
    }
    long reduce_count() {
        return --m_count;
    }
    long get_count() {
        return m_count;
    }
 private:
    long m_count;
};
template<typename T>
class my_shared_ptr {

 template<typename U>
 friend class my_shared_ptr;

 public:
    explicit my_shared_ptr(T* ptr = nullptr) : m_ptr(ptr) {
        if (ptr) {
            m_shared_count = new shared_count();
        }
    }

    my_shared_ptr(const my_shared_ptr& other) {
        // copy pointer
        m_ptr = other.m_ptr;

        //copy count
        if (m_ptr) {
            other.m_shared_count->add_count();
            m_shared_count = other.m_shared_count;
        }
    }

    template <typename U> // for any type
    my_shared_ptr(const my_shared_ptr<U>& other) {
        // copy pointer
        m_ptr = other.m_ptr;

        //copy count
        if (m_ptr) {
            other.m_shared_count->add_count();
            m_shared_count = other.m_shared_count;
        }
    }

    template <typename U> // for any type, for move constructor
    my_shared_ptr(const my_shared_ptr<U>&& other) {
        // copy pointer
        m_ptr = other.m_ptr;

        //copy count
        if (m_ptr) {
            m_shared_count = other.m_shared_count;
            other.m_ptr = nullptr;
        }
    }
    
    long use_count() const {
        if (m_ptr) {
            return m_shared_count->get_count();
        } else {
            return 0;
        }
    }

    ~my_shared_ptr() {
        if (m_ptr && !m_shared_count->reduce_count()) {
            delete m_ptr;
            delete m_shared_count;
        }
    }
    //swap is 
    void swap(my_shared_ptr& rhs) {
        using std::swap;
        swap(m_ptr, rhs.m_ptr);
        swap(m_shared_count, rhs.m_shared_count);
    }
 private:
    shared_count* m_shared_count;
    T* m_ptr;

};
