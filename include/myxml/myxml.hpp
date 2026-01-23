/**
 * @file myxml.hpp
 * @brief XML For Modern C/C++.
 * @details All public API, types, macros, and configuration.
 * @author Sackey Ezekiel Etrue (djoezeke)
 * @version 0.1.0
 * @see https://www.github.com/djoezeke/myxml
 * @copyright Copyright (c) 2025 Sackey Ezekiel Etrue
 *
 * Developed by Sackey Ezekiel Etrue and every direct or indirect contributors to the GitHub.
 * See LICENSE for copyright and licensing details (standard MIT License).
 *
 * MYXML: What this Is
 *
 * DOCUMENTATION:
 *
 * FEATURES:
 *
 * MISSION:
 *
 * ISSUES:
 *
 * NOTES:
 *
 * USAGE:
 *
 * FAQS:
 *
 * HELP:
 *    - See links below.
 *    - Read top of myxml.cpp for more details and comments.
 *
 *  Has only had a few tests run, may have issues.
 *
 *  If having issues compiling/linking/running raise an issue (https://github.com/djoezeke/myxml/issues).
 *  Please post in https://github.com/djoezeke/myxml/discussions if you cannot find a solution in resources above.
 *
 * RESOURCES:
 * - Homepage ................... https://github.com/djoezeke/myxml
 * - Releases & changelog ....... https://github.com/djoezeke/myxml/releases
 * - Issues & support ........... https://github.com/djoezeke/myxml/issues
 *
 */

#ifndef DJOEZEKE_MYXML_HPP

/**
 * [SECTIONS] Index of this file
 *
 *  SECTION: Include Mess
 *  SECTION: Configurations
 *  SECTION: Function Macros
 *  SECTION: Platform Defines
 *  SECTION: Standard Defines
 *  SECTION: Compiler Defines
 *  SECTION: Compiler Warnings
 *  SECTION: Compiler Attributes
 *  SECTION: API Imports/Exports
 *
 *  Forward: Forward Declarations
 *
 *  SECTION: Details Declarations
 *  SECTION: Myxml Declarations
 *  SECTION: Literals Declarations
 *
 *  Details: Details API Namespace
 *
 *  SECTION: Flags & Enumerations
 *  SECTION: Data Structures
 *  SECTION: Function Declarations
 *
 *  Myxml: Myxml API Namespace
 *
 *  SECTION: Flags & Enumerations
 *  SECTION: Data Structures
 *  SECTION: Function Declarations
 *
 *  Literals: Literals API Namespace
 *
 *  SECTION: Function Declarations
 *
 */

#define DJOEZEKE_MYXML_HPP

// clang-format off

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
    #define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef MYXML_SKIP_VERSION_CHECK
    #if defined(MYXML_VERSION_MAJOR) && defined(MYXML_VERSION_MINOR) && defined(MYXML_VERSION_PATCH)
        #if MYXML_VERSION_MAJOR != 1 || MYXML_VERSION_MINOR != 0 || MYXML_VERSION_PATCH != 0
            #warning "Already included a different version of the library!"
        #endif
    #endif
#endif  // MYXML_SKIP_VERSION_CHECK

/**
 * @defgroup version version Information
 * @brief Macros for library versioning.
 * @{
 */

/**
 * @def MYXML_VERSION_MAJOR
 * @brief Major version number of the library.
 * @note If this were version 1.2.3, this value would be 1.
 * @since This macro is available since 0.1.0 .
 */
#ifndef MYXML_VERSION_MAJOR
    #define MYXML_VERSION_MAJOR 0
#endif // MYXML_VERSION_MAJOR

/**
 * @def MYXML_VERSION_MINOR
 * @brief Minor version number of the library.
 * @note If this were version 1.2.3, this value would be 2.
 * @since This macro is available since 0.1.0 .
 */
#ifndef MYXML_VERSION_MINOR
    #define MYXML_VERSION_MINOR 1
#endif // MYXML_VERSION_MINOR

/**
 * @def MYXML_VERSION_PATCH
 * @brief Patch version number of the library.
 * @note If this were version 1.2.3, this value would be 3.
 * @since This macro is available since 0.1.0 .
 */
#ifndef MYXML_VERSION_PATCH
    #define MYXML_VERSION_PATCH 0
#endif // MYXML_VERSION_PATCH

/**
 * @def MYXML_VERSION
 * @brief Library version string in the format @c "X.Y.Z",
 * where @c X is the major version number, @c Y is a minor version
 * number, and @c Z is the patch version number.
 * @sa MyGetVersion
 */
#ifndef MYXML_VERSION
    #define MYXML_VERSION "0.1.0"
#endif // MYXML_VERSION

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Include Mess
//-----------------------------------------------------------------------------

#include <exception>
#include <functional>
#include <ostream>
#include <istream>

#include <stdio.h>
#include <stdint.h>
// #include <uchar.h> // char16_t, char32_t
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <iostream>

#include <optional>

//-----------------------------------------------------------------------------
// [SECTION] Configurations
//-----------------------------------------------------------------------------

/**
 * @defgroup configure Library Configurations
 * @{
 */

/**
 * @def MYXML_DISABLE_READER
 * @brief Exclude Reading/Deserialization APIs.
 *
 * Define to 1 to remove reader/parsing code at compile time when parsing
 * is not required. This reduces the compiled binary size.
 *
 * Example:
 * @code
 * #define MYXML_DISABLE_READER 1
 * #include <myxml/myxml.hpp>
 * @endcode
 *
 * @note When disabled, all parsing classes and functions are not available.
 */
#ifndef MYXML_DISABLE_READER
#endif

/**
 * @def MYXML_DISABLE_WRITER
 * @brief Exclude Writing/Serialization methods.
 * Define as 1 to disable writer if serialization is not required.
 *
 * @warning This will disable these function at compile-time.
 *
 * @note This will reduce the binary size by about 30%.
 */
#ifndef MYXML_DISABLE_WRITER
#endif

// Uncomment this to disable STL
// #define MYXML_NO_STL

// Uncomment this to disable exceptions
// #define MYXML_NO_EXCEPTIONS

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Function Macros
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [SECTION] Platform Defines
//-----------------------------------------------------------------------------

/**
 * @defgroup platform Platform Definitions
 * @{
 */

