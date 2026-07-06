add_subdirectory(manager)
add_subdirectory(model)
add_subdirectory(proxy)

qt_add_qml_module(Backend
    URI Backend
    VERSION 1.0
    )