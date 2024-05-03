cmake_minimum_required(VERSION 3.5)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
add_compile_options("-lstdc++fs")
add_compile_options("-pthread")
add_compile_options("-O2")

project(ZIPLIB)
SET(CMAKE_CXX_COMPILER g++-11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

file(GLOB CPP_FILES *.cpp)
file(GLOB DETAIL_FILES detail/*.cpp)
file(GLOB BZIP2_FILES extlibs/bzip2/*.c)
file(GLOB LZMA_UNIX_FILES extlibs/lzma/unix/*.c)

find_package(ZLIB)
if(NOT ZLIB_FOUND)
    FetchContent_Declare(zlib
        GIT_REPOSITORY  https://github.com/madler/zlib.git
        GIT_TAG         v1.2.13
        GIT_SHALLOW     TRUE
        GIT_PROGRESS    TRUE
    )

    FetchContent_GetProperties(zlib)
    if(NOT zlib_POPULATED)
    FetchContent_Populate(zlib)
    execute_process(
        COMMAND           ${GIT_EXECUTABLE} apply ${CMAKE_CURRENT_LIST_DIR}/cmake/zlib.patch
        WORKING_DIRECTORY ${zlib_SOURCE_DIR}
        #OUTPUT_QUIET
        #ERROR_QUIET
    )
    set(ZLIB_INCLUDE_DIR ${zlib_SOURCE_DIR} ${zlib_BINARY_DIR})
    set(ZLIB_LIBRARY zlibstatic)
    set(CMAKE_PROJECT_INCLUDE_BEFORE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/enable_cmp0048.cmake")
    add_subdirectory(${zlib_SOURCE_DIR} ${zlib_BINARY_DIR} EXCLUDE_FROM_ALL)
    unset(CMAKE_PROJECT_INCLUDE_BEFORE)
    endif()
endif()

add_library(${PROJECT_NAME} STATIC 
    ${CPP_FILES}
    ${DETAIL_FILES}
    ${BZIP2_FILES}
    ${LZMA_UNIX_FILES}
    ${LZMA_UNIX_UTIL_FILES}
)

include_directories (${ZLIB_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} 
    Threads::Threads
    ZLIB
)

target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})