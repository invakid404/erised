cmake_minimum_required(VERSION 3.16)
project(erised)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Network Widgets WebSockets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Network Qt5::Widgets Qt5::WebSockets)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

qt5_add_resources(QT_RESOURCES erised.qrc)

add_subdirectory(test-widget)
add_subdirectory(clock-widget)
add_subdirectory(weather-widget)

add_executable(${PROJECT_NAME} main.cpp server/server.cpp server/server.h server/handler.cpp server/handler.h widget/interface.h util/window.h widget/manager.cpp widget/manager.h style/global.h ${QT_RESOURCES} util/positioning.h util/http.h)

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
