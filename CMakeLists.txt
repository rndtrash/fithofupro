cmake_minimum_required(VERSION 3.11)

project(fithofupro LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Gui Widgets LinguistTools REQUIRED)

file(GLOB_RECURSE TS_FILES CONFIGURE_DEPENDS ts/*.ts)
file(GLOB_RECURSE QRC_FILES CONFIGURE_DEPENDS res/*.qrc)

add_executable(fithofupro
    src/macro.h
    src/mainwindow.h
    src/projectfolderreadtask.h
    src/projectfoldertype.h
    src/mainwindow.ui
    src/main.cpp
    src/mainwindow.cpp
    src/projectfolderreadtask.cpp
    ${QRC_FILES}
    ${TS_FILES}
)

target_link_libraries(fithofupro PRIVATE Qt5::Widgets)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
