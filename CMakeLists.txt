cmake_minimum_required(VERSION 3.14)

project(SimpleDownloadManager VERSION 0.1 LANGUAGES CXX)

include(FindPkgConfig)
pkg_check_modules(CURLPP REQUIRED curlpp)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR}Network)


set(PROJECT_SOURCES
        main.cpp
        qml.qrc
        Core/DownloaderCore.h Core/DownloaderCore.cpp
        Network/FileDownloader.h Network/FileDownloader.cpp
        Core/DownloaderWrapper.h Core/DownloaderWrapper.cpp
        Core/FileDownloaderModel.h Core/FileDownloaderModel.cpp
        Network/DownloadItemWrapper.h Network/DownloadItemWrapper.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SimpleDownloadManager
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SimpleDownloadManager APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SimpleDownloadManager SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SimpleDownloadManager
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(SimpleDownloadManager
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(SimpleDownloadManager
  PRIVATE Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Quick
  Qt${QT_VERSION_MAJOR}::Network
  ${CURLPP_LDFLAGS}
  )

set_target_properties(SimpleDownloadManager PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(SimpleDownloadManager)
    qt_finalize_executable(SimpleDownloadManager)
endif()
