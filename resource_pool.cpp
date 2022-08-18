/**
 * @file resource_pool.cpp
 * @author Mihai Dragusin (dragusin.mihai.90@gmail.com)
 * @brief [Implementation file] Generic resource pool with optional adaptor for resource initialization logic.
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
#include "resource_pool.hpp"

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
void Pool<T>::add(T &t)
{
    std::lock_guard<std::mutex> guard(lock);
    addAlloc(t, pool);
}
template <typename T>
Pool<T>::Pool(const std::function<void(T &, std::deque<T> &)> TAllocAdd)
{
    addAlloc = TAllocAdd;
}

template <typename T>
Pool<T>::Pool(int capacity, const std::function<void(T, std::deque<T> &)> TAllocAdd)
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

/*
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
*/