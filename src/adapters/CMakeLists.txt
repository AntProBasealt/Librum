# Dependencies
find_package(QT NAMES Qt5 COMPONENTS Core Quick Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Network REQUIRED)


# Build
add_library(adapters
                SHARED
                    interfaces/controllers/i_authentication_controller.hpp
                    interfaces/controllers/i_book_controller.hpp
                    interfaces/controllers/i_user_controller.hpp
                    interfaces/controllers/i_settings_controller.hpp
                    interfaces/persistance/i_user_storage_access.hpp
                    interfaces/persistance/i_book_storage_access.hpp
                    interfaces/persistance/i_authentication_access.hpp
                    
                    controllers/authentication_controller.cpp
                    controllers/authentication_controller.hpp
                    controllers/book_controller.cpp
                    controllers/book_controller.hpp
                    controllers/user_controller.cpp
                    controllers/user_controller.hpp
                    controllers/settings_controller.cpp
                    controllers/settings_controller.hpp
                    
                    gateways/user_storage_gateway.cpp
                    gateways/user_storage_gateway.hpp
                    gateways/authentication_gateway.cpp
                    gateways/authentication_gateway.hpp
                    gateways/book_storage_gateway.cpp
                    gateways/book_storage_gateway.hpp
                    
                    data_models/app_information.hpp
                    data_models/library_model/library_model.cpp
                    data_models/library_model/library_model.hpp
                    data_models/library_model/library_proxy_model.cpp
                    data_models/library_model/library_proxy_model.hpp
                    data_models/library_model/filter_request.hpp
                    data_models/user_tags_model/user_tags_model.cpp
                    data_models/user_tags_model/user_tags_model.hpp
                    data_models/shortcuts_model/shortcuts_model.cpp
                    data_models/shortcuts_model/shortcuts_model.hpp
                    data_models/shortcuts_model/shortcuts_proxy_model.cpp
                    data_models/shortcuts_model/shortcuts_proxy_model.hpp
                    
                    DTOs/login_dto.hpp
                    DTOs/register_dto.hpp
                    DTOs/book_dto.hpp
                    DTOs/tag_dto.hpp
)

target_include_directories(adapters
                PUBLIC
                    ${CMAKE_CURRENT_SOURCE_DIR}/interfaces/persistance
                    ${CMAKE_CURRENT_SOURCE_DIR}/interfaces/controllers
                    ${CMAKE_CURRENT_SOURCE_DIR}/controllers
                    ${CMAKE_CURRENT_SOURCE_DIR}/gateways
                    ${CMAKE_CURRENT_SOURCE_DIR}/DTOs
                    ${CMAKE_CURRENT_SOURCE_DIR}/data_models/library_model
                    ${CMAKE_CURRENT_SOURCE_DIR}/data_models/user_tags_model
                    ${CMAKE_CURRENT_SOURCE_DIR}/data_models/shortcuts_model
                    ${CMAKE_CURRENT_SOURCE_DIR}/data_models
                PRIVATE
                    ${CMAKE_CURRENT_SOURCE_DIR}
                    ${DOMAIN_INCLUDES}
                    ${APPLICATION_INCLUDES}
)

target_compile_definitions(adapters
                PRIVATE
                    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)

target_link_libraries(adapters
                PRIVATE
                    domain
                    application
                    rapidfuzz::rapidfuzz
                    Qt5::Core
                    Qt5::Quick
                    Qt5::Network
)

target_compile_options(adapters PRIVATE "$<$<CONFIG:DEBUG>:${LIBRUM_WARNINGS};${LIBRUM_SANITIZERS};${COVERAGE_COMPILE_OPTIONS};-O0;-g>")
target_compile_options(adapters PRIVATE "$<$<CONFIG:RELEASE>:-O3>")

target_link_options(adapters PRIVATE "${COVERAGE_LINKING_OPTIONS}")


# Generate code coverage
if (ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU") # Only works when the compiler is GCC
    include(CodeCoverage)
    append_coverage_compiler_flags_to_target(adapters)
    setup_target_for_coverage_gcovr_html(
              NAME adapters_coverage
              EXECUTABLE adapters_unit_tests
              BASE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
              EXCLUDE ${PROJECT_BINARY_DIR}/* ${PROJECT_SOURCE_DIR}/libs/*)
endif()