#=============================================================================
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt
#=============================================================================

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
cmake_policy(VERSION 3.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release")
    message(STATUS "CMAKE_BUILD_TYPE not set, using ${CMAKE_BUILD_TYPE}")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS On)

project(Raptor VERSION 0.3.1 LANGUAGES CXX)

set(Boost_USE_STATIC_LIBS 1)

find_package(AdobeSourceLibraries REQUIRED CONFIG)
find_package(Boost 1.54 REQUIRED COMPONENTS program_options system OPTIONAL_COMPONENTS unit_test_framework)
find_package(ScanBuild QUIET)
find_package(BoostBook QUIET)
find_package(Git QUIET)

add_library(boost::boost INTERFACE IMPORTED)
set_target_properties(boost::boost PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${Boost_INCLUDE_DIR}"
    INTERFACE_COMPILE_DEFINITIONS "BOOST_ALL_NO_LIBS=1"
)
foreach(_lib IN ITEMS program_options system unit_test_framework)
    string(TOUPPER "${_lib}" _libup)
    add_library(boost::${_lib} INTERFACE IMPORTED)
    set_target_properties(boost::${_lib} PROPERTIES
        INTERFACE_LINK_LIBRARIES "boost::boost;$<$<CONFIG:Debug>:${Boost_${_libup}_LIBRARY_DEBUG}>;$<$<NOT:$<CONFIG:Debug>>:${Boost_${_libup}_LIBRARY_RELEASE}>"
    )
endforeach()

if(GIT_EXECUTABLE AND NOT TARGET Git::git)
    add_executable(Git::git IMPORTED)
    set_target_properties(Git::git PROPERTIES IMPORTED_LOCATION "${GIT_EXECUTABLE}")
endif()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

option(BUILD_TESTING "Enable unit tests" Off)
option(${PROJECT_NAME}_DEVELOPER "Enable extra targets for developers" Off)
mark_as_advanced(${PROJECT_NAME}_DEVELOPER)

if(BUILD_TESTING)
    enable_testing()
endif()

add_subdirectory(libs)
add_subdirectory(tools)
add_subdirectory(doc)

if(COMMAND add_scan_build)
    add_scan_build(scan-build)
    set_target_properties(${_target} PROPERTIES
        SCANBUILD_TITLE "${PROJECT_NAME}"
        SCANBUILD_STATUS_BUGS "Yes"
        SCANBUILD_BUILD_TYPE "Debug"
        SCANBUILD_DEFINES "${PROJECT_NAME}_DEVELOPER=No;BUILD_TESTING=Yes"
    )
endif()

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    COMPONENT "${PROJECT_NAME}-dev"
)
install(EXPORT ${PROJECT_NAME}
    NAMESPACE   ${PROJECT_NAME}::
    FILE        ${PROJECT_NAME}Targets.cmake
    DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/cmake
    COMPONENT   ${PROJECT_NAME}-dev
)

write_basic_package_version_file(
    ${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    ${PROJECT_NAME}Config.cmake.in
    ${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/cmake
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
    PATH_VARS CMAKE_INSTALL_INCLUDEDIR
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/cmake
)

if(NOT CPACK_GENERATOR)
    set(CPACK_GENERATOR "TGZ;ZIP")
endif()
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_NAME}")
set(CPACK_PACKAGE_VENDOR "Kiron")
# set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.txt")
# set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/Copyright.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${${PROJECT_NAME}_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${${PROJECT_NAME}_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${${PROJECT_NAME}_VERSION_PATCH}")
include(CPack)

