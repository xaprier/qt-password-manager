cmake_minimum_required(VERSION 3.5)

project(qt-password-manager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(lib) # compile libs

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

# 4 - add qm file to qrc file and load it in code
file(GLOB CPP_HILES "src/*.cpp")
file(GLOB HPP_HILES "include/*.hpp")
file(GLOB UI_HILES "design/*.ui")
file(GLOB QRC_HILES "**/*.qrc")
file(GLOB TS_FILES "translations/*.ts")

set(PROJECT_SOURCES
    ${CPP_HILES} ${HPP_HILES} ${UI_HILES} ${QRC_HILES}
)

set(LANGS tr de)

# 1 - first create an translation file to translate texts.
set(QM_FILES "")

foreach(LANG ${LANGS})
    qt_create_translation(QM_FILE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/translations/translation_${LANG}.ts)
    list(APPEND QM_FILES ${QM_FILE})
endforeach()

# 2 - translate files using linguist

# 3 - after translate and build we should configure file to get file to correct directory
foreach(QM_FILE ${QM_FILES})
    if(EXISTS ${QM_FILE})
        configure_file(${QM_FILE} ${CMAKE_SOURCE_DIR}/translations COPYONLY)
    else()
        list(APPEND PROJECT_SOURCES ${TS_FILES} ${QM_FILES})
    endif()
endforeach()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

# Define target properties for Android with Qt 6 as:
# set_property(TARGET qt-password-manager APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
# CMAKE_CURRENT_SOURCE_DIR/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )

    # Define properties for Android with Qt 5 after find_package() calls as:
    # set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Cipher JSONHandler)
target_include_directories(${PROJECT_NAME} PRIVATE include)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER https://xaprier.dev
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
