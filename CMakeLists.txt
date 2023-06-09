message(STATUS "Using CMake version ${CMAKE_VERSION}")
cmake_minimum_required(VERSION 3.12...${CMAKE_VERSION})

# extract version from CGlobal.hpp to have it in CMake project
# expecting a line with the following format
#	static inline const std::string version{ "v0.0.1" };
file(READ TentakelsAttacking2/Constants/public/CGlobal.hpp CGlobal_contents)
string(REGEX MATCH "version\{[ ]*\"v([0-9]+\.[0-9]+\.[0-9]+)\"[ ]*\}\;" _ "${CGlobal_contents}")
set(TA2_version ${CMAKE_MATCH_1})
if ("${TA2_version}" STREQUAL "")
  message(FATAL_ERROR "Failed to extract version from CGlobal.hpp file")
endif()
message(STATUS "Extracted version '${TA2_version}' from CGlobal.hpp")

project(TentakelsAttacking2 VERSION ${TA2_version} LANGUAGES CXX)

# We need at least C++20 support, but if the user wants to specify another version let the user do it
# https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html
string(COMPARE EQUAL "${CMAKE_CXX_STANDARD}" "" no_cmake_cxx_standard_set)
if(no_cmake_cxx_standard_set)
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
  message(STATUS "Using default C++ standard ${CMAKE_CXX_STANDARD}")
else()
  message(STATUS "Using user specified C++ standard ${CMAKE_CXX_STANDARD}")
endif()

# get all C++ source files for the executable and create it
file(GLOB_RECURSE TA2_SOURCES
  "TentakelsAttacking2/*.cpp"
  "TentakelsAttacking2/*.h"
  "TentakelsAttacking2/*.hpp")
add_executable(${PROJECT_NAME} ${TA2_SOURCES})

# find all directories with header files and add them to the include directories
file(GLOB_RECURSE TA2_INCLUDE_DIRS
  "TentakelsAttacking2/*.h"
  "TentakelsAttacking2/*.hpp"
)
list(TRANSFORM TA2_INCLUDE_DIRS REPLACE "/[^/]+\.h(pp)?$" "")
list(REMOVE_DUPLICATES TA2_INCLUDE_DIRS)
target_include_directories(${PROJECT_NAME} PRIVATE ${TA2_INCLUDE_DIRS})

# check for 'std::format' support of the compiler
include(CheckIncludeFileCXX)
CHECK_INCLUDE_FILE_CXX(format has_std_format)
if (NOT has_std_format)
  message(STATUS "compiler doesn't support C++20 <format>, looking for fmt to use instead")
  target_compile_definitions(${PROJECT_NAME} PRIVATE USE_FMT_FORMAT)
  find_package(fmt REQUIRED)
  target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
  # workaround for Ubuntu libfmt-dev package when building in 'RelWithDebInfo'
  # the fmt::fmt target has no RelWithDebInfo imported config, use Release in that case
  get_target_property(imported_configs fmt::fmt IMPORTED_CONFIGURATIONS)
  message(STATUS "imported configs: ${imported_configs}")
  if(NOT "RELWITHDEBINFO" IN_LIST imported_configs AND "NONE" IN_LIST imported_configs)
    set_property(TARGET fmt::fmt PROPERTY MAP_IMPORTED_CONFIG_RELWITHDEBINFO none)
  endif()
  if(NOT "RELEASE" IN_LIST imported_configs AND "NONE" IN_LIST imported_configs)
    set_property(TARGET fmt::fmt PROPERTY MAP_IMPORTED_CONFIG_RELEASE none)
  endif()
endif()

# find and link to raylib dependency
find_package(raylib CONFIG QUIET)
if (NOT raylib_FOUND)
  # workaround because raylib with vcpkg on Linux is broken with asan/ubsan build errors
  # see: https://github.com/microsoft/vcpkg/issues/21293
  message(STATUS "raylib dependency not found, adding 'raylib' subdirectory to satisfy dependency")
  add_subdirectory(raylib EXCLUDE_FROM_ALL)
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
