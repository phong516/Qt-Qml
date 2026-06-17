cmake_minimum_required(VERSION 3.16)

project(learn VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QT_QML_GENERATE_QMLLS_INI ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Core5Compat)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(applearn
    main.cpp
)

qt_add_qml_module(applearn
    URI learn
    QML_FILES
        Main.qml
)

add_subdirectory(Todo)
target_link_libraries(applearn PRIVATE todoplugin)

qt_add_resources(applearn "qrc"
    PREFIX
        "/"
    FILES
        "resource/images.jpg"
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(applearn PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.applearn
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(applearn
    PRIVATE Qt6::Quick Qt6::Core5Compat
)

install(TARGETS applearn
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
