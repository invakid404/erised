cmake_minimum_required(VERSION 3.16)
project(weather_widget)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Network Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Network Qt5::Widgets)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

qt5_add_resources(QT_RESOURCES weather.qrc)

include_directories(../)

add_library(${PROJECT_NAME} SHARED weather.h ${QT_RESOURCES} icons.h)

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})