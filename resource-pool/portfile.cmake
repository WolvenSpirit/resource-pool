vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO WolvenSpirit/resource-pool
    REF 2d16bed1ef1caa9ec5f56659fcb4c9f3867593a9
    SHA512 c15287ddc2b1637d9c17ce80de3be8a75e9091b227e0961cace9ab8bb38175bd604f9534cccfd5afaaeb6c7271df4d291b74f931f8f10c6b8ae70edb6fd1511d
    HEAD_REF install
    GITHUB_HOST https://github.com
#    [AUTHORIZATION_TOKEN <${SECRET_FROM_FILE}>]
#    [FILE_DISAMBIGUATOR <N>]
)

vcpkg_configure_cmake(
    SOURCE_PATH "${SOURCE_PATH}"
    # OPTIONS -DUSE_THIS_IN_ALL_BUILDS=1 -DUSE_THIS_TOO=2
    # OPTIONS_RELEASE -DOPTIMIZE=1
    # OPTIONS_DEBUG -DDEBUGGABLE=1
)

message("Source path is ${SOURCE_PATH}")

vcpkg_install_cmake()

# # Moves all .cmake files from /debug/share/resource-pool/ to /share/resource-pool/
# # See /docs/maintainers/ports/vcpkg-cmake-config/vcpkg_cmake_config_fixup.md for more details
# When you uncomment "vcpkg_cmake_config_fixup()", you need to add the following to "dependencies" vcpkg.json:
#{
#    "name": "vcpkg-cmake-config",
#    "host": true
#}
# vcpkg_cmake_config_fixup(CONFIG_PATH cmake TARGET_PATH share/resource-pool)

# Uncomment the line below if necessary to install the license file for the port to share/${PORT}/copyright
# file(INSTALL "${SOURCE_PATH}/LICENSE" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}" RENAME copyright)
