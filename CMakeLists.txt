cmake_minimum_required(VERSION 3.0.0)
project(resource-pool VERSION 0.1.0)
include(CMakePackageConfigHelpers)

#include(CTest)
#enable_testing()

add_library(resource-pool STATIC resource_pool.cpp)
#add_executable(resource-pool main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

target_include_directories(${PROJECT_NAME} PRIVATE ./)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER resource_pool.hpp)

include(GNUInstallDirs)

install(
    TARGETS                     ${PROJECT_NAME} EXPORT rsTargets # rsTargets needs to be defined here
    LIBRARY DESTINATION         ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION   ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT rsTargets # use exported name
    FILE rsTargets.cmake
    DESTINATION "${CMAKE_INSTALL_DATADIR}/resource-pool/cmake"
    NAMESPACE YourLibrary::
)
install(
    FILES       ${CMAKE_CURRENT_BINARY_DIR}/resource-pool-config.cmake  
                ${CMAKE_CURRENT_BINARY_DIR}/resource-poolConfigVersion.cmake

    DESTINATION ${CMAKE_INSTALL_LIBDIR}/../share/resource-pool)

include(CPack)
