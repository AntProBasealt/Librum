# Qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)



# Configuration
set(QML_IMPORT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/presentation/modules ${CMAKE_CURRENT_BINARY_DIR}/" CACHE STRING "Qml modules")


# Dependencies
list(APPEND CMAKE_PREFIX_PATH "")
include(GNUInstallDirs)
#find_package(Qt6 6.2 REQUIRED COMPONENTS Quick)
find_package(QT NAMES Qt5 COMPONENTS Quick Widgets QuickControls2 REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Quick Widgets QuickControls2 REQUIRED)

configure_file(
    "${CMAKE_MODULE_PATH}/GPUIConfig.cmake.in"
    "${CMAKE_BINARY_DIR}/GPUIConfig.cmake"
    "${CMAKE_MODULE_PATH}/Qt6Config.cmake.in"
    "${CMAKE_BINARY_DIR}/Qt6Config.cmake"

    IMMEDIATE @ONLY)



# Language
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



# Configure and add subdirectories
set(OKULARCORE_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/application/core
    ${CMAKE_CURRENT_SOURCE_DIR}/application/core/core
    ${CMAKE_CURRENT_SOURCE_DIR}/application/core/gui
    ${CMAKE_CURRENT_BINARY_DIR}/application/core
    ${CMAKE_CURRENT_BINARY_DIR}/application/core/core
)

add_subdirectory(domain/)
get_target_property(DOMAIN_INCLUDES domain INTERFACE_INCLUDE_DIRECTORIES)

add_subdirectory(application/)
get_target_property(APPLICATION_INCLUDES application INTERFACE_INCLUDE_DIRECTORIES)

add_subdirectory(infrastructure/)
get_target_property(INFRASTRUCTURE_INCLUDES infrastructure INTERFACE_INCLUDE_DIRECTORIES)

add_subdirectory(adapters/)
get_target_property(ADAPTERS_INCLUDES adapters INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(ADAPTERS_BIN_DIR adapters CMAKE_BINARY_DIR)

add_subdirectory(presentation/)




# Building
add_executable(appLibrum
    main.cpp
    dependency_injection.hpp
    message_handler.hpp
)

target_compile_definitions(appLibrum
    PRIVATE
        $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)

target_link_libraries(appLibrum
    PRIVATE
        presentation
        adapters
        application
        infrastructure
        okularpart
        Qt5::Quick
        Qt5::Widgets
        Qt5::QuickControls2
)

target_include_directories(appLibrum
    PRIVATE
        ${ADAPTERS_INCLUDES}
        ${APPLICATION_INCLUDES}
        ${INFRASTRUCTURE_INCLUDES}
        ${OKULARCORE_INCLUDES}
)

target_compile_options(appLibrum PRIVATE "$<$<CONFIG:DEBUG>:${LIBRUM_SANITIZERS};-O0;-g>")
target_compile_options(appLibrum PRIVATE "$<$<CONFIG:RELEASE>:-O3>")

target_link_options(appLibrum PRIVATE "$<$<CONFIG:DEBUG>:${LIBRUM_SANITIZERS}>")



# Move fonts into binary dir    
include(CopyRecursive)
set(FONTS_OUT_DIR ${PROJECT_BINARY_DIR}/resources/fonts)
file(MAKE_DIRECTORY ${FONTS_OUT_DIR})
message(DEBUG "Folder created at ${FONTS_OUT_DIR}")
copy_recursive(${PROJECT_SOURCE_DIR}/resources/fonts ${FONTS_OUT_DIR} "*.otf")
