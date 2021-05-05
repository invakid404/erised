cmake_minimum_required(VERSION 3.16)
project(erised)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets WebSockets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::WebSockets OpenSSL::Crypto)
set(MIN_OPENSSL_VERSION 1.1.1)

add_subdirectory(test-widget)

add_executable(${PROJECT_NAME} main.cpp server/server.cpp server/server.h server/handler.cpp server/handler.h widget/interface.h widget/loader.h util/window.h util/password.h util/random.h util/byte_array.h util/config.h)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
find_package(OpenSSL ${MIN_OPENSSL_VERSION} REQUIRED)

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
