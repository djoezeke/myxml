# ===================================================================
# Copyright © 2025 Sackey Ezekiel Etrue
# Distributed under the terms of the MIT license.
# ===================================================================

cmake_minimum_required(VERSION 3.16...4.1.1 FATAL_ERROR)

# TODO: Add UTF-8 encoding support for supported compilers.
# TODO: Set compiler according C++11 support. include(CheckCXXCompilerFlag)
# TODO: Set compiler according C11 support. include(CheckCCompilerFlag)
# TODO: Use Cmake Dependent Option. include(CMakeDependentOption)
# TODO: Enable Custom Compiler Warning Flags
# TODO: Enable Address Sanitizers.
# TODO: Run Clang-tidy and Clang-format.
# TODO: Add C++ Modules Support (optional).
# TODO: Add debug view definition file for msvc (natvis)
# TODO: Use a custom package version config file instead
# TODO: Execute test suite with Valgrind.

# include(CheckLibraryExists)
# include(CheckIncludeFile)
# include(CheckLanguage)

# define a macro that helps defining an option
macro(myxml_set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

#--------------------------------------------------------------------
# Project and version.
#--------------------------------------------------------------------

# set a default build type if none was provided
# this has to be done before the project() instruction!
myxml_set_option(CMAKE_BUILD_TYPE Release STRING "Choose the type of build (Debug or Release)")

set (MYXML_VERSION_MAJOR 0)
set (MYXML_VERSION_MINOR 1)
set (MYXML_VERSION_PATCH 1)
set (MYXML_VERSION_STRING "0.1.0")

project(Myxml
        VERSION ${MYXML_VERSION_STRING} 
        DESCRIPTION "Xml parser for C/C++"
        HOMEPAGE_URL "https://github.com/djoezeke/myxml"
        LANGUAGES  C CXX
)

#--------------------------------------------------------------------
# Preparations depending on the specified build options  
#--------------------------------------------------------------------

# Check if this project is the main project
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(MYXML_IS_TOP_LEVEL ON)
else()
  set(MYXML_IS_TOP_LEVEL OFF)
endif()

# Add UTF-8 encoding support for MSVC compiler.
# This ensures that the MSVC compiler interprets source files as UTF-8 encoded,
# which is useful for projects containing non-ASCII characters in source files.
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# we use the paths from the cmake GNUInstallDirs library as defaults
# you can override these if you like
# https://cmake.org/cmake/help/latest/library/GNUInstallDirs.html
include(GNUInstallDirs)

include(CMakeDependentOption)

#--------------------------------------------------------------------
# Configure variables for the library   
#--------------------------------------------------------------------

myxml_set_option(MYXML_ENABLE_WARNING ${MYXML_IS_TOP_LEVEL} BOOL "ON to enable warning messages.")

myxml_set_option(MYXML_BUILD_CMYXML ON BOOL "ON to build MYXMLC")

# add an option for choosing the build type (shared or static)
myxml_set_option(MYXML_BUILD_SHARED ON BOOL "ON to build MYXML as shared libraries, OFF to build it as static libraries")

# add an option for linking to myxml either statically or dynamically
set(LINK_STATICALLY_DEFAULT ON)
myxml_set_option(CMYXML_LINK_MYXML_STATICALLY ${LINK_STATICALLY_DEFAULT} BOOL "ON to link to a static version of MYXML, OFF to link dynamically")

myxml_set_option(MYXML_INSTALL ${MYXML_IS_TOP_LEVEL} BOOL "ON to Generate installation target" )
cmake_dependent_option(MYXML_INSTALL_DOCS "Install docs for Myxml" ${MYXML_IS_TOP_LEVEL} "MYXML_INSTALL" ON)
cmake_dependent_option(MYXML_INSTALL_TESTS "Install test-cases" ${MYXML_IS_TOP_LEVEL} "MYXML_INSTALL" ON)
cmake_dependent_option(MYXML_INSTALL_CPACK "Create binary Myxml archive using CPack" ${MYXML_IS_TOP_LEVEL} "MYXML_INSTALL" ON)

# option(MYXML_BUILD_SHARED "Build shared library" ${MYXML_IS_TOP_LEVEL})
# option(MYXML_BUILD_DEBUG "Build debug version of library" ${MYXML_IS_TOP_LEVEL})
# option(MYXML_ENABLE_DOXYGEN "Build documentation with Doxygen." ${MYXML_IS_TOP_LEVEL})

option(MYXML_BUILD_C11 "Build Myxml with C11" OFF)
option(MYXML_BUILD_C17 "Build Myxml with C17" OFF)
option(MYXML_BUILD_C23 "Build Myxml with C23" OFF)

option(MYXML_BUILD_CXX11 "Build Myxml with C++11" OFF)
option(MYXML_BUILD_CXX14 "Build Myxml with C++14" OFF)
option(MYXML_BUILD_CXX17 "Build Myxml with C++17" OFF)
option(MYXML_BUILD_CXX20 "Build Myxml with C++20" OFF)
option(MYXML_BUILD_CXX23 "Build Myxml with C++23" OFF)

# Set required C standard
if(MYXML_BUILD_C23)
    set(CMAKE_C_STANDARD 23)
elseif(MYXML_BUILD_C17)
    set(CMAKE_C_STANDARD 17)
elseif(MYXML_BUILD_C11)
    set(CMAKE_C_STANDARD 11)
else()
    set(CMAKE_C_STANDARD 17)
endif()
set(CMAKE_C_STANDARD_REQUIRED TRUE)

# Set required C++ standard
if(MYXML_BUILD_CXX23)
    set(CMAKE_CXX_STANDARD 23)
elseif(MYXML_BUILD_CXX20)
    set(CMAKE_CXX_STANDARD 20)
elseif(MYXML_BUILD_CXX17)
    set(CMAKE_CXX_STANDARD 17)
elseif(MYXML_BUILD_CXX14)
    set(CMAKE_CXX_STANDARD 14)
elseif(MYXML_BUILD_CXX11)
    set(CMAKE_CXX_STANDARD 11)
else()
    set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if(DEFINED BUILD_SHARED_LIBS)
    # When defined, use BUILD_SHARED_LIBS as default
    if(BUILD_SHARED_LIBS)
        set(MYXML_STATIC OFF)
    else()
        set(MYXML_STATIC ON)
    endif()
else()
    # Default to just building the static library
    set(MYXML_STATIC ON)
endif()

# Add compiler warnings
if(MYXML_ENABLE_WARNINGS)
    if(MSVC)
        set(MYXML_WARNINGS /WX /W4 /permissive-)
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
        set(MYXML_WARNINGS -Werror -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion)
    endif()
endif()

option(MYXML_ENABLE_SANITIZERS "Enable sanitizers" OFF)
if(MYXML_ENABLE_SANITIZERS)
    string(APPEND CMAKE_CXX_FLAGS " -fno-omit-frame-pointer -fno-sanitize-recover=all -fsanitize=undefined")
endif()

option(MYXML_ENABLE_STDLIB_ASSERTIONS "Enable standard library assertions" OFF)
if(MYXML_ENABLE_STDLIB_ASSERTIONS)
    # intentionally using `add_compile_definitions` here to propagate defines to subdirectories
    add_compile_definitions(_GLIBCXX_ASSERTIONS=1)                                   # see https://gcc.gnu.org/wiki/LibstdcxxDebugMode

    # Xcode has a property to control this - adding the define ourselves causes multiple definitions
    if(XCODE)
        set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_STANDARD_LIBRARY_HARDENING "Yes (extensive)")
    else()
        add_compile_definitions(_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE) # see https://libcxx.llvm.org/Hardening.html
    endif()
