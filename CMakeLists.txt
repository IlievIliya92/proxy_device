cmake_minimum_required(VERSION 3.9)
project(proxy_service)

include(cmake/GolangSimple.cmake)

# --- Proxy Service
add_subdirectory(service)

# --- GO server / proxy
add_subdirectory(proxy)
add_subdirectory(server)

# --- Clients
add_subdirectory(client)
