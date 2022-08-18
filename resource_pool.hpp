/**
 * @file resource_pool.hpp
 * @author Mihai Dragusin (dragusin.mihai.90@gmail.com)
 * @brief [Header file] Generic resource pool with optional adaptor for resource initialization logic.
 * @version 0.1
 * @date 2022-08-18
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <deque>
#include <mutex>
#include <functional>
#include <memory>

template <typename T>
class Pool
{
private:
    /**
     * @brief pool is made available if an optional initializer fn is passed.
     * 
     */
    std::deque<T> pool;
    /**
     * @brief Allows concurrent access, private.
     * 
     */
    std::mutex lock;

public:
    /**
     * @brief The constructor can take an allocator function as argument, capacity or both.
     * Meant to be used for resources that require initialization, such as network sockets.
     * @return void
     */
    Pool();
    /**
     * @brief The constructor can take an allocator function as argument, capacity or both.
     * Meant to be used for resources that require initialization, such as network sockets.
     * @param capacity
     * @return void
     */
    Pool(int capacity);

    std::function<void(T &, std::deque<T> &)> addAlloc;

    void _add(T t, std::deque<T> &p);

    void add(T &t);

    /**
     * @brief The constructor can take an allocator function as argument, capacity or both.
     * Meant to be used for resources that require initialization, such as network sockets.
     * @param TAllocAdd
     * @return void
     */
    Pool(const std::function<void(T &, std::deque<T> &)> TAllocAdd);

    /**
     * @brief The constructor can take an allocator function as argument, capacity or both.
     * Meant to be used for resources that require initialization, such as network sockets.
     * @param capacity
     * @param TAllocAdd
     * @return void
     */
    Pool(int capacity, const std::function<void(T, std::deque<T> &)> TAllocAdd);

    T get();
};
