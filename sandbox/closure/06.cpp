
#include <boost/function.hpp>
#include <iostream>

template<typename This = void>
struct guard {
    explicit guard(This _this) : this_(_this) {}
    template<typename Lambda>
    void operator=(Lambda f) { f_ = f; }
    ~guard() { if(f_) f_(this_); }
private:
    This this_;
    boost::function<void (This)> f_;
};

template<>
struct guard<void> {
    template<typename Lambda>
    void operator=(Lambda f) { f_ = f; }
    ~guard() { if(f_) f_(); }
private:
    boost::function<void (void)> f_;
};

struct x {
    void f() {
        i_ = 30;
        int r = -20, v = 20;
        guard<x*> g(this); g = [&r, v](x* this_) mutable -> void {
            r = v + this_->i_;
            std::cout << r << " " << v << std::endl;
        };
        std::cout << r << " " << v << std::endl;
    }
private:
    int i_;
};

int main() {
    x xx;
    xx.f();

    int r = -10, v = 10;
    guard<> g; g = [&r, v]() mutable -> void {
        r = v;
        std::cout << r << " " << v << std::endl;
    };
    std::cout << r << " " << v << std::endl;
    return 0;
}