/**
 * @brief   Checks if the compiler is of given brand.
 * @param   name Platform, like `APPLE`.
 * @retval  true   It is.
 * @retval  false  It isn't.
 */
#define MYXML_PLATFORM_IS(name) MYXML_PLATFORM_IS_##name

/**
 * @brief  Returns the current platform name.
 * @return  platform name.
 */
#ifdef __APPLE__
	/**
	* A preprocessor macro that is only defined if compiling for MacOS.
	*/
	#define MYXML_PLATFORM_IS_APPLE 1
	/**
	 * @brief  Returns the current platform name.
	 * @return  platform name.
	 */
  #define MYXML_PLATFORM_NAME_IS "Apple"
#elif defined(linux) || defined(__linux) || defined(__linux__)
	/**
	* A preprocessor macro that is only defined if compiling for Linux.
	*/
	#define MYXML_PLATFORM_IS_LINUX 1
  	/**
   	* @brief  Returns the current platform name.
   	* @return  platform name.
   	*/
  	#define MYXML_PLATFORM_NAME_IS "Linux"
#elif defined(WIN32) || defined(__WIN32__) || defined(_WIN32) || defined(_MSC_VER) || defined(__MINGW32__)
  	/**
   	* A preprocessor macro that is only defined if compiling for Windows.
   	*/
  	#define MYXML_PLATFORM_IS_WINDOWS 1
  	/**
   	* @brief  Returns the current platform name.
   	* @return  platform name.
   	*/
  	#define MYXML_PLATFORM_NAME_IS "Windows"
#else
  	/**
   	* A preprocessor macro that is only defined if compiling for others.
   	*/
  	#define MYXML_PLATFORM_IS_OTHERS 1
  	/**
   	* @brief  Returns the current platform name.
   	* @return  platform name.
   	*/
  	#define MYXML_PLATFORM_NAME_IS "Others"
#endif

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Standard Defines
//-----------------------------------------------------------------------------

/**
 * @defgroup language Standard Checks
 * @{
 */

/** C version (STDC) */
#if defined(__STDC__) && (__STDC__ >= 1) && defined(__STDC_VERSION__)
	#define MYXML_STDC __STDC_VERSION__
#else
	#define MYXML_STDC 0
#endif

// With the MSVC compilers, the value of __cplusplus is by default always "199611L"(C++98).
// To avoid that, the library instead references _MSVC_LANG which is always set a correct value.
// See https://devblogs.microsoft.com/cppblog/msvc-now-correctly-reports-__cplusplus/ for more details.
#if defined(_MSVC_LANG) && !defined(__clang__)
    #define MYXML_CPLUSPLUS _MSVC_LANG
#else
    #define MYXML_CPLUSPLUS __cplusplus
#endif

// C++ language standard detection

#if !defined(MYXML_HAS_CXX_26) && !defined(MYXML_HAS_CXX_23) && !defined(MYXML_HAS_CXX_20) && !defined(MYXML_HAS_CXX_17) && !defined(MYXML_HAS_CXX_14) && !defined(MYXML_HAS_CXX_11)
    #if (defined(MYXML_CPLUSPLUS) && MYXML_CPLUSPLUS > 202302L)
        #define MYXML_HAS_CXX_26
        #define MYXML_HAS_CXX_23
        #define MYXML_HAS_CXX_20
        #define MYXML_HAS_CXX_17
        #define MYXML_HAS_CXX_14
    #elif (defined(MYXML_CPLUSPLUS) && MYXML_CPLUSPLUS > 202002L)
        #define MYXML_HAS_CXX_23
        #define MYXML_HAS_CXX_20
        #define MYXML_HAS_CXX_17
        #define MYXML_HAS_CXX_14
    #elif (defined(MYXML_CPLUSPLUS) && MYXML_CPLUSPLUS > 201703L)
        #define MYXML_HAS_CXX_20
        #define MYXML_HAS_CXX_17
        #define MYXML_HAS_CXX_14
    #elif (defined(MYXML_CPLUSPLUS) && MYXML_CPLUSPLUS > 201402L)
        #define MYXML_HAS_CXX_17
        #define MYXML_HAS_CXX_14
    #elif (defined(MYXML_CPLUSPLUS) && MYXML_CPLUSPLUS > 201103L)
        #define MYXML_HAS_CXX_14
    #endif
    // Always specified because it is the minimal required version
    #define MYXML_HAS_CXX_11
#endif

/** @} */


//-----------------------------------------------------------------------------
// [SECTION] Compiler Defines
//-----------------------------------------------------------------------------

/**
 * @defgroup compiler Compiler Definitions
 * @{
 */

/**
 * @brief   Checks if the compiler is of given brand.
 * @param   name  Compiler brand, like `MSVC`.
 * @retval  true   It is.
 * @retval  false  It isn't.
 */
#define MYXML_COMPILER_IS(name) MYXML_COMPILER_IS_##name

/// Compiler is apple
#if !defined(__clang__)
    #define MYXML_COMPILER_IS_APPLE 0
#elif !defined(__apple_build_version__)
    #define MYXML_COMPILER_IS_APPLE 0
#else
    #define MYXML_COMPILER_IS_APPLE 1
    #define MYXML_COMPILER_VERSION_MAJOR __clang_major__
    #define MYXML_COMPILER_VERSION_MINOR __clang_minor__
    #define MYXML_COMPILER_VERSION_PATCH __clang_patchlevel__
#endif

/// Compiler is clang
#if !defined(__clang__)
    #define MYXML_COMPILER_IS_CLANG 0
#elif MYXML_COMPILER_IS(APPLE)
    #define MYXML_COMPILER_IS_CLANG 0
#else
    #define MYXML_COMPILER_IS_CLANG 1
    #define MYXML_COMPILER_VERSION_MAJOR __clang_major__
    #define MYXML_COMPILER_VERSION_MINOR __clang_minor__
    #define MYXML_COMPILER_VERSION_PATCH __clang_patchlevel__
#endif

/// Compiler is intel
#if !defined(__INTEL_COMPILER)
    #define MYXML_COMPILER_IS_INTEL 0
