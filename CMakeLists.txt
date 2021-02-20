cmake_minimum_required(VERSION 3.11)

project(fithofupro LANGUAGES CXX VERSION 0.1.0)

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
    src/projectfoldermodel.h
    src/mainwindow.ui
    src/main.cpp
    src/mainwindow.cpp
    src/projectfolderreadtask.cpp
    src/projectfoldermodel.cpp
    ${QRC_FILES}
    ${TS_FILES}
)

target_link_libraries(fithofupro PRIVATE Qt5::Widgets)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

SET(CMAKE_INSTALL_PREFIX /usr)
SET(DDM_DESKTOP_DIR "/usr/share/applications")
SET(DDM_PIXMAPS_DIR "/usr/share/icons")

install(TARGETS fithofupro)

install(FILES share/fithofupro.desktop DESTINATION ${DDM_DESKTOP_DIR})

install(FILES "${CMAKE_SOURCE_DIR}/res/fithofupro.png" DESTINATION ${DDM_PIXMAPS_DIR})

find_program(XDG-DESKTOP-MENU_EXECUTABLE xdg-desktop-menu)
install(CODE "
  execute_process(COMMAND ${XDG-DESKTOP-MENU_EXECUTABLE} install --novendor ${DDM_DESKTOP_DIR}/fithofupro.desktop)
  "
)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_PACKAGE_SECTION utils)
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Fight with your procrastination using non-effective methods!")

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_EXECUTABLE "fithofupro" "FiThoFuPro")
SET(CPACK_SET_DESTDIR TRUE)

INCLUDE(CPack)
