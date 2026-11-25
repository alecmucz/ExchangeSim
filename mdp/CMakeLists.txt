cmake_minimum_required(VERSION 3.30)
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
project(mdp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(MDP_PROTO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../schemas/proto)

# Dependencies
find_package(Protobuf CONFIG REQUIRED)
find_package(boost_beast CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

# Components
add_subdirectory(common)
add_subdirectory(feedhandler)