#elif !defined(__INTEL_COMPILER_UPDATE)
    #define MYXML_COMPILER_IS_INTEL 1
    /* __INTEL_COMPILER = XXYZ */
    #define MYXML_COMPILER_VERSION_MAJOR (__INTEL_COMPILER / 100)
    #define MYXML_COMPILER_VERSION_MINOR (__INTEL_COMPILER % 100 / 10)
    #define MYXML_COMPILER_VERSION_PATCH (__INTEL_COMPILER % 10)
#else
    #define MYXML_COMPILER_IS_INTEL 1
    /* __INTEL_COMPILER = XXYZ */
    #define MYXML_COMPILER_VERSION_MAJOR (__INTEL_COMPILER / 100)
    #define MYXML_COMPILER_VERSION_MINOR (__INTEL_COMPILER % 100 / 10)
    #define MYXML_COMPILER_VERSION_PATCH __INTEL_COMPILER_UPDATE
#endif

/// Compiler is msc
#if !defined(_MSC_VER)
    #define MYXML_COMPILER_IS_MSVC 0
#elif MYXML_COMPILER_IS(CLANG)
    #define MYXML_COMPILER_IS_MSVC 0
#elif MYXML_COMPILER_IS(INTEL)
    #define MYXML_COMPILER_IS_MSVC 0
#elif _MSC_VER >= 1400
    #define MYXML_COMPILER_IS_MSVC 1
    /* _MSC_FULL_VER = XXYYZZZZZ */
    #define MYXML_COMPILER_VERSION_MAJOR (_MSC_FULL_VER / 10000000)
    #define MYXML_COMPILER_VERSION_MINOR (_MSC_FULL_VER % 10000000 / 100000)
    #define MYXML_COMPILER_VERSION_PATCH (_MSC_FULL_VER % 100000)
#elif defined(_MSC_FULL_VER)
    #define MYXML_COMPILER_IS_MSVC 1
    /* _MSC_FULL_VER = XXYYZZZZ */
    #define MYXML_COMPILER_VERSION_MAJOR (_MSC_FULL_VER / 1000000)
    #define MYXML_COMPILER_VERSION_MINOR (_MSC_FULL_VER % 1000000 / 10000)
    #define MYXML_COMPILER_VERSION_PATCH (_MSC_FULL_VER % 10000)
#else
    #define MYXML_COMPILER_IS_MSVC 1
    /* _MSC_VER = XXYY */
    #define MYXML_COMPILER_VERSION_MAJOR (_MSC_VER / 100)
    #define MYXML_COMPILER_VERSION_MINOR (_MSC_VER % 100)
    #define MYXML_COMPILER_VERSION_PATCH 0
#endif

/// Compiler is gcc
#if !defined(__GNUC__)
    #define MYXML_COMPILER_IS_GCC 0
#elif MYXML_COMPILER_IS(APPLE)
    #define MYXML_COMPILER_IS_GCC 0
#elif MYXML_COMPILER_IS(CLANG)
    #define MYXML_COMPILER_IS_GCC 0
#elif MYXML_COMPILER_IS(INTEL)
    #define MYXML_COMPILER_IS_GCC 0
#else
    #define MYXML_COMPILER_IS_GCC 1
    #define MYXML_COMPILER_VERSION_MAJOR __GNUC__
    #define MYXML_COMPILER_VERSION_MINOR __GNUC_MINOR__
    #define MYXML_COMPILER_VERSION_PATCH __GNUC_PATCHLEVEL__
#endif

/**
 * @brief   Checks if the compiler is of given brand and is newer than or equal
 *          to the passed version.
 * @param   name     Compiler brand, like `MSVC`.
 * @param   x      Major version.
 * @param   y      Minor version.
 * @param   z      Patchlevel.
 * @retval  true   name >= x.y.z.
 * @retval  false  otherwise.
 */
#define MYXML_COMPILER_SINCE(name, x, y, z)                                 \
  (MYXML_COMPILER_IS(name) && ((MYXML_COMPILER_VERSION_MAJOR > (x)) ||     \
                                ((MYXML_COMPILER_VERSION_MAJOR == (x)) &&   \
                                 ((MYXML_COMPILER_VERSION_MINOR > (y)) ||   \
                                  ((MYXML_COMPILER_VERSION_MINOR == (y)) && \
                                   (MYXML_COMPILER_VERSION_PATCH >= (z)))))))

/**
 * @brief   Checks if  the compiler  is of  given brand and  is older  than the
 *          passed version.
 * @param   name     Compiler brand, like `MSVC`.
 * @param   x      Major version.
 * @param   y      Minor version.
 * @param   z      Patchlevel.
 * @retval  true   name < x.y.z.
 * @retval  false  otherwise.
 */
#define MYXML_COMPILER_BEFORE(name, x, y, z)                                \
  (MYXML_COMPILER_IS(name) && ((MYXML_COMPILER_VERSION_MAJOR < (x)) ||     \
                                ((MYXML_COMPILER_VERSION_MAJOR == (x)) &&   \
                                 ((MYXML_COMPILER_VERSION_MINOR < (y)) ||   \
                                  ((MYXML_COMPILER_VERSION_MINOR == (y)) && \
                                   (MYXML_COMPILER_VERSION_PATCH < (z)))))))


// exclude unsupported compilers
#ifndef MYXML_SKIP_COMPILER_CHECK
    #if MYXML_COMPILER_IS_CLANG
        #if (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__) < 30400
            #error "Unsupported Clang Compiler version."
        #endif
    #elif MYXML_COMPILER_IS_GCC
        #if (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) < 40800
            #error "Unsupported GCC Compiler version."
        #endif
    #endif
#endif

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Compiler Warnings
//-----------------------------------------------------------------------------

/**
 * @defgroup compiler Compiler Warnings
 * @{
 */

#if MYXML_COMPILER_IS(CLANG)
    #define MYXML_PRAGMA_TO_STR(x) _Pragma(#x)
    #define MYXML_CLANG_SUPPRESS_WARNING_PUSH _Pragma("clang diagnostic push")
    #define MYXML_CLANG_SUPPRESS_WARNING(w) \
    MYXML_PRAGMA_TO_STR(clang diagnostic ignored w)
    #define MYXML_CLANG_SUPPRESS_WARNING_POP _Pragma("clang diagnostic pop")
    #define MYXML_CLANG_SUPPRESS_WARNING_WITH_PUSH(w) \
    MYXML_CLANG_SUPPRESS_WARNING_PUSH MYXML_CLANG_SUPPRESS_WARNING(w)
