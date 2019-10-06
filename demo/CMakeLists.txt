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

function(add_resources out_var)
  set(result)
  foreach(in_f ${ARGN})
    file(RELATIVE_PATH src_f ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${in_f})
    set(out_f "${PROJECT_BINARY_DIR}/${in_f}.o")
    add_custom_command(OUTPUT ${out_f}
      COMMAND ld -r -b binary -o ${out_f} ${src_f}
      DEPENDS ${in_f}
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      COMMENT "Building resource object ${out_f}"
      VERBATIM
      )
    list(APPEND result ${out_f})
  endforeach()
  set(${out_var} "${result}" PARENT_SCOPE)
endfunction()

# A simple program that uses resources
add_resources(SCRIPTS scripts/demo.lua)

message("Embedding resources:")
foreach(script ${SCRIPTS})
    message(${script})
endforeach()

set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(demo
    demo.cpp
    ${SCRIPTS}
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

link_directories(${CMAKE_INSTALL_LIBDIR})

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

install(
    DIRECTORY scripts/
    DESTINATION ${CMAKE_INSTALL_DATADIR}/scripts
)

#add_custom_command(TARGET demo POST_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
#                       ${CMAKE_CURRENT_SOURCE_DIR}/scripts/demo.lua
#                       $<TARGET_FILE_DIR:demo>/demo.lua
#                   )

# scripts
#install(
#    DIRECTORY scripts/
#    DESTINATION ${CMAKE_INSTALL_BINDIR}/scripts
#)
