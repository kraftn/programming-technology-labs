cmake_minimum_required(VERSION 3.1.0)

project(client)

find_package(cppzmq)

set (CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.11.2\\5.11.2\\msvc2015")

# Find includes in corresponding build directories
set (CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set (CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set (CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

QT5_WRAP_UI (CODE_UI mainwindow.ui settings.ui)

# Populate a CMake variable with the sources
set (client_SRCS mainwindow.ui mainwindow.h mainwindow.cpp settings.ui settings.h settings.cpp main.cpp receiver.h)
# Tell CMake to create the helloworld executable
add_executable(client ${client_SRCS} ${CODE_UI})
# Use the Widgets module from Qt 5 and cppzmq
target_link_libraries(client Qt5::Widgets)
target_link_libraries(client cppzmq)
