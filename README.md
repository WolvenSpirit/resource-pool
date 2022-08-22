### Resource pool

A generic pool class to be used for things that would usually be open connections objects or socket file descriptor (pointers).

##### Installing the library

Use the `install.sh` script after you have a working vcpkg cloned to your work dir (If you already have a system-wide install of vcpkg or in another project you could share it by symlinking it as well). This symlinks the portfile shipped with the library to vcpkg ports/ dir then attempts an install which will invoke our CMakeLists.txt file. Knowing all of this, if something goes wrong usually you can fix it by editing one of these 2 files.


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