vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO WolvenSpirit/resource-pool
    REF 95dbc1a597d094c284cbde547dbe54d814a8d165
    SHA512 07796c203d45fd3ac6376225d51c7ee85a77ad506ba55a9d100cb3c8cbc639a9a36fa5b747250e37f397870d1270b160c4b5e1c73320944caae20a9328b07d74
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
