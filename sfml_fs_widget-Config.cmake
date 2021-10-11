cmake_minimum_required(VERSION 3.15)

# Find SFML. Note: this handles all dependencies, libraries and include directories.
set(SFML_VERSION "2.5.1")

if (WIN32)
    # TODO: Make this a build option (the location of SFML)
    message("EXT_SFML: ${EXT_SFML}")
    if(NOT DEFINED EXT_SFML)
        set(SFML_DIR "external/compiled/SFML-${SFML_VERSION}/lib/cmake/SFML")
    else()
        message("Using ext")
        set(SFML_DIR "${EXT_SFML}")
    endif()
    find_package(SFML ${SFML_VERSION} COMPONENTS audio graphics window system REQUIRED)
else()
    include(FetchContent)
    FetchContent_Declare(
            sfml
            GIT_REPOSITORY "https://github.com/SFML/SFML.git"
            GIT_TAG        "${SFML_VERSION}"
    )

    FetchContent_GetProperties(sfml)
    if(NOT sfml_POPULATED)
        FetchContent_Populate(sfml)
        add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
    endif()
endif (WIN32)




add_library(sfml_fs_widget
        ${CMAKE_CURRENT_LIST_DIR}/FSWidget.cc
        ${CMAKE_CURRENT_LIST_DIR}/UiView.cc
        ${CMAKE_CURRENT_LIST_DIR}/VerticalTextList.cc
        ${CMAKE_CURRENT_LIST_DIR}/DrawUtil.cc
        ${CMAKE_CURRENT_LIST_DIR}/Controls.cc
)
target_include_directories(sfml_fs_widget PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(sfml_fs_widget sfml-audio sfml-graphics sfml-window sfml-system)
