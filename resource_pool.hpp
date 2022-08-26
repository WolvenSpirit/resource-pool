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
class PoolObject;

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

    std::function<void(T , std::deque<T> &)> addAlloc;

    void _add(T t, std::deque<T> &p);

    void add(T t);

    /**
     * @brief The constructor can take an allocator function as argument, capacity or both.
     * Meant to be used for resources that require initialization, such as network sockets.
     * @param TAllocAdd
     * @return void
     */
    Pool(const std::function<void(T , std::deque<T> &)> TAllocAdd);

    /**
     * @brief The constructor can take an allocator function as argument, capacity or both.
     * Meant to be used for resources that require initialization, such as network sockets.
     * @param capacity
     * @param TAllocAdd
     * @return void
     */
    Pool(int capacity, const std::function<void(T , std::deque<T> &)> TAllocAdd);

    T get();

    PoolObject<T> getManaged();
};

// --- Implementation

template <typename T>
Pool<T>::Pool()
{
    addAlloc = _add;
}

template <typename T>
Pool<T>::Pool(int capacity)
{
    pool.resize(capacity);
    addAlloc = _add;
}

template <typename T>
void Pool<T>::_add(T t, std::deque<T> &p)
{
    std::lock_guard<std::mutex> guard(lock);
    pool.push_back(t);
}

template <typename T>
void Pool<T>::add(T t)
{
    std::lock_guard<std::mutex> guard(lock);
    addAlloc(t, pool);
}
template <typename T>
Pool<T>::Pool(const std::function<void(T , std::deque<T> &)> TAllocAdd)
{
    addAlloc = TAllocAdd;
}

template <typename T>
Pool<T>::Pool(int capacity, const std::function<void(T , std::deque<T> &)> TAllocAdd)
{
    pool.resize(capacity);
    addAlloc = TAllocAdd;
}

template <typename T>
T Pool<T>::get()
{
    std::lock_guard<std::mutex> guard(lock);
    T &t = pool.back();
    pool.pop_back();
    return std::move(t);
}

/**
 * @brief Class that handles recycling back to the pool.
 * 
 */
template <typename T>
class PoolObject {
    public:
    T value;
    Pool<T> *pool;
    /**
     * @brief Construct a new Pool Object
     * 
     * @param t 
     * @param p 
     */
    PoolObject(T t, Pool<T> *p) {
        value = t;
        pool = p;
    }
    /**
     * @brief Recycle the Pool Object
     * 
     */
    ~PoolObject() {
        pool->add(value);
    }
};

/**
 * @brief Returns a managed object class of type T which handles recycling T back to the pool
 * 
 */
template <typename T>
PoolObject<T> Pool<T>::getManaged() {
    return PoolObject<T>(this->get(),this);
}