#else // MYXML_CLANG
    #define MYXML_CLANG_SUPPRESS_WARNING_PUSH
    #define MYXML_CLANG_SUPPRESS_WARNING(w)
    #define MYXML_CLANG_SUPPRESS_WARNING_POP
    #define MYXML_CLANG_SUPPRESS_WARNING_WITH_PUSH(w)
#endif // MYXML_CLANG

#if MYXML_COMPILER_IS(GCC)
    #define MYXML_PRAGMA_TO_STR(x) _Pragma(#x)
    #define MYXML_GCC_SUPPRESS_WARNING_PUSH _Pragma("GCC diagnostic push")
    #define MYXML_GCC_SUPPRESS_WARNING(w) \
    MYXML_PRAGMA_TO_STR(GCC diagnostic ignored w)
    #define MYXML_GCC_SUPPRESS_WARNING_POP _Pragma("GCC diagnostic pop")
    #define MYXML_GCC_SUPPRESS_WARNING_WITH_PUSH(w) \
    MYXML_GCC_SUPPRESS_WARNING_PUSH MYXML_GCC_SUPPRESS_WARNING(w)
#else // MYXML_GCC
    #define MYXML_GCC_SUPPRESS_WARNING_PUSH
    #define MYXML_GCC_SUPPRESS_WARNING(w)
    #define MYXML_GCC_SUPPRESS_WARNING_POP
    #define MYXML_GCC_SUPPRESS_WARNING_WITH_PUSH(w)
#endif // MYXML_GCC

#if MYXML_COMPILER_IS(MSVC)
    #define MYXML_MSVC_SUPPRESS_WARNING_PUSH __pragma(warning(push))
    #define MYXML_MSVC_SUPPRESS_WARNING(w) __pragma(warning(disable : w))
    #define MYXML_MSVC_SUPPRESS_WARNING_POP __pragma(warning(pop))
    #define MYXML_MSVC_SUPPRESS_WARNING_WITH_PUSH(w) \
    MYXML_MSVC_SUPPRESS_WARNING_PUSH MYXML_MSVC_SUPPRESS_WARNING(w)
#else // MYXML_MSVC
    #define MYXML_MSVC_SUPPRESS_WARNING_PUSH
    #define MYXML_MSVC_SUPPRESS_WARNING(w)
    #define MYXML_MSVC_SUPPRESS_WARNING_POP
    #define MYXML_MSVC_SUPPRESS_WARNING_WITH_PUSH(w)
#endif // MYXML_MSVC

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Compiler Attributes
//-----------------------------------------------------------------------------

/**
 * @defgroup compiler Compiler Attributes
 * @{
 */

 /** compiler builtin check */
#ifndef MYXML_HAS_BUILTIN
	#ifdef __has_builtin
    	#define MYXML_HAS_BUILTIN(x) __has_builtin(x)
  	#else
    	#define MYXML_HAS_BUILTIN(x) 0
  	#endif
#endif

/** compiler attribute check */
#ifndef MYXML_HAS_ATTRIBUTE
  	#ifdef __has_attribute
    	#define MYXML_HAS_ATTRIBUTE(x) __has_attribute(x)
  	#else
    	#define MYXML_HAS_ATTRIBUTE(x) 0
  	#endif
#endif

/** compiler feature check */
#ifndef MYXML_HAS_FEATURE
  	#ifdef __has_feature
    	#define MYXML_HAS_FEATURE(x) __has_feature(x)
  	#else
    	#define MYXML_HAS_FEATURE(x) 0
  	#endif
#endif

/** compiler include check */
#ifndef MYXML_HAS_INCLUDE
  	#ifdef __has_include
    	#define MYXML_HAS_INCLUDE(x) __has_include(x)
  	#else
    	#define MYXML_HAS_INCLUDE(x) 0
  	#endif
#endif

/** compiler cpp attribute check */
#ifndef MYXML_HAS_CPP_ATTRIBUTE
  	#ifdef __has_cpp_attribute
        #define MYXML_HAS_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
  	#else
    	#define MYXML_HAS_CPP_ATTRIBUTE(x) 0
  	#endif
#endif


 /** inline for compiler */
#ifndef MYXML_INLINE
  	#if MYXML_COMPILER_SINCE(MSVC, 12, 0, 0)
    	#define MYXML_INLINE __forceinline
  	#elif MYXML_COMPILER_IS(INTEL)
    	#define MYXML_INLINE __inline
  	#elif MYXML_HAS_ATTRIBUTE(always_inline) || MYXML_COMPILER_SINCE(GCC, 4, 0, 0)
    	#define MYXML_INLINE __inline__ __attribute__((always_inline))
  	#elif MYXML_COMPILER_IS(CLANG) || MYXML_COMPILER_IS(GCC)
    	#define MYXML_INLINE __inline__
  	#elif defined(__cplusplus) || MYXML_STDC >= 199901L
    	#define MYXML_INLINE inline
  	#else
    	#define MYXML_INLINE
  	#endif
#endif

/** noinline for compiler */
#ifndef MYXML_NOINLINE
  	#if MYXML_COMPILER_SINCE(MSVC, 14, 0, 0)
    	#define MYXML_NOINLINE __declspec(noinline)
  	#elif MYXML_HAS_ATTRIBUTE(noinline) || (MYXML_COMPILER_SINCE(GCC, 4, 0, 0))
    	#define MYXML_NOINLINE __attribute__((noinline))
  	#else
    	#define MYXML_NOINLINE
  	#endif
#endif

/** align for compiler */
#ifndef MYXML_ALIGN
  	#if MYXML_COMPILER_SINCE(MSVC, 13, 0, 0)
    	#define MYXML_ALIGN(x) __declspec(align(x))
  	#elif MYXML_HAS_ATTRIBUTE(aligned) || defined(__GNUC__)
    	#define MYXML_ALIGN(x) __attribute__((aligned(x)))
  	#elif MYXML_CPP_VERSION >= 201103L
    	#define MYXML_ALIGN(x) alignas(x)
  	#else
    	#define MYXML_ALIGN(x)
  	#endif
