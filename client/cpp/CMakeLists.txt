cmake_minimum_required(VERSION 3.15)
project(client LANGUAGES CXX)

find_package(Boost QUIET REQUIRED COMPONENTS program_options thread)
add_executable(client client.cpp)

target_link_libraries(client ${Boost_LIBRARIES} )
target_link_libraries(client Boost::program_options)
target_link_libraries(client Boost::thread)
