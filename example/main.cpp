#include <iostream>
#include <deque>
#include <mutex>
#include <functional>
#include <memory>
#include "../resource_pool.hpp"

int main()
{
    auto n = 3;
    int *i = &n;
        auto n2 = 5;
    int *i2 = &n2;
        auto n3 = 7;
    int *i3 = &n3;

    auto alloc = [](int *t, std::deque<int *> &pool)
    {
        std::cout << "called" << std::endl;
        pool.push_back(std::move(t));
        return;
    };

    Pool<int *> p(alloc);
    p.add(i);p.add(i2);p.add(i3);
    auto x = p.getManaged();
    std::cout << **x << std::endl;
    auto y = p.getManaged();
    std::cout << **y << std::endl;
    auto z = p.getManaged();
    std::cout << **z << std::endl;
    return 0;
}