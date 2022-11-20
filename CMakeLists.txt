cmake_minimum_required(VERSION 3.16)

project(main)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(OPTIMIZATION_FLAGS O3)
option(BUILD_Posix OFF)
option(BUILD_x86_32 OFF)


set(CFLAGS
    -Wall
    -${OPTIMIZATION_FLAGS}
    -fdiagnostics-color=always   # high light the warning or error
    )
set(LDFLAGS

    )
set(DEPEN_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    )


add_compile_options(${CFLAGS})
add_link_options(${LDFLAGS})



set(DEPEN_DIR
    ${DEPEN_DIR}
)



# Assembly file
FILE(GLOB ASMSRC src/*.s)
# C file
FILE(GLOB CSRC src/*.c)
# C++ file
FILE(GLOB CXXSRC src/*.cpp)

set_property(SOURCE ${ASMSRC} PROPERTY LANGUAGE C)

set(SOURCE_FILE
  ${CSRC}
  ${CXXSRC}
  ${ASMSRC} 
  )


add_library(graph ${CSRC})
target_include_directories(graph PUBLIC ${DEPEN_DIR})


# generate the test executable file
add_subdirectory(test)

