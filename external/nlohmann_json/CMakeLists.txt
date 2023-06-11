# extract version number from json.hpp looking like the following lines
#define NLOHMANN_JSON_VERSION_MAJOR 3   // NOLINT(modernize-macro-to-enum)
#define NLOHMANN_JSON_VERSION_MINOR 11  // NOLINT(modernize-macro-to-enum)
#define NLOHMANN_JSON_VERSION_PATCH 2   // NOLINT(modernize-macro-to-enum)
file(READ include/nlohmann/json.hpp _nlohmann_contents)
string(REGEX MATCH "#define NLOHMANN_JSON_VERSION_MAJOR[ ]*([0-9]+)" _ "${_nlohmann_contents}")
if ("${CMAKE_MATCH_1}" STREQUAL "")
  message(FATAL_ERROR "Failed to extract major version from json.hpp file")
endif()
set(nlohmann_json_VERSION_MAJOR "${CMAKE_MATCH_1}")
string(REGEX MATCH "#define NLOHMANN_JSON_VERSION_MINOR[ ]*([0-9]+)" _ "${_nlohmann_contents}")
if ("${CMAKE_MATCH_1}" STREQUAL "")
  message(FATAL_ERROR "Failed to extract minor version from json.hpp file")
endif()
set(nlohmann_json_VERSION_MINOR "${CMAKE_MATCH_1}")
string(REGEX MATCH "#define NLOHMANN_JSON_VERSION_PATCH[ ]*([0-9]+)" _ "${_nlohmann_contents}")
if ("${CMAKE_MATCH_1}" STREQUAL "")
  message(FATAL_ERROR "Failed to extract patch version from json.hpp file")
endif()
set(nlohmann_json_VERSION_PATCH "${CMAKE_MATCH_1}")
set(nlohmann_json_VERSION "${nlohmann_json_VERSION_MAJOR}.${nlohmann_json_VERSION_MINOR}.${nlohmann_json_VERSION_PATCH}")

message(STATUS "Providing nlohmann_json version ${nlohmann_json_VERSION}")
project(nlohmann_json LANGUAGES CXX VERSION "${nlohmann_json_VERSION}")

add_library(nlohmann_json INTERFACE)

target_include_directories(nlohmann_json
  SYSTEM INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
)
# Enable extended diagnostics information
# https://github.com/nlohmann/json/releases/tag/v3.10.0
target_compile_definitions(nlohmann_json INTERFACE JSON_DIAGNOSTICS=1)

# provide a namespaced alias for clients to 'link' against if nlohman_json is included as a sub-project
add_library(nlohmann_json::nlohmann_json ALIAS nlohmann_json)
