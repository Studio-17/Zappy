cmake_minimum_required(VERSION 3.17)

# set the project name and version
project(Zappy VERSION 0.1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include raylib into build
include(cmake-modules/Findraylib.cmake)

# specify the sources
file(GLOB SOURCES
    ../../library/net/*.c
    ../../library/net/protocol/*.c
    Source/Main.cpp
    Source/Client/*.cpp
    Source/Errors/*.cpp
    Source/Errors/ErrorsModules/*.cpp
    Source/Errors/ErrorsModules/Client/*.cpp
    Source/Errors/ErrorsModules/Options/*.cpp
    Source/Options/*.cpp
    Source/Window/*.cpp
    Source/App/*.cpp
    Source/App/Window/*.cpp
    Source/App/Camera/*.cpp
    Source/App/Position/*.cpp
    Source/App/Object/*.cpp
    Source/App/Rendering/*.cpp
    Source/App/Object/Player/*.cpp
    Source/App/Object/Resource/*.cpp
    Source/App/Object/Tile/*.cpp
    Source/App/Game/*.cpp
    Source/Events/*.cpp
    Source/App/Scenes/*.cpp
    Source/App/Scenes/Menu/*.cpp
)

# specify the headers
include_directories(
    ../../library/include/
    Source/
    Source/Client/
    Source/Errors/
    Source/Errors/ErrorsModules/
    Source/Errors/ErrorsModules/Client/
    Source/Errors/ErrorsModules/Options/
    Source/Options/
    Source/App/
    Source/App/Window/
    Source/App/Camera/
    Source/App/Position/
    Source/App/Object
    Source/App/Rendering
    Source/App/Object/Player/
    Source/App/Object/Resource/
    Source/App/Object/Tile/
    Source/App/Game/
    Source/App/Events/
    Source/App/Scenes/
    Source/App/Scenes/Menu
    Source/App/Clock/
)

add_executable(zappy_gui ${SOURCES})
target_link_libraries(zappy_gui raylib)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
