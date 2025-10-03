cmake_minimum_required(VERSION 3.16)
project(custom_https_server CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)
# Boost::system is commonly needed with Beast/Asio
find_package(Boost REQUIRED COMPONENTS system)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(https_server
    src/main.cpp
    src/ssl_utils.cpp
    src/file_responder.cpp
    src/router.cpp
    src/https_session.cpp
    src/http_redirect_session.cpp
)

target_link_libraries(https_server
    PRIVATE
        Boost::system
        OpenSSL::SSL
        OpenSSL::Crypto
        Threads::Threads
)

# On Linux, this helps static file IO perf with large files
if (UNIX AND NOT APPLE)
  target_compile_definitions(https_server PRIVATE _FILE_OFFSET_BITS=64)
endif()
