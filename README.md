### Resource pool

A generic pool class to be used for things that would usually be open connections objects or socket file descriptor (pointers).

##### Installing the library

Use the `install.sh` script after you have a working vcpkg cloned to your work dir (If you already have a system-wide install of vcpkg or in another project you could share it by symlinking it as well). This symlinks the portfile shipped with the library to vcpkg ports/ dir then attempts an install which will invoke our CMakeLists.txt file. Knowing all of this, if something goes wrong usually you can fix it by editing one of these 2 files.


```cpp
// Example:
#include <iostream>
#include <deque>
#include <mutex>
#include <functional>
#include <memory>
#include <resource_pool.hpp>

int main()
{
    // Make some fake pointers
    auto n = 3;
    int *i = &n;
    auto n2 = 5;
    int *i2 = &n2;
    auto n3 = 7;
    int *i3 = &n3;

    // Custom lambda where you can create instances and possibly establish connections
    auto alloc = [](int *t, std::deque<int *> &pool)
    {
        std::cout << "called" << std::endl;
        pool.push_back(std::move(t));
        return;
    };

    Pool<int *> p(alloc);

    p.add(i);
    p.add(i2);
    p.add(i3);

    // Get the stored objects
    auto x = p.getManaged();
    std::cout << **x << std::endl; // After x goes out of scope the value is recycled to the pool
    auto y = p.getManaged();
    std::cout << **y << std::endl;
    auto z = p.getManaged();
    std::cout << **z << std::endl;
    return 0;
}
```

Output: 
```sh
called
called
called
7
5
3
called
called
called
```