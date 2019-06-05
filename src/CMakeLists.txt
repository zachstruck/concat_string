add_library(libconcat_string INTERFACE)

target_include_directories(libconcat_string
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(libconcat_string
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/zpp/concat_string.hpp
)
add_custom_target(libconcat_string-ide
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/zpp/concat_string.hpp
)