endif()

set(MYXML_CMAKE_CONFIG_NAME "${PROJECT_NAME}Config")
set(MYXML_CMAKE_TARGET_NAME "${PROJECT_NAME}Target")

set(MYXML_INCLUDE_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(MYXML_INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}")
set(MYXML_CONFIG_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}" CACHE INTERNAL "Install directory path for config files.")

set(MYXML_CMAKE_CONFIG_TEMPLATE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(MYXML_CMAKE_CONFIG_TEMPLATE "${MYXML_CMAKE_CONFIG_TEMPLATE_DIR}/${MYXML_CMAKE_CONFIG_NAME}.cmake.in")
set(MYXML_CMAKE_VERSION_CONFIG_TEMPLATE "${MYXML_CMAKE_CONFIG_TEMPLATE_DIR}/${MYXML_CMAKE_CONFIG_NAME}Version.cmake.in")
set(MYXML_CMAKE_PACKAGE_CONFIG_TEMPLATE "${MYXML_CMAKE_CONFIG_TEMPLATE_DIR}/pkg-config.pc.in")

set(MYXML_CMAKE_CONFIG_DIR  ${CMAKE_CURRENT_BINARY_DIR})
set(MYXML_CMAKE_CONFIG_FILE  ${MYXML_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Config.cmake)
set(MYXML_CMAKE_TARGETS_FILE  ${MYXML_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Targets.cmake)
set(MYXML_CMAKE_PACKAGE_FILE  ${MYXML_CMAKE_CONFIG_DIR}/${PROJECT_NAME}.pc)
set(MYXML_CMAKE_VERSION_CONFIG_FILE  ${MYXML_CMAKE_CONFIG_DIR}/${PROJECT_NAME}ConfigVersion.cmake)

#--------------------------------------------------------------------
# Macro to Build libraries
#--------------------------------------------------------------------

include(CMakeParseArguments)

# example: myxml_make_library(Myxml
#                       SOURCES myxmlc.cpp ...
#                       DEPENDS Myxml::MyxmlC
#                       [STATIC]) # Always create a static library
macro(myxml_make_library library)

    # parse the arguments
    cmake_parse_arguments(THIS "" "DEPENDS" "SOURCES" ${ARGN})
    if(NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments when calling myxml_make_library: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    # create the target
    string(TOLOWER ${library} target)
    if(MYXML_STATIC)
        add_library(${target} STATIC ${THIS_SOURCES})
    else()
        add_library(${target} SHARED ${THIS_SOURCES})
    endif()
    add_library(Myxml::${library} ALIAS ${target})

    # require C11 support
    target_compile_features(${target} PUBLIC c_std_11)

    # enable C++17 support
    target_compile_features(${target} PUBLIC cxx_std_17)

    # define the export symbol of the library
    string(REPLACE "-" "_" NAME_UPPER "${target}")
    string(TOUPPER "${NAME_UPPER}" NAME_UPPER)
    set_target_properties(${target} PROPERTIES DEFINE_SYMBOL ${NAME_UPPER}_EXPORTS)

    # define the export name of the library
    set_target_properties(${target} PROPERTIES EXPORT_NAME Myxml::${library})

    # set the target's folder (for IDEs that support it, e.g. Visual Studio)
    set_target_properties(${target} PROPERTIES FOLDER "Myxml")

    # add <project>/include as public include directory
    target_include_directories(${target} 
        PUBLIC $<BUILD_INTERFACE:${MYXML_INCLUDE_BUILD_DIR}>
        INTERFACE $<INSTALL_INTERFACE:${MYXML_INCLUDE_INSTALL_DIR}>
    )

    if(NOT MYXML_STATIC)
        set_target_properties(${target} PROPERTIES DEBUG_POSTFIX -d)
        if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
            # include the major version number in Windows shared library names (but not import library names)
            set_target_properties(${target} PROPERTIES SUFFIX "-${PROJECT_VERSION_MAJOR}${CMAKE_SHARED_LIBRARY_SUFFIX}")

            # on Windows/gcc get rid of "lib" prefix for shared libraries,
            # and transform the ".dll.a" suffix into ".a" for import libraries
            if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
                set_target_properties(${target} PROPERTIES PREFIX "")
                set_target_properties(${target} PROPERTIES IMPORT_SUFFIX ".a")
            endif()
        endif()
    else()
        set_target_properties(${target} PROPERTIES DEBUG_POSTFIX -d)
        set_target_properties(${target} PROPERTIES RELEASE_POSTFIX "")
        set_target_properties(${target} PROPERTIES MINSIZEREL_POSTFIX "")
        set_target_properties(${target} PROPERTIES RELWITHDEBINFO_POSTFIX "")
    endif()

    # set the version and soversion of the target (for compatible systems -- mostly Linuxes)
    set_target_properties(${target} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
    set_target_properties(${target} PROPERTIES VERSION ${PROJECT_VERSION})

    foreach(WARNING ${MYXML_WARNINGS})
        set_target_properties(${target} PROPERTIES APPEND_STRING COMPILE_FLAGS " ${WARNING}")
    endforeach()

    if(NOT MYXML_STATIC)
        # define MYXML_BUILD_SHARED if the build type is set to 'shared'
        target_compile_definitions(${target} PRIVATE MYXML_BUILD_SHARED)
        set_target_properties(${target} PROPERTIES DEFINE_SYMBOL MYXML_BUILD_SHARED)
    else()
        # define MYXML_BUILD_STATIC if the build type is set to 'static'
        target_compile_definitions(${target} PRIVATE MYXML_BUILD_STATIC)
        set_target_properties(${target} PROPERTIES DEFINE_SYMBOL MYXML_BUILD_STATIC)
    endif()

    # Enable support for UTF-8 characters in source code
    if(MSVC)
        target_compile_options(${target} PRIVATE /utf-8)
    endif()
endmacro()

#--------------------------------------------------------------------
# Build library targets
#--------------------------------------------------------------------

# If both shared and static libs are build at once with MSVC it generates a
# shared library consisting of
#
# * a DLL (that contains the actual code) with filename suffix `.dll`,
# * a correspoding import library (against which users should link) with
#   filename suffix `.lib`.
#
# and a static library with filename suffix `.lib`
#
# As both, the shared import library and the static library share the same
# basename and suffix one would overwrite the other.
#
# To solve this issue we set the PREFIX for *static* libs explicitely so MSVC
# will build:
#
# * shared: myxml.dll
# * import: myxml.lib
# * static: libmyxml.lib
#
# and this for debug:
#
# * shared: myxml-d.dll
# * import: myxml-d.lib
# * static: libmyxml-d.lib
#
# As all other platforms already set `PREFIX` for all lib types they remain
# unchanged. Therefore no `if(MSVC)` check is needed here.

if(NOT (MYXML_STATIC OR BUILD_SHARED_LIBS))
    message(FATAL_ERROR "MYXML_STATIC and BUILD_SHARED_LIBS cannot both be disabled")
endif()

# define the myxml target
myxml_make_library(Myxml
                    SOURCES src/myxml.cpp
                    )

# define the myxmlc target
myxml_make_library(MyxmlC
                    SOURCES src/myxmlc.cpp
                    DEPENDS Myxml::Myxml
                    )

#--------------------------------------------------------------------
# Configurations
#--------------------------------------------------------------------

# Default to build type "Release" unless tests are being built
if(NOT CMAKE_BUILD_TYPE)
	if (NOT MYXML_BUILD_TESTS)
		message(STATUS "No build type selected, default to Release")
		set(CMAKE_BUILD_TYPE "Release")
	else()
		message(STATUS "No build type selected but tests are being built, default to Debug")
		set(CMAKE_BUILD_TYPE "Debug")
	endif()
endif()

# Output directories for a build tree
if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif()

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

#--------------------------------------------------------------------
# Add Project subdirectories
#--------------------------------------------------------------------

# add an option for building the API documentation
myxml_set_option(MYXML_BUILD_DOCS OFF BOOL "ON to generate the API documentation, OFF to ignore it")

# Build the documentation   
if(MYXML_BUILD_DOCS)
    add_subdirectory(docs)
endif()

# add an option for building the examples
myxml_set_option(MYXML_BUILD_EXAMPLES OFF BOOL "ON to build the CMYXML examples, OFF to ignore them")

# Build the example apps   
if(MYXML_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# add an option for building the tests
myxml_set_option(MYXML_BUILD_TESTS OFF BOOL "ON to build the CMYXML test suite, OFF to ignore it")

# Build the test apps   
if(MYXML_BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)

    # Set the unit test app project as the Visual Studio startup project
    # if the target compiler is some version of Microsoft Visual C++ and
    # if this project is the main project.
    if(MSVC AND CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MyxmlUnitTest)
    endif()
endif()

#--------------------------------------------------------------------
# Install a pkg-config file
#--------------------------------------------------------------------

#--------------------------------------------------------------------
# Configure package.
#--------------------------------------------------------------------
include(CMakePackageConfigHelpers)

configure_file(
    ${MYXML_CMAKE_CONFIG_TEMPLATE}
    ${MYXML_CMAKE_CONFIG_FILE}
    @ONLY
)

configure_file(
    ${MYXML_CMAKE_VERSION_CONFIG_TEMPLATE}
    ${MYXML_CMAKE_VERSION_CONFIG_FILE}
    @ONLY
)

configure_file(
    "${MYXML_CMAKE_PACKAGE_CONFIG_TEMPLATE}"
    "${MYXML_CMAKE_PACKAGE_FILE}"
)

#--------------------------------------------------------------------
# Install package.
#--------------------------------------------------------------------

if(MYXML_INSTALL)
    # install(
    #     DIRECTORY ${MYXML_INCLUDE_BUILD_DIR}
    #     DESTINATION ${MYXML_INCLUDE_INSTALL_DIR}
    # )

    # install(
    #     FILES ${MYXML_CMAKE_CONFIG_FILE} ${MYXML_CMAKE_VERSION_CONFIG_FILE}
    #     DESTINATION ${MYXML_CONFIG_INSTALL_DIR}
    # )

    # export(
    #     TARGETS ${MYXML_TARGET_NAME}
    #     NAMESPACE ${PROJECT_NAME}::
    #     FILE ${MYXML_CMAKE_TARGETS_FILE}
    # )

    # install(
    #     TARGETS ${MYXML_TARGET_NAME}
    #     EXPORT ${MYXML_CMAKE_TARGET_NAME}
    # )

    # install(
    #     EXPORT ${MYXML_CMAKE_TARGET_NAME}
    #     NAMESPACE ${PROJECT_NAME}::
    #     DESTINATION ${MYXML_CONFIG_INSTALL_DIR}
    # )

    # install(
    #     FILES "${MYXML_CMAKE_PACKAGE_FILE}"
    #     DESTINATION ${MYXML_CONFIG_INSTALL_DIR}
    # )

    if(MYXML_INSTALL_CPACK)
        SET(CPACK_PACKAGE_NAME "Myxml")
        set(CPACK_PACKAGE_NAME_SUMMARY "Simple and Fast Xml Parser")
        SET(CPACK_PACKAGE_CONTACT "djoezeke")
        set(CPACK_PACKAGE_VENDOR "Myxml Contributers")
        set(CPACK_PACKAGE_FILE_NAME "myxml-${PROJECT_VERSION}")
        set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
        set(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
        set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
        SET(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
        set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
        set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
        set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
        set(CPACK_PACKAGE_INSTALL_DIRECTORY "Myxml ${PROJECT_VERSION}")
        # set(CPACK_MONOLITHIC_INSTALL ON)
        SET(CPACK_GENERATOR "ZIP;TGZ;DEB;RPM") # Remove this, if you want the NSIS installer on Windows
        SET(CPACK_DEBIAN_PACKAGE_SHLIBDEPS OFF) # can be used to generate deps, slow and requires tools.
        SET(CPACK_DEBIAN_PACKAGE_NAME "lib${CPACK_PACKAGE_NAME}-dev")
        SET(CPACK_RPM_PACKAGE_NAME "lib${CPACK_PACKAGE_NAME}-devel")

        include(CPack)

    endif()

endif()


install(FILES LICENSE DESTINATION ${CMAKE_INSTALL_DOCDIR})
install(FILES README.md DESTINATION ${CMAKE_INSTALL_DOCDIR})

#--------------------------------------------------------------------
# Package with CPack.
#--------------------------------------------------------------------
# TODO : Add Packing with CPack

#--------------------------------------------------------------------
# Uninstall Target
#--------------------------------------------------------------------

if(MYXML_UNINSTALL)
    if(NOT TARGET uninstall)
        configure_file(cmake/cmake_uninstall.cmake.in cmake_uninstall.cmake IMMEDIATE @ONLY)

        add_custom_target(uninstall
            COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")
    endif()
endif()

#--------------------------------------------------------------------
# Clang CI
#--------------------------------------------------------------------

myxml_set_option(CLANG_FORMAT_EXECUTABLE clang-format STRING "Override clang-format executable, requires version 17")
add_custom_target(format
    COMMAND ${CMAKE_COMMAND} -DCLANG_FORMAT_EXECUTABLE=${CLANG_FORMAT_EXECUTABLE} -P ./cmake/Format.cmake
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} VERBATIM)

myxml_set_option(CLANG_TIDY_EXECUTABLE clang-tidy STRING "Override clang-tidy executable, requires minimum version 14")
add_custom_target(tidy
    COMMAND ${CMAKE_COMMAND} -DCLANG_TIDY_EXECUTABLE=${CLANG_TIDY_EXECUTABLE} -DPROJECT_BINARY_DIR=${PROJECT_BINARY_DIR} -P ./cmake/Tidy.cmake
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} VERBATIM)
