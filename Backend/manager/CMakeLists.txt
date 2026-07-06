qt_add_qml_module(Manager
    STATIC
    URI Backend.Manager
    VERSION 1.0
    SOURCES
        TodoManager.hpp
        TodoManager.cpp
)

target_link_libraries(Manager
    PRIVATE
        Model
        Proxy
)