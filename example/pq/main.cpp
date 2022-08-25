/**
 * @file example/pq/main.cpp
 * @author Mihai Dragusin (dragusin.mihai.90@gmail.com)
 * @brief [pqxx pool example]
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
#include <resource_pool.hpp>
#include <libpq-fe.h>
#include <pqxx/pqxx>

using namespace std;

typedef pqxx::connection *pool_conn;

Pool<pool_conn> *pool;

int main()
{
    string user = "postgres";
    string pass = "";
    string host = "localhost";
    string port = "5432";
    string name = "db01";
    string uri = "postgresql://" + user + ":" + pass + "@" + host + ":" + port + "/" + name;

    auto capacity = 3;

    auto alloc = [uri](pool_conn t, std::deque<pool_conn> &pool)
    {
        auto conn = new pqxx::connection(uri.c_str());
        pool.push_back(std::move(conn));
        return;
    };

    Pool<pool_conn> p(alloc);

    for (auto i = 0; i < capacity; i++)
    {
        p.add((pool_conn)NULL);
    }
    pool = &p;
    auto c = pool->get();

    std::cout << c->dbname() << " " << c->backendpid() << std::endl;
    std::cout << c->dbname() << " " << c->backendpid() << std::endl;
    std::cout << c->dbname() << " " << c->backendpid() << std::endl;

    return 0;
}