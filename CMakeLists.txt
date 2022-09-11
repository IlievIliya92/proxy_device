cmake_minimum_required(VERSION 3.9)
project(proxy_service)

include(cmake/GolangSimple.cmake)

# --- Proxy Service
add_subdirectory(service)

# --- GO server / proxy
GO_GET(zmq github.com/pebbe/zmq4)
add_subdirectory(proxy)
add_subdirectory(server)

add_subdirectory(client)
