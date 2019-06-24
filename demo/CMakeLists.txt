cmake_minimum_required(VERSION 3.10)
project(
    demo
    VERSION 0.1 
    LANGUAGES CXX)


find_package(Flatland 0.1 REQUIRED)

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
)
