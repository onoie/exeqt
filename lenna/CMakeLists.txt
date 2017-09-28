cmake_minimum_required(VERSION 3.7)
project(lenna)

#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)#
set(CMAKE_PREFIX_PATH "~/Qt/5.9/gcc_64/")#
set(CMAKE_AUTOMOC ON)#
set(CMAKE_AUTOUIC ON)#
set(CMAKE_AUTORCC ON)#
set(CMAKE_INCLUDE_CURRENT_DIR ON)#

find_package( Qt5Core REQUIRED )#
find_package( Qt5Widgets REQUIRED )#
find_package( Qt5Gui REQUIRED )#
find_package( Qt5Network REQUIRED )#
find_package( Qt5OpenGL REQUIRED )#
find_package( Qt5WebView REQUIRED )#


set(SOURCE_FILES main.cpp mainwindow.h mainwindow.cpp slib.h)

#QT5_ADD_RESOURCES(RESOURCES resource_file.qrc)
QT5_ADD_RESOURCES(QRC resources/resource_file.qrc)

add_executable(lenna ${SOURCE_FILES} ${QRC})

target_link_libraries(lenna Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Network Qt5::OpenGL Qt5::WebView)#

#file(
#    COPY ${CMAKE_CURRENT_SOURCE_DIR}/img/lena.bmp
#    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/img
#)
#add_custom_command(
#    TARGET lenna POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy
#    ${CMAKE_SOURCE_DIR}/img/lena.bmp
#    ${CMAKE_CURRENT_BINARY_DIR}/img/lena.bmp
#)