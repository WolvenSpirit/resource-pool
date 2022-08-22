cmake_minimum_required(VERSION 3.0.0)
project(resource-pool VERSION 0.1.0)

#include(CTest)
#enable_testing()

add_library(resource-pool STATIC resource_pool.cpp)
#add_executable(resource-pool main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

target_include_directories(${PROJECT_NAME} PRIVATE ./)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER resource_pool.hpp)

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
include(CPack)
