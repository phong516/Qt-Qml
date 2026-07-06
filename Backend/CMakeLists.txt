qt_add_qml_module(Backend
    URI Backend
    VERSION 1.0
    )

target_include_directories(Backend
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(manager)
add_subdirectory(model)
add_subdirectory(proxy)