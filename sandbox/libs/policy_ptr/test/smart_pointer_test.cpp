#include "boost\smart_ptr\smart_ptr.hpp"

int main(void)
{
    typedef boost::smart_ptr<int> int_ptr;
    int_ptr p;
    int_ptr q;

    p < q;
    p == q;
    p != q;
    std::less<int_ptr> l;
    l(p, q);
    std::swap(p, q);
}




