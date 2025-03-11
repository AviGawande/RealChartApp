cmake_minimum_required(VERSION 3.16)

project(RealChartApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Quick Core Network)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appRealChartApp
    main.cpp
)

qt_add_qml_module(appRealChartApp
    URI RealChartApp
    VERSION 1.0
    QML_FILES
        Main.qml
        QML_FILES WaterfallChart.qml
        SOURCES datamodel.h datamodel.cpp
        QML_FILES
        SOURCES
        SOURCES udpreceiver.h udpreceiver.cpp
        QML_FILES
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appRealChartApp PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appRealChartApp
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appRealChartApp
    PRIVATE Qt6::Quick Qt6::Core Qt6::Gui Qt6::Network
)

include(GNUInstallDirs)
install(TARGETS appRealChartApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
