cmake_minimum_required(VERSION 3.9)
project(tcp_proxy_service VERSION 1.0.0 DESCRIPTION "TCP proxy service.")

include(ExternalProject)

file(GLOB_RECURSE SOURCES "src/*.c")
add_executable(tcp_proxy_service ${SOURCES})
set_target_properties(tcp_proxy_service PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1)


include(ExternalProject)
ExternalProject_Add(tcpServer
  	GIT_REPOSITORY https://github.com/IlievIliya92/tcp_server.git
  	GIT_TAG	"main"
	INSTALL_COMMAND cmake -E echo "Skipping install step."
)


target_include_directories(tcp_proxy_service PRIVATE src/)
target_include_directories(tcp_proxy_service PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/tcpServer-prefix/src/tcpServer/include/)
target_include_directories(tcp_proxy_service PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/tcpServer-prefix/src/tcpServer/libs/log/include/)
target_include_directories(tcp_proxy_service PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/tcpServer-prefix/src/tcpServer/libs/utils/include/)

target_link_libraries(tcp_proxy_service zmq czmq)

target_link_libraries(tcp_proxy_service ${CMAKE_CURRENT_BINARY_DIR}/tcpServer-prefix/src/tcpServer-build/libtcp_server.so)
target_link_libraries(tcp_proxy_service ${CMAKE_CURRENT_BINARY_DIR}/tcpServer-prefix/src/tcpServer-build/libs/log/liblog.so)
target_link_libraries(tcp_proxy_service ${CMAKE_CURRENT_BINARY_DIR}/tcpServer-prefix/src/tcpServer-build/libs/utils/libutils.so)


add_dependencies(tcp_proxy_service tcpServer)
