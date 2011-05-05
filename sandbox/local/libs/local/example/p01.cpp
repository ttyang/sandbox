
#include <iostream>
#include <vector>
#include <algorithm>

struct global_func {
    template<typename T>
    void operator()(T num) {
    }
private:
    double& sum;
    const int& factor;
};

int main() {
    double sum = 0.0;
    int factor = 10;

    global_ add(sum, factor);

    v[0] = -1.0; v[1] = -2.0; v[2] = -3.0;
    std::for_each(v.begin(), v.end(), l);

    std::vector<std::string> s(3);
    s[0] = "aa"; s[1] = "bb"; s[2] = "cc";
    std::for_each(s.begin(), s.end(), l);

    std::cout << sum << std::endl;
    return 0;
}
