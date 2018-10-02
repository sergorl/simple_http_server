cmake_minimum_required(VERSION 2.8)

project(http_server)

execute_process(COMMAND sudo apt install -y qtbase5-dev)        

set (CMAKE_CXX_STANDARD 11)
add_compile_options(-std=c++11) 

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the Qt library
find_package(Qt5Core  CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)

# Populate a CMake variable with the sources
set(SRC    
    httpserver.cpp
    worker.cpp
    handler.cpp
    response.cpp
    main.cpp
)
add_executable(final ${SRC})

target_link_libraries(final Qt5::Core Qt5::Network)


add_custom_command(TARGET final 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:final> .)