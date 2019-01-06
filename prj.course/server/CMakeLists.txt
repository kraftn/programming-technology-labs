# Find includes in corresponding build directories
set (CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set (CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set (CMAKE_AUTOUIC ON)

# Find the QtWidgets and Qt5Network libraries
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)
# Find the zeromq library
find_package(cppzmq)

QT5_WRAP_UI (CODE_UI server.ui)

# Populate a CMake variable with the sources
set(server_SRCS main.cpp server.ui server.h server.cpp beacon.h beacon.cpp forwarder.h forwarder.cpp)

# Tell CMake to create the server executable
add_executable(server WIN32 ${server_SRCS} ${CODE_UI})

set_property(TARGET server PROPERTY CXX_STANDARD 14)

# Use the libraries
target_link_libraries(server Qt5::Widgets)
target_link_libraries(server Qt5::Network)
target_link_libraries(server cppzmq)
target_link_libraries(server ${QT_QTMAIN_LIBRARY})