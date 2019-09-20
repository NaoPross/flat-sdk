cmake_minimum_required(VERSION 3.10)
project(
    demo
    VERSION 0.1 
    LANGUAGES CXX)

include(FindLua)
include(GNUInstallDirs) # for install
  
find_package(Flatland 0.1 REQUIRED)
find_package(sol2 3.0 REQUIRED)
find_package(Lua REQUIRED)
find_package(Flatlua 0.1 REQUIRED)

add_executable(demo
    demo.cpp
)
 
target_compile_options(demo
    PRIVATE 
        $<$<CXX_COMPILER_ID:GNU>:
            -fdiagnostics-color
            -pedantic -Wall -Wextra -Wcast-qual -Wcast-align
            -Wpointer-arith -Winit-self -Wshadow -Wswitch-enum 
            -Wredundant-decls -Wfloat-equal -Wundef -Wvla 
            -Wconversion -Wstrict-aliasing
        >
        
        $<$<CXX_COMPILER_ID:MSVC>: /W4>
)

# setting up c++ standard 17
target_compile_features(demo
    PRIVATE
        cxx_std_17
)

target_link_libraries(demo
    PRIVATE
        Flatland::Flatland
        sol2::sol2
        Flatlua::Flatlua
        ${LUA_LIBRARIES}
)

target_include_directories(demo
    PUBLIC
        $<INSTALL_INTERFACE:include/>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_compile_definitions(demo
    PRIVATE
        ASSETS_INSTALL_PREFIX="${CMAKE_INSTALL_DATADIR}/demo/"
)

# Install section
# executable
install(
    TARGETS demo
    EXPORT demo-targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# assets
install(
    DIRECTORY assets/
    DESTINATION ${CMAKE_INSTALL_DATADIR}/demo
)

# scripts
install(
    DIRECTORY scripts/
    DESTINATION ${CMAKE_INSTALL_BINDIR}/scripts
)
