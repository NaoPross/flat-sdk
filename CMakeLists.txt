cmake_minimum_required(VERSION 3.10)

project(flat-sdk)
option(BUILD_OFFLINE "Build offline" OFF)
if (${BUILD_OFFLINE})
    set_property(
        DIRECTORY ${flat-sdk_SOURCE_DIR}
        PROPERTY EP_UPDATE_DISCONNECTED 1
    )
endif()

message("${CMAKE}")

add_custom_target(offline
    ${CMAKE_COMMAND} -H${CMAKE_SOURCE_DIR} -B${CMAKE_BINARY_DIR} -DBUILD_OFFLINE=ON
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_target(online
    ${CMAKE_COMMAND} -H${CMAKE_SOURCE_DIR} -B${CMAKE_BINARY_DIR} -DBUILD_OFFLINE=OFF
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

include(ExternalProject)
ExternalProject_Add(libmm
    PREFIX libmm
    GIT_REPOSITORY https://github.com/NaoPross/libmm.git
    GIT_TAG master
    GIT_PROGRESS ON
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libmm
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/root
)

ExternalProject_Add(libwsdl2
    DEPENDS libmm
    PREFIX libwsdl2
    GIT_REPOSITORY https://github.com/NaoPross/libwsdl2.git
    GIT_TAG master
    GIT_PROGRESS ON
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libwsdl2
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/root
)

ExternalProject_Add(lua
    PREFIX lua
    URL https://www.lua.org/ftp/lua-5.3.5.tar.gz
    URL_MD5 4f4b4f323fd3514a68e0ab3da8ce3455 
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lua
    CONFIGURE_COMMAND true
    BUILD_COMMAND make linux
    BUILD_IN_SOURCE ON
    INSTALL_COMMAND make INSTALL_TOP=${CMAKE_BINARY_DIR}/root install
)

ExternalProject_Add(sol2
    DEPENDS lua
    PREFIX sol2
    GIT_REPOSITORY https://github.com/ThePhD/sol2.git
    GIT_TAG v3.0.2
    GIT_SHALLOW ON
    GIT_PROGRESS ON
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sol2
    PATCH_COMMAND patch -p1 < ${CMAKE_CURRENT_SOURCE_DIR}/patches/sol2/0001-Fix-CMake-headers-install-target.patch.txt
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/root
)

ExternalProject_Add(flatland
    DEPENDS libmm
    DEPENDS libwsdl2
    DEPENDS sol2
    DEPENDS lua
    PREFIX flatland
    GIT_REPOSITORY https://github.com/NaoPross/flatland.git
    GIT_TAG master
    GIT_PROGRESS ON
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/flatland
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/root
)

ExternalProject_Add(demo
    DEPENDS flatland
    PREFIX demo
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/demo
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/root
    INSTALL_COMMAND true
)