#endif

/** deprecate warning */
#if defined(MYXML_HAS_CXX_14)
    #define MYXML_DEPRECATED(msg) [[deprecated(msg)]]
#else
  	#if MYXML_COMPILER_SINCE(MSVC, 14, 0, 0)
    	#define MYXML_DEPRECATED(msg) __declspec(deprecated(msg))
  	#elif MYXML_HAS_FEATURE(attribute_deprecated_with_message) || \
    (MYXML_COMPILER_SINCE(GCC, 4, 0, 0) ||                    \
     (MYXML_COMPILER_VERSION_MAJOR == 5 &&                    \
      MYXML_COMPILER_VERSION_MINOR >= 5))
    	#define MYXML_DEPRECATED(msg) __attribute__((deprecated(msg)))
  	#elif MYXML_COMPILER_SINCE(MSVC, 3, 0, 0)
    	#define MYXML_DEPRECATED(msg) __attribute__((deprecated))
  	#else
    	#define MYXML_DEPRECATED(msg)
  	#endif
#endif

// switch usage of constexpr keyword depending on active C++ standard.
#if defined(MYXML_HAS_CXX_17)
    #define MYXML_CONSTEXPR constexpr
#else
    #define MYXML_CONSTEXPR
#endif

// switch usage of [[likely]] C++ attribute which has been available since C++20.
#if defined(MYXML_HAS_CXX_20) && MYXML_HAS_CPP_ATTRIBUTE(likely) >= 201803L
    #define MYXML_LIKELY(expr) (!!(expr)) [[likely]]
#elif MYXML_HAS_BUILTIN(__builtin_expect)
    #define MYXML_LIKELY(expr) (__builtin_expect(!!(expr), 1))
#else
    #define MYXML_LIKELY(expr) (!!(expr))
#endif

// switch usage of [[unlikely]] C++ attribute which has been available since C++20.
#if defined(MYXML_HAS_CXX_20) && MYXML_HAS_CPP_ATTRIBUTE(unlikely) >= 201803L
    #define MYXML_UNLIKELY(expr) (!!(expr)) [[unlikely]]
#elif MYXML_HAS_BUILTIN(__builtin_expect)
    #define MYXML_UNLIKELY(expr) (__builtin_expect(!!(expr), 0))
#else
    #define MYXML_UNLIKELY(expr) (!!(expr))
#endif

// switch usage of char8_t which has been available since C++20.
#if defined(MYXML_HAS_CXX_20) && defined(__cpp_char8_t) && __cpp_char8_t >= 201811L
    #define MYXML_HAS_CHAR8_T (1)
#else
    #define MYXML_HAS_CHAR8_T (0)
#endif

/** @} */


//-----------------------------------------------------------------------------
// [SECTION] API Import/Export
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

#if (defined(__cpp_exceptions) || defined(__EXCEPTIONS) || defined(_CPPUNWIND)) && !defined(MYXML_NOEXCEPTION)
    #define MYXML_THROW(exception) throw exception
    #define MYXML_TRY try
    #define MYXML_CATCH(exception) catch(exception)
#else
    #include <cstdlib>
    #define MYXML_THROW(exception) std::abort()
    #define MYXML_TRY if(true)
    #define MYXML_CATCH(exception) if(false)
#endif

#ifndef MYXML_ASSERT
    #include <cassert> // assert
    #define MYXML_ASSERT(x) assert(x)
#else
    #define MYXML_ASSERT(x)
#endif

#if MYXML_COMPILER_SINCE(GCC, 6, 0, 0)
    #define MYXML_QUOTE_OPERATOR operator""_xml
#else
    #define MYXML_QUOTE_OPERATOR operator"" _xml
#endif

// clang-format on

#pragma region Forward
namespace myxml
{
    /**
     * @namespace detail
     * @brief The Details namespace myxml::detail::
     */
    namespace detail
    {
        //-----------------------------------------------------------------------------
        // [SECTION] Details Forward Declarations
        //-----------------------------------------------------------------------------

        /** Enumerations */

        enum class token_t;
        enum class error_t;
        enum class event_t;
        enum class value_t;
        enum class break_t; /** Line break types. */

        /** Structures */

        struct mark; /** The pointer position. */
        struct event;
        struct token;

        // input
        class lexer;
        class parser;
        class iadapter;
        class deserializer;
        class file_iadapter;
        class stream_iadapter;
        class memory_iadapter;
        class iterator_iadapter;

        // output
        class emitter;
        class oadapter;
        class serializer;
        class file_iadapter;
        class stream_oadapter;
        class memory_oadapter;
        class iterator_oadapter;

    } // namespace detail

} // namespace myxml

/**
 * @namespace myxml
 * @brief The Api namespace myxml::
 */
namespace myxml
{
    //-----------------------------------------------------------------------------
    // [SECTION] Myxml Forward Declarations
    //-----------------------------------------------------------------------------

    /** Enumerations */

    enum class encoding; /** The stream encoding. */
    enum class node_t;

    /** Structures */

    class xml;
    class version;
    class formatter;
    class exception;

} // namespace myxml

namespace myxml
{
    /**
     * @namespace literals
     * @brief The Literals namespace myxml::literals::
     */
    namespace literals
    {
        //-----------------------------------------------------------------------------
        // [SECTION] Literal Forward Declarations
        //-----------------------------------------------------------------------------

    } // namespace literals

} // namespace myxml

#pragma endregion // Forward

#pragma region Detail

/**
 * @namespace myxml
 * @brief The API namespace myxml::
 */
namespace myxml
{

    /**
     * @namespace detail
     * @brief The Details namespace myxml::detail::
     */
    namespace detail
    {
        //-----------------------------------------------------------------------------
        // [SECTION] Flags & Enumerations
        //-----------------------------------------------------------------------------

        /**
         * @defgroup enum Flags & Enumerations
         * @brief Detail enum types and flags.
         * @{
         */

        enum class token_t
        {
            unknown,
        };

        enum class error_t
        {
            unknown,
            lexer,
            parser,
            reader,
            writer,
            emitter,
            encoding,
            decoding,
        };

        enum class event_t
        {
            unknown,
        };

        enum class value_t
        {
            unknown,
        };

