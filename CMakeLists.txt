cmake_minimum_required(VERSION 3.29)

if(NOT PATCH_VERSION)
    set(PATCH_VERSION "1")
endif()

set(PROJECT_VERSION 1.0.${PATCH_VERSION})
project(helloworld VERSION ${PROJECT_VERSION})

find_package(Git QUIET)
if(GIT_FOUND)
    # Execute git describe
    execute_process(
        COMMAND ${GIT_EXECUTABLE} describe --tags --always --dirty
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_RELEASE_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
else()
    set(GIT_RELEASE_VERSION "unknown")
endif()

include_directories(${CMAKE_BINARY_DIR}/generated)

set(Boost_USE_STATIC_LIBS OFF)          
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

cmake_policy(SET CMP0167 OLD)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)


message(STATUS "==========================================")
message(STATUS "Boost include dirs: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost library: ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}")
message(STATUS "Boost libraries: ${Boost_LIBRARIES}")
message(STATUS "==========================================")

add_executable(helloworld_cli main.cpp)
add_library(helloworld lib.cpp)
add_executable(test_version test_version.cpp)

set_target_properties(helloworld_cli helloworld test_version PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(helloworld PRIVATE "${CMAKE_BINARY_DIR}")
target_include_directories(test_version PRIVATE ${Boost_INCLUDE_DIRS} "${CMAKE_BINARY_DIR}")

target_link_libraries(helloworld_cli PRIVATE helloworld)


target_link_libraries(test_version
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    helloworld
)


if(MINGW)
    target_compile_definitions(test_version PRIVATE
        BOOST_ALL_DYN_LINK=1
        BOOST_LIB_DIAGNOSTIC=1
    )
endif()


if (MSVC)
    target_compile_options(helloworld_cli PRIVATE /W4)
    target_compile_options(helloworld PRIVATE /W4)
    target_compile_options(test_version PRIVATE /W4)
else ()
    target_compile_options(helloworld_cli PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(helloworld PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(test_version PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

enable_testing()
add_test(test_version test_version)