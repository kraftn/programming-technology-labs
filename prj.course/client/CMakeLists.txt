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

QT5_WRAP_UI (CODE_UI client.ui settings.ui)

# Populate a CMake variable with the sources
set (client_SRCS main.cpp client.ui client.h client.cpp settings.ui settings.h settings.cpp subscriber.h subscriber.cpp)

# Tell CMake to create the client executable
add_executable(client WIN32 ${client_SRCS} ${CODE_UI})

set_property(TARGET client PROPERTY CXX_STANDARD 14)

# Use the libraries
target_link_libraries(client Qt5::Widgets)
target_link_libraries(client Qt5::Network)
target_link_libraries(client cppzmq)
target_link_libraries(client ${QT_QTMAIN_LIBRARY})