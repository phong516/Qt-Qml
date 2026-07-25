qt_add_qml_module(Backend
    STATIC
    URI Backend
    VERSION 1.0
    )

target_include_directories(Backend
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(manager)
add_subdirectory(model)
add_subdirectory(proxy)
add_subdirectory(storage)