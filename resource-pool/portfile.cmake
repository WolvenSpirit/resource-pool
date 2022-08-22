vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO WolvenSpirit/resource-pool
    REF b0a8c798d4e4b5867e6b3089352e0569aba8df9f
    SHA512 b911d7e70a570a49c320d5efa11b9405434b4c98f7b07f015ecb420a94d7e8528f0fe309a6301978caaf8e54c01e68187992413b57750a36f485c4519d9796c7
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
