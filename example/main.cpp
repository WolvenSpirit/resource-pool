#include <iostream>
#include <deque>
#include <mutex>
#include <functional>
#include <memory>
#include "../resource_pool.hpp"

int main() {
    auto n = 3;
    int *i = &n;

    auto alloc = []( int* t, std::deque< int*> &pool) {
        std::cout << "called" << std::endl;
        pool.push_back(std::move(t));
        return;
    };

    Pool< int*> p(alloc);
    p.add(i);
    auto z = p.get();
    std::cout << *z << std::endl;
    return 0;
}