        enum class break_t
        {
            any, /** Let the parser choose the break type. */
            cr,  /** Use CR for line breaks (Mac style). */
            ln,  /** Use LN for line breaks (Unix style). */
            crln /** Use CR LN for line breaks (DOS style). */

        };

        /** @} group enum */

        //-----------------------------------------------------------------------------
        // [SECTION] Data Structures
        //-----------------------------------------------------------------------------

        /**
         * @defgroup structs Data Structures
         * @brief Detail types and data structures.
         * @{
         */

        struct mark
        {
            size_t column{0}; /** The position column. */
            size_t index{0};  /** The position index. */
            size_t line{0};   /** The position line. */
        };

        struct event
        {
            event_t type{event_t::unknown}; /** The event type. */
            mark start{};                   /** The beginning of the token. */
            mark end{};                     /** The end of the token. */
        };

        struct token
        {
            token_t type{token_t::unknown}; /** The token type. */
            union
            {
                char *value;

            } value;
            mark start{}; /** The beginning of the token. */
            mark end{};   /** The end of the token. */
        };

        /** @} group structs */

        /**
         * @defgroup input
         * @brief
         * @{
         */

        /**
         * @brief Abstract base for input adapters used by the parser.
         *
         * Implementers must advance the internal reading position by the number of
         * bytes actually copied into the caller buffer. All methods return
         * std::nullopt on error to allow callers to detect failures uniformly.
         */
        class iadapter
        {
        public:
            /**
             * @brief Return the encoding type of the input adapter.
             *
             * @return The encoding type.
             */
            virtual myxml::encoding encoding() = 0;

            /**
             * @brief Read up to @p size bytes into @p data.
             *
             * Implementations must copy at most @p size bytes into the provided
             * buffer and advance the stream position accordingly.
             *
             * @param[out] data Buffer to receive the bytes. Must be at least @p size bytes.
             * @param[in] size Number of bytes requested.
             * @return The number of bytes actually read, or `0` if an error occurred.
             */
            virtual std::size_t read(void *data, std::size_t size) = 0;

            /**
             * @brief Virtual destructor.
             */
            virtual ~iadapter() = default;
        };

        class file_iadapter : public iadapter
        {
        public:
            /**
             * @brief Construct the stream from a FILE pointer
             *
             * @param file file to open
             *
             * @throws myxml::exception on error
             */
            file_iadapter(std::FILE *file);

            file_iadapter(std::FILE *file, myxml::encoding encoding);

            /**
             * @brief Deleted copy constructor
             */
            file_iadapter(const file_iadapter &) = delete;

            /**
             * @brief Default move constructor
             */
            file_iadapter(file_iadapter &&) noexcept = default;

            /**
             * @brief Return the encoding type.
             *
             * @return The encoding type.
             */
            myxml::encoding encoding() override;

            /**
             * @brief Read up to @p size bytes into @p data.
             *
             * @param[out] data Buffer to receive the bytes.
             * @param[in] size Number of bytes requested.
             * @return The number of bytes actually read, or `0` if an error occurred.
             */
            std::size_t read(void *data, std::size_t size) override;

            /**
             * @brief Deleted copy assignment operator
             */
            file_iadapter &operator=(const file_iadapter &) = delete;

            /**
             * @brief Delete move assignment operator
             */
            file_iadapter &operator=(file_iadapter &&) = delete;

        private:
            /** Member data */

            myxml::encoding m_encoding;
            std::FILE *m_file;
        };

        class stream_iadapter : public iadapter
        {
        public:
            stream_iadapter(std::istream &stream);

            stream_iadapter(std::istream &stream, myxml::encoding encoding);

            /**
             * @brief Deleted copy constructor
             */
            stream_iadapter(const stream_iadapter &) = delete;

            /**
             * @brief Default move constructor
             */
            stream_iadapter(stream_iadapter &&) noexcept = default;

            /**
             * @brief Return the encoding type.
             *
             * @return The encoding type.
             */
            myxml::encoding encoding() override;

            /**
             * @brief Read up to @p size bytes into @p data.
             *
             * @param[out] data Buffer to receive the bytes.
             * @param[in] size Number of bytes requested.
             * @return The number of bytes actually read, or `0` if an error occurred.
             */
            std::size_t read(void *data, std::size_t size) override;

            /**
             * @brief Deleted copy assignment operator
             */
            stream_iadapter &operator=(const stream_iadapter &) = delete;

            /**
             * @brief Delete move assignment operator
             */
            stream_iadapter &operator=(stream_iadapter &&) = delete;

        private:
            /** Member data */

            myxml::encoding m_encoding;
            std::istream *m_stream;
        };

        class memory_iadapter : public iadapter
        {
        public:
            /**
             * @brief Construct the stream from its data
             *
             * @param data Pointer to the data in memory
             * @param size Size of the data, in bytes
             */
            memory_iadapter(void *data, std::size_t size);

            memory_iadapter(void *data, std::size_t size, myxml::encoding encoding);

            /**
             * @brief Deleted copy constructor
             */
            memory_iadapter(const memory_iadapter &) = delete;

            /**
             * @brief Default move constructor
             */
            memory_iadapter(memory_iadapter &&) noexcept = default;

            /**
             * @brief Return the encoding type.
             *
             * @return The encoding type.
             */
            myxml::encoding encoding() override;

            /**
             * @brief Read up to @p size bytes into @p data.
             *
             * @param[out] data Buffer to receive the bytes.
             * @param[in] size Number of bytes requested.
             * @return The number of bytes actually read, or `0` if an error occurred.
             */
            std::size_t read(void *data, std::size_t size) override;

            /**
             * @brief Deleted copy assignment operator
             */
            memory_iadapter &operator=(const memory_iadapter &) = delete;

            /**
             * @brief Delete move assignment operator
             */
            memory_iadapter &operator=(memory_iadapter &&) = delete;

        private:
            /** Member data */

            myxml::encoding m_encoding;
            std::size_t m_pos;
            std::size_t m_size;
            void *m_data;
        };

        class lexer
        {
        public:
            lexer(iadapter &adapter);

            /**
             * @brief Deleted copy constructor
             */
            lexer(const lexer &) = delete;

            /**
             * @brief Default move constructor
             */
            lexer(lexer &&) noexcept = default;

