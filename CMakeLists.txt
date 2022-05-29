cmake_minimum_required(VERSION 3.9)
project(proxy_service)

cmake_minimum_required(VERSION 3.0)

include(cmake/GolangSimple.cmake)

# --- Proxy Service
add_subdirectory(service)

# --- GO server / proxy
GO_GET(zmq github.com/pebbe/zmq4)
add_subdirectory(proxy)
add_subdirectory(server)
