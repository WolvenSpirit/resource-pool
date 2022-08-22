#include <iostream>
#include <deque>
#include <mutex>
#include <functional>
#include <memory>
#include "../resource_pool.hpp"

typedef std::shared_ptr<int> ptr;

int main() {
    auto n = 3;
    ptr i = std::make_unique<int>(3);

    auto alloc = []( ptr t, std::deque< ptr> &pool) {
        std::cout << "called" << std::endl;
        pool.push_back(std::move(t));
        return;
    };

    Pool< ptr> p(50,alloc);
    p.add(i);
    ptr z = p.get();
    std::cout << *z.get() << std::endl;
    return 0;
}