            /**
             * @brief Deleted copy assignment operator
             */
            lexer &operator=(const lexer &) = delete;

            /**
             * @brief Deleted move assignment operator
             */
            lexer &operator=(lexer &&) = delete;

            /**
             * @brief Advance the lexer and return the next token type.
             *
             * This method reads input as necessary and updates the lexer's
             * internal token state. Callers can inspect the token with
             * get_token() or check get_type().
             *
             * @return The token produced.
             */
            token next_token();

            /**
             * @brief Return the current token.
             *
             * @return The current token.
             */
            token get_token();

            /**
             * @brief Return the current token type.
             *
             * @return The current token type.
             */
            token_t get_type();

        private:
            int get_char();
            void unget_char();
            void add_char(int c);

        private:
            iadapter &m_adapter;
            mark m_position;

            token m_token;
            int current;

            // values
            std::string m_string;
            float m_float;
            int m_int;
        };

        /** @} group input */

        /**
         * @defgroup output
         * @brief
         * @{
         */

        /**
         * @brief Abstract base for output adapters used by the emitter.
         *
         * All write methods accept a pointer to immutable data (const void*) because
         * writing should never mutate the caller'string source buffer.
         */
        class oadapter
        {
        public:
            /**
             * @brief Return the encoding type of the output adapter.
             *
             * @return The encoding type.
             */
            virtual myxml::encoding encoding() = 0;

            /**
             * @brief Write up to @p size bytes from @p data into the stream.
             *
             * Implementations must copy at most @p size bytes from the provided buffer
             * and advance the stream position accordingly.
             *
             * @param data Pointer to the bytes to write.
             * @param size Number of bytes to write.
             * @return The number of bytes actually written, or `0` on error.
             */
            virtual std::size_t write(const void *data, std::size_t size) = 0;

            /**
             * @brief Virtual destructor.
             */
            virtual ~oadapter() = default;
        };

        class file_oadapter : public oadapter
        {
        public:
            /**
             * @brief Construct the stream from a FILE pointer
             *
             * @param file file to open
             *
             * @throws myxml::exception on error
             */
            file_oadapter(std::FILE *file);

            file_oadapter(std::FILE *file, myxml::encoding encoding);

            /**
             * @brief Deleted copy constructor
             */
            file_oadapter(const file_oadapter &) = delete;

            /**
             * @brief Default move constructor
             */
            file_oadapter(file_oadapter &&) noexcept = default;

            /**
             * @brief Return the encoding type.
             *
             * @return The encoding type.
             */
            myxml::encoding encoding() override;

            /**
             * @brief Write up to @p size bytes from @p data into the stream.
             *
             * @param data Pointer to the bytes to write.
             * @param size Number of bytes to write.
             * @return The number of bytes actually written, or `0` on error.
             */
            std::size_t write(const void *data, std::size_t size) override;

            /**
             * @brief Deleted copy assignment operator
             */
            file_oadapter &operator=(const file_oadapter &) = delete;

            /**
             * @brief Delete move assignment operator
             */
            file_oadapter &operator=(file_oadapter &&) = delete;

        private:
            /** Member data */

            myxml::encoding m_encoding;
            std::FILE *m_file;
        };

        class stream_oadapter : public oadapter
        {
        public:
            stream_oadapter(std::ostream &stream);

            stream_oadapter(std::ostream &stream, myxml::encoding encoding);

            /**
             * @brief Deleted copy constructor
             */
            stream_oadapter(const stream_oadapter &) = delete;

            /**
             * @brief Default move constructor
             */
            stream_oadapter(stream_oadapter &&) noexcept = default;

            /**
             * @brief Return the encoding type.
             *
             * @return The encoding type.
             */
            myxml::encoding encoding() override;

            /**
             * @brief Write up to @p size bytes from @p data into the stream.
             *
             * @param data Pointer to the bytes to write.
             * @param size Number of bytes to write.
             * @return The number of bytes actually written, or `0` on error.
             */
            std::size_t write(const void *data, std::size_t size) override;

            /**
             * @brief Deleted copy assignment operator
             */
            stream_oadapter &operator=(const stream_oadapter &) = delete;

            /**
             * @brief Delete move assignment operator
             */
            stream_oadapter &operator=(stream_oadapter &&) = delete;

        private:
            /** Member data */

            myxml::encoding m_encoding;
            std::ostream *m_stream;
        };

        class memory_oadapter : public oadapter
        {
        public:
            /**
             * @brief Construct the stream from its data
             *
             * @param data        Pointer to the data in memory
             * @param size Size of the data, in bytes
             */
            memory_oadapter(void *data, std::size_t size);

            memory_oadapter(void *data, std::size_t size, myxml::encoding encoding);

            /**
             * @brief Deleted copy constructor
             */
            memory_oadapter(const memory_oadapter &) = delete;

            /**
             * @brief Default move constructor
             */
            memory_oadapter(memory_oadapter &&) noexcept = default;

            /**
             * @brief Return the encoding type.
             *
             * @return The encoding type.
             */
            myxml::encoding encoding() override;

            /**
             * @brief Write up to @p size bytes from @p data into the stream.
             *
             * @param data Pointer to the bytes to write.
             * @param size Number of bytes to write.
             * @return The number of bytes actually written, or `0` on error.
             */
            std::size_t write(const void *data, std::size_t size) override;

            /**
             * @brief Deleted copy assignment operator
             */
            memory_oadapter &operator=(const memory_oadapter &) = delete;

            /**
             * @brief Delete move assignment operator
             */
            memory_oadapter &operator=(memory_oadapter &&) = delete;

        private:
            /** Member data */

            myxml::encoding m_encoding;
            std::size_t m_pos;
            std::size_t m_size;
            void *m_data;
        };

        /** @} group output */

        //-----------------------------------------------------------------------------
        // [SECTION] Function Declarations
        //-----------------------------------------------------------------------------

    }; // namespace detail

} // namespace myxml

#pragma endregion // Detail

#pragma region Myxml

/**
 * @namespace myxml
 * @brief The API namespace myxml::
 */
namespace myxml
{
    //-----------------------------------------------------------------------------
    // [SECTION] Flags & Enumerations
    //-----------------------------------------------------------------------------

    /**
     * @defgroup enum Flags & Enumerations
     * @brief Core enum types and flags.
     * @{
     */

