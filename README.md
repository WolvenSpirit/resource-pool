### Resource pool

A generic pool class to be used for things that would usually be open connections objects or socket file descriptor (pointers).


```cpp
// Example:
#include <iostream>
#include <resource_pool>
#include <functional>
#include <memory>

// alias, I know `ptr` is a poor choice, it's short though
typedef std::shared_ptr<int> ptr;

int main() {
    ptr i = std::make_unique<int>(3);

    // The optional allocator, it doesn't have to be a lambda, it can also be a regular function with same signature.
    auto alloc = []( ptr t, std::deque< ptr> &pool) {
        std::cout << "called" << std::endl;
        pool.push_back(std::move(t));
        return;
    };
    // Set capacity and pass the custom function
    Pool< ptr> p(50,alloc);
    // Add to pool
    p.add(i);
    // Get from pool
    ptr z = p.get();
    // Output
    std::cout << *z.get() << std::endl;
    return 0;
}

```