/**
 * @file myxml.h
 * @brief XML parser library header for C/C++.
 * This is a  C/C++ Xml Parser Library Header @c myxml.c.
 * @details This header provides all public API, types, macros, and
 * configuration for XML and supports both C and C++ usage.
 * @author Sackey Ezekiel -Etrue (djoezeke)
 * @date Thur 02 11:08:15 Oct GMT 2025
 * @version 0.1.0
 * @see https://www.github.com/djoezeke/myxml
 * @copyright Copyright (c) 2025 Sackey Ezekiel Etrue
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Usage:
 * @code
 *  #include <myxml.h>
 * @endcode
 *
 * Index of this file:
 *  [SECTION] Header mess
 *  [SECTION] Configurable macros
 *  [SECTION] Function Macros
 *  [SECTION] Imports/Exports
 *  [SECTION] Data Structures
 *  [SECTION] C Only Functions
 *  [SECTION] C++ Only Classes
 *
 *
 * Resources:
 * - Homepage ................... https://github.com/djoezeke/myxml
 * - Releases & changelog ....... https://github.com/djoezeke/myxml/releases
 * - Issues & support ........... https://github.com/djoezeke/myxml/issues
 *
 */

#ifndef DJOEZEKE_MYXML_H
#define DJOEZEKE_MYXML_H

// clang-format off

#ifndef MYXML_SKIP_VERSION_CHECK
    #if defined(MYXML_VERSION_MAJOR) && defined(MYXML_VERSION_MINOR) && defined(MYXML_VERSION_PATCH)
        #if MYXML_VERSION_MAJOR != 0 || MYXML_VERSION_MINOR != 1 || MYXML_VERSION_PATCH != 0
            #warning "Already included a different version of the library!"
        #endif
    #endif
#endif  // MYXML_SKIP_VERSION_CHECK

/**
 * @defgroup version Version Information
 * @brief Macros for library versioning.
 * @{
 */

/**
 * @def MYXML_VERSION_MAJOR
 * @brief Major version number of the library.
 * @note If this were Myyaml version 1.2.3, this value would be 1.
 * @since This macro is available since Myyaml 0.1.0.
 */
#define MYXML_VERSION_MAJOR 0

/**
 * @def MYXML_VERSION_MINOR
 * @brief Minor version number of the library.
 * @note If this were Myyaml version 1.2.3, this value would be 2.
 * @since This macro is available since Myyaml 0.1.0.
 */
#define MYXML_VERSION_MINOR 1

/**
 * @def MYXML_VERSION_PATCH
 * @brief Patch version number of the library.
 * @note If this were Myyaml version 1.2.3, this value would be 3.
 * @since This macro is available since Myyaml 0.1.0.
 */
#define MYXML_VERSION_PATCH 0

/**
 * @def MYXML_VERSION
 * @brief Library version string in the format @c "X.Y.Z",
 * where @c X is the major version number, @c Y is a minor version
 * number, and @c Z is the patch version number.
 * @sa MyGetVersion
 */
#define MYXML_VERSION "0.1.0"

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Header mess
//-----------------------------------------------------------------------------


#ifdef __cplusplus

#endif  //__cplusplus

//-----------------------------------------------------------------------------
// [SECTION] Configurable Macros
//-----------------------------------------------------------------------------

/**
 * @def MYXML_DISABLE_READER
 * @brief Exclude Reading/Deserialization XML methods.
 * Define as 1 to diable XML reader if parsing is not required.
 *
 * @warning This will disable these function at compile-time.
 *
 * @note This will reduce the binary size by about 60%.
 */
#ifndef MYXML_DISABLE_READER
#endif

/**
 * @def MYXML_DISABLE_WRITER
 * @brief Exclude Writing/Serialization XML methods.
 * Define as 1 to disable XML writer if XML serialization is not required.
 *
 * @warning This will disable these function at compile-time.
 *
 * @note This will reduce the binary size by about 30%.
 */
#ifndef MYXML_DISABLE_WRITER
#endif

/**
 * @def MYXML_DISABLE_ENCODING
 * @brief Exclude Encoding/UTF-8 XML methods.
 * Define as 1 to disable UTF-8 validation at compile time.
 *
 * @warning This will disable these function at compile-time.
 *
 * @note This will reduce the binary size by about 7%.
 */
