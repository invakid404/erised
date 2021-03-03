cmake_minimum_required(VERSION 3.16)
project(test_widget)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Widgets)

include_directories(../)

add_library(${PROJECT_NAME} SHARED test.h)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
