
#include <boost/scope_exit.hpp>
#include <iostream>

struct file {
    file() : open_(false) {}
    file(char const* path) : open_(false) { open(path); }

    void open(char const* path) { open_ = true; }
    void close(void) { open_ = false; }
    
    bool is_open(void) const { return open_; }
private:
    bool open_;
};

void bad(void) {
    //[try_catch_bad
    file passwd;
    try {
        passwd.open("/etc/passwd");
        // ...
        passwd.close();
    } catch(...) {
        std::clog << "could not get user info" << std::endl;
        if(passwd.is_open()) passwd.close();
        throw;
    }
    //]
}

void good(void) {
    //[try_catch_good
    try {
        file passwd("/etc/passwd");
        BOOST_SCOPE_EXIT(&passwd) {
            passwd.close();
        } BOOST_SCOPE_EXIT_END
    } catch(...) {
        std::clog << "could not get user info" << std::endl;
        throw;
    }
    //]
}

int main(void) {
    bad();
    good();
    return 0;
}