    enum class encoding
    {
        Unspecified, /** Let the parser choose the encoding. */
        utf8,        /** The UTF-8 encoding. */
        utf16,       /** The UTF-16-LE encoding with native endianness. */
        utf16le,     /** The UTF-16-LE encoding with BOM. */
        utf16be,     /** The UTF-16-BE encoding with BOM. */
        utf32,       /** The UTF-32 encoding with native endianness. */
        utf32le,     /** The UTF-32-LE encoding with BOM. */
        utf32be,     /** The UTF-32-BE encoding with BOM. */
    };

    enum class node_t
    {
        unknown,
    };

    /** @} */

    //-----------------------------------------------------------------------------
    // [SECTION] Data Structures
    //-----------------------------------------------------------------------------

    /**
     * @defgroup struct Data Structures
     * @brief Core types and data structures.
     * @{
     */

    /**
     * @class myxml::version
     * @brief version numbering scheme @c https://semver.org/
     * @note Its members can be accessed directly (there are no accessors like
     * `SetMajor()`, `GetMajor()`). Usage example:
     */
    class version
    {
    public:
        /**
         * @brief Default constructor
         *
         * @note Creates a `version(0, 0, 0)`.
         */
        version() = default;

        /**
         * @brief Construct the version.
         *
         * @param major The major version number.
         * @param minor The minor version number.
         * @param patch The patch version number.
         *
         */
        version(int major, int minor, int patch);

    public:
        /** Member data */
        int major{}; /** The major version number. */
        int minor{}; /** The minor version number. */
        int patch{}; /** The patch version number. */
    };

    bool operator<(const version &lhs, const version &rhs) noexcept;
    bool operator>(const version &lhs, const version &rhs) noexcept;
    bool operator==(const version &lhs, const version &rhs) noexcept;
    bool operator!=(const version &lhs, const version &rhs) noexcept;
    bool operator<=(const version &lhs, const version &rhs) noexcept;
    bool operator>=(const version &lhs, const version &rhs) noexcept;

    /**
     * @brief Write the version object string into stream.
     *
     * @param[in] ostream An output stream object.
     * @param[in] version A version object.
     *
     * @return Reference to the output stream object `ostream`.
     */
    std::ostream &operator<<(std::ostream &ostream, const version &version);

    /**
     * @class myxml::exception
     * @brief A base exception class used in library.
     */
    class exception : public std::exception
    {
    public:
        /**
         * @brief Construct a new exception object without any error messages.
         */
        exception() = default;

        /**
         * @brief Construct a new exception object with an error messages.
         * @param[in] message An error message.
         */
        exception(const char *message) noexcept;

        /**
         * @brief Returns an error message internally held. If nothing, a non-null,
         * empty string will be returned.
         * @return An error message internally held. The message might be empty.
         */
        const char *what() const noexcept override;

    private:
        std::string m_Message; /** An error message holder. */
    };

    /** @} */

    //-----------------------------------------------------------------------------
    // [SECTION] Function Declarations
    //-----------------------------------------------------------------------------

    /**
     * @brief A wrapper for the serialization feature.
     *
     * @param[in] stream An output stream object.
     * @param[in] node A xml object.
     *
     * @return Reference to the output stream object `stream`.
     */
    std::ostream &operator<<(std::ostream &stream, const xml &node);

    /**
     * @brief A wrapper for the deserialization feature.
     *
     * @param[in] stream An input stream object.
     * @param[in] node A xml object.
     *
     * @return Reference to the input stream object `stream`.
     */
    std::istream &operator>>(std::istream &stream, const xml &node);

} // namespace myxml

#pragma endregion // Myxml

#pragma region Literal

/**
 * @namespace myxml
 * @brief The API namespace myxml::
 */
namespace myxml
{

    /**
     * @namespace literals
     * @brief The literals namespace myxml::literals::
     */
    namespace literals
    {

        //-----------------------------------------------------------------------------
        // [SECTION] Function Declarations
        //-----------------------------------------------------------------------------

        // Whitespace before the literal operator is deprecated in C++23 or later but required in C++11.
        MYXML_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wdeprecated")

        /**
         * @brief Deserializes a `char` array into a `xml` object.
         *
         * @param s An input `char` array.
         * @param node The size of `s`.
         *
         * @return The resulting `xml` object deserialized from `s`.
         */
        inline xml MYXML_QUOTE_OPERATOR(const char *s, std::size_t node);

#if MYXML_HAS_CHAR8_T

        /**
         * @brief Deserializes a `char8_t` array into a `xml` object.
         *
         * @param s An input `char8_t` array.
         * @param node The size of `s`.
         *
         * @return The resulting `xml` object deserialized from `s`.
         */
        inline xml MYXML_QUOTE_OPERATOR(const char8_t *s, std::size_t node);

#endif // MYXML_HAS_CHAR8_T

        /**
         * @brief Deserializes a `char16_t` array into a `xml` object.
         *
         * @param s An input `char16_t` array.
         * @param node The size of `s`.
         *
         * @return The resulting `xml` object deserialized from `s`.
         */
        inline xml MYXML_QUOTE_OPERATOR(const char16_t *s, std::size_t node);

        /**
         * @brief Deserializes a `char32_t` array into a `xml` object.
         *
         * @param s An input `char32_t` array.
         * @param node The size of `s`.
         *
         * @return The resulting `xml` object deserialized from `s`.
         */
        inline xml MYXML_QUOTE_OPERATOR(const char32_t *s, std::size_t node);

        MYXML_CLANG_SUPPRESS_WARNING_POP

    } // namespace literals

}; // namespace myxml

#pragma endregion // Literal

//-----------------------------------------------------------------------------

// clang-format off

#if MYXML_COMPILER_IS_GCC
    #pragma GCC diagnostic pop
#endif // MYXML_COMPILER_IS_GCC

#if MYXML_COMPILER_IS_MSVC
    #pragma warning(pop)
#endif // MYXML_COMPILER_IS_MSVC

#if MYXML_COMPILER_IS_CLANG
    #pragma clang diagnostic pop
#endif // MYXML_COMPILER_IS_CLANG

// clang-format on

#endif // DJOEZEKE_MYXML_HPP

/**
 * HISTORY: version History
 */

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