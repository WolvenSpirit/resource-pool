vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO WolvenSpirit/resource-pool
    REF 6e71b465b642c0cf5c9e701bc49a21e1a533557e
    SHA512 b3c6f89fdcf47a64c8427726e94ace17f44dcee6b2237bf133236e370451c9b932e252a56e7cc5f141ce17a23331ab440a01aed1a67145bf1ed5be123755f0bb
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
