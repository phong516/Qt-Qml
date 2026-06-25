cmake_minimum_required(VERSION 3.16)

project(learn VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Core5Compat Core)

if(QT_VERSION VERSION_GREATER_EQUAL "6.4")
    set(QT_QML_GENERATE_QMLLS_INI ON)
endif()

if(QT_VERSION VERSION_GREATER_EQUAL "6.3")
    qt_standard_project_setup(REQUIRES 6.2)
else()
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)
endif()

qt_add_executable(applearn
    main.cpp
)

qt_add_qml_module(applearn
    URI learn
    VERSION 1.0
    QML_FILES
        Main.qml
)

add_subdirectory(Backend)
target_link_libraries(applearn PRIVATE Backend)

add_subdirectory(UI)
target_link_libraries(applearn PRIVATE UI)

add_subdirectory(Model)
target_link_libraries(applearn PRIVATE Model)

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
    # MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    # MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    # MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(applearn
    PRIVATE Qt6::Quick Qt6::Core5Compat Qt6::Core
)

install(TARGETS applearn
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
