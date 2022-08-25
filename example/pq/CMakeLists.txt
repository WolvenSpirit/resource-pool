cmake_minimum_required(VERSION 3.0.0)
project(pq-example VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

find_package(resource-pool REQUIRED)
find_package(OpenSSL CONFIG COMPONENTS SSL Crypto)
find_package(libpqxx CONFIG COMPONENTS pqxx) 

add_executable(pq-example main.cpp)

target_link_libraries(pq-example PUBLIC libpqxx::pqxx)
target_link_libraries(pq-example PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(pq-example PRIVATE PostgreSQL::PostgreSQL)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
