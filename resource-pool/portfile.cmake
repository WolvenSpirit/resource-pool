vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO WolvenSpirit/resource-pool
    REF d7bb1c32a7934d0242c2b03425dc826bfb46857f
    SHA512 53569bbf8253c970c3662d8741e4acddc3ddddeb77b4a4150d3b8f08b4486877dae20f02fb0226d22aa99e2f6bd9a220e87e99ac6f55a81e11df753b52284cf1
    HEAD_REF main
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