#ifndef MYXML_DISABLE_ENCODING
#endif


//-----------------------------------------------------------------------------
// [SECTION] Import/Export
//-----------------------------------------------------------------------------

/**
 * @defgroup export Export Definitions
 * @{
 */

#if defined(_WIN32)
  	#define MYXML_API_EXPORT __declspec(dllexport)
  	#define MYXML_API_IMPORT __declspec(dllimport)
  	#define MYXML_NO_EXPORT
#else  // _WIN32
  	#define MYXML_API_EXPORT __attribute__((visibility("default")))
  	#define MYXML_API_IMPORT __attribute__((visibility("default")))
  	#define MYXML_NO_EXPORT __attribute__((visibility("hidden")))
#endif  // _WIN32

/**
 * @def MYXML_API
 * @brief Macro for public API symbol export/import.
 * @details Use this macro to annotate all public API functions for correct
 * symbol visibility on all platforms.
 */

#if defined(MYXML_BUILD_STATIC)
  	#define MYXML_API
#elif defined(MYXML_BUILD_SHARED) || defined(MYXML_EXPORTS)
  	/* We are building this library */
  	#define MYXML_API MYXML_API_EXPORT
#elif defined(MYXML_LOAD_SHARED) || defined(MYXML_IMPORTS)
  	/* We are using this library */
  	#define MYXML_API MYXML_API_IMPORT
#else  // MYXML_BUILD_STATIC
  	#define MYXML_API
#endif  // MYXML_BUILD_STATIC

/** @} */

// clang-format on

//-----------------------------------------------------------------------------
// [SECTION] Data Structures
//-----------------------------------------------------------------------------

/**
 * @defgroup basic Basic Types
 * @brief Core types and data structures for XML.
 * @{
 */

/**
 * Version numbering scheme.
 * @see https://semver.org/
 */
typedef struct myXmlVersion {
    int major;    /**< Significant changes */
    int minor;    /**< Incremental changes */
    int revision; /**< Bug fixes */
} myXmlVersion;

/** @} */

#if !defined(MYXML_DISABLE_READER) || !MYXML_DISABLE_READER

#endif  // MYXML_DISABLE_READER

#if !defined(MYXML_DISABLE_WRITER) || !MYXML_DISABLE_WRITER

#endif  // MYXML_DISABLE_WRITER

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] C Only Functions
//-----------------------------------------------------------------------------

#pragma region C

#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

#pragma region Error

#pragma endregion  // Error

#pragma region Document

#pragma endregion  // Document

#pragma region Node

#pragma endregion  // Node

#if !defined(MYXML_DISABLE_READER) || !MYXML_DISABLE_READER

#pragma region Reader

#pragma endregion  // Reader

#endif  // MYXML_DISABLE_READER

#if !defined(MYXML_DISABLE_WRITER) || !MYXML_DISABLE_WRITER

#pragma region Writer

#pragma endregion  // Writer

#endif  // MYXML_DISABLE_WRITER

#ifdef __cplusplus
};
#endif  //__cplusplus

#pragma endregion  // C

//-----------------------------------------------------------------------------
// [SECTION] C++ Only Classes
//-----------------------------------------------------------------------------

#pragma region Cpp

#ifdef __cplusplus

namespace myxml {

#pragma region Exception

#pragma endregion  // Exception

#pragma region Xml

#pragma endregion  // Xml

#if !defined(MYXML_DISABLE_READER) || !MYXML_DISABLE_READER

#pragma region Reader

#pragma endregion  // Reader

#endif  // MYXML_DISABLE_READER

#if !defined(MYXML_DISABLE_WRITER) || !MYXML_DISABLE_WRITER

#pragma region Writer

#pragma endregion  // Writer

#endif  // MYXML_DISABLE_WRITER

};  // namespace myxml

#endif  //__cplusplus

#pragma endregion  // Cpp

#endif  // DJOEZEKE_MYXML_H

/**
 * LICENSE: MIT License
 *
 * Copyright (c) 2025 Sackey Ezekiel Etrue
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */