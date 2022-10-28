#include <iostream>
class shape {
 public:
    shape() {}
    ~shape() {}
    void get_shape() {
        std::cout<<"i am a shape"<<std::endl;
    }
};

class circle : public shape {
 public:
     ~circle() {
        puts("~circle()");
    }
};