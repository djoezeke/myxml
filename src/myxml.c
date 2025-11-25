/**
 * @file myxml.c
 * @brief XML parser library header for C/C++.
 * This is a  C/C++ Xml Parser Library Source @c myxml.h.
 * @details This header provides all public API, types, macros, and
 * configuration for XML and supports both C and C++ usage.
 * @author Sackey Ezekiel Etrue (djoezeke)
 * @date Thur 16 00:08:15 Oct GMT 2025
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
 *
 *  Internal:
 *
 *  [SECTION] Includes
 *  [SECTION] Macro Defines
 *  [SECTION] Data Structures
 *  [SECTION] C Only Functions
 *    - [SECTION] Declarations
 *    - [SECTION] Definations
 *  [SECTION] C++ Only Classes
 *    - [SECTION] Declarations
 *    - [SECTION] Definations
 *
 *  Myxml:
 *
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

//-------------------------------------------------------------------------
// [SECTION] INCLUDES
//-------------------------------------------------------------------------

#include <myxml/myxml.h>

#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>   //
#include <stdlib.h>  //
#include <string.h>  //

// clang-format off

#ifdef __cplusplus

    /** C++ Exclusive headers. */
    #include <algorithm>
    #include <cctype>
    #include <exception>
    #include <fstream>
    #include <iostream>
    #include <map>
    #include <sstream>
    #include <string>
    #include <type_traits>
    #include <vector>

#endif  //__cplusplus

#ifndef MYXML_SKIP_VERSION_CHECK
    #if defined(MYXML_VERSION_MAJOR) && defined(MYXML_VERSION_MINOR) && defined(MYXML_VERSION_PATCH)
        #if MYXML_VERSION_MAJOR != 0 || MYXML_VERSION_MINOR != 1 || MYXML_VERSION_PATCH != 0
            #warning "Included a different library header (myxml.h) version!"
        #endif
    #endif
#endif  // MYXML_SKIP_VERSION_CHECK

#if defined( NDEBUG ) || defined( MYXML_ENABLE_DEBUG )
    #warning "Cannot both define NDEBUG and MYXML_ENABLE_DEBUG"
#endif

//-----------------------------------------------------------------------------
// [SECTION] Myxml Info Check
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [SECTION] Platform
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
// [SECTION] Compiler
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

// Compiler Checks

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

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Warnings
//-----------------------------------------------------------------------------

/**
 * @defgroup compiler Compiler Warnings
 * @{
 */

#if MYXML_COMPILER_IS(CLANG)
	#define MYXML_PRAGMA_TO_STR(x) _Pragma(#x)
	#define MYXML_CLANG_SUPPRESS_WARNING_PUSH _Pragma("clang diagnostic push")
	#define MYXML_CLANG_SUPPRESS_WARNING(w) MYXML_PRAGMA_TO_STR(clang diagnostic ignored w)
	#define MYXML_CLANG_SUPPRESS_WARNING_POP _Pragma("clang diagnostic pop")
	#define MYXML_CLANG_SUPPRESS_WARNING_WITH_PUSH(w) MYXML_CLANG_SUPPRESS_WARNING_PUSH MYXML_CLANG_SUPPRESS_WARNING(w)
#else  // MYXML_CLANG
	#define MYXML_CLANG_SUPPRESS_WARNING_PUSH
	#define MYXML_CLANG_SUPPRESS_WARNING(w)
	#define MYXML_CLANG_SUPPRESS_WARNING_POP
	#define MYXML_CLANG_SUPPRESS_WARNING_WITH_PUSH(w)
#endif  // MYXML_CLANG

#if MYXML_COMPILER_IS(GCC)
	#define MYXML_PRAGMA_TO_STR(x) _Pragma(#x)
	#define MYXML_GCC_SUPPRESS_WARNING_PUSH _Pragma("GCC diagnostic push")
	#define MYXML_GCC_SUPPRESS_WARNING(w) MYXML_PRAGMA_TO_STR(GCC diagnostic ignored w)
	#define MYXML_GCC_SUPPRESS_WARNING_POP _Pragma("GCC diagnostic pop")
	#define MYXML_GCC_SUPPRESS_WARNING_WITH_PUSH(w) MYXML_GCC_SUPPRESS_WARNING_PUSH MYXML_GCC_SUPPRESS_WARNING(w)
#else  // MYXML_GCC
	#define MYXML_GCC_SUPPRESS_WARNING_PUSH
	#define MYXML_GCC_SUPPRESS_WARNING(w)
	#define MYXML_GCC_SUPPRESS_WARNING_POP
	#define MYXML_GCC_SUPPRESS_WARNING_WITH_PUSH(w)
#endif  // MYXML_GCC

#if MYXML_COMPILER_IS(MSVC)
	#define MYXML_MSVC_SUPPRESS_WARNING_PUSH __pragma(warning(push))
	#define MYXML_MSVC_SUPPRESS_WARNING(w) __pragma(warning(disable : w))
	#define MYXML_MSVC_SUPPRESS_WARNING_POP __pragma(warning(pop))
	#define MYXML_MSVC_SUPPRESS_WARNING_WITH_PUSH(w) MYXML_MSVC_SUPPRESS_WARNING_PUSH MYXML_MSVC_SUPPRESS_WARNING(w)
#else  // MYXML_MSVC
	#define MYXML_MSVC_SUPPRESS_WARNING_PUSH
	#define MYXML_MSVC_SUPPRESS_WARNING(w)
	#define MYXML_MSVC_SUPPRESS_WARNING_POP
	#define MYXML_MSVC_SUPPRESS_WARNING_WITH_PUSH(w)
#endif  // MYXML_MSVC

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Compiler Checks
//-----------------------------------------------------------------------------

/**
 * @defgroup check Compiler Checks
 * @{
 */

/** C version (STDC) */
#if defined(__STDC__) && (__STDC__ >= 1) && defined(__STDC_VERSION__)
	#define MYXML_STDC_VERSION __STDC_VERSION__
#else
	#define MYXML_STDC_VERSION 0
#endif

/** C++ version */
#if defined(__cplusplus)
	#define MYXML_CPP_VERSION __cplusplus
#else
  #define MYXML_CPP_VERSION 0
#endif

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

/** include check */
#ifndef MYXML_HAS_INCLUDE
  	#ifdef __has_include
    	#define MYXML_HAS_INCLUDE(x) __has_include(x)
  	#else
    	#define MYXML_HAS_INCLUDE(x) 0
  	#endif
#endif

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Compiler Attributes
//-----------------------------------------------------------------------------

/**
 * @defgroup attribute Compiler Attributes
 * @{
 */

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
  	#elif defined(__cplusplus) || MYXML_STDC_VERSION >= 199901L
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

/** likely for compiler */
#ifndef MYXML_LIKELY
  	#if MYXML_HAS_BUILTIN(__builtin_expect) || (MYXML_COMPILER_SINCE(GCC, 4, 0, 0) && MYXML_COMPILER_VERSION_MAJOR != 5)
    	#define MYXML_LIKELY(expr) __builtin_expect(!!(expr), 1)
  	#else
    	#define MYXML_LIKELY(expr) (expr)
  	#endif
#endif

/** unlikely for compiler */
#ifndef MYXML_UNLIKELY
  	#if MYXML_HAS_BUILTIN(__builtin_expect) || (MYXML_COMPILER_SINCE(GCC, 4, 0, 0) && MYXML_COMPILER_VERSION_MAJOR != 5)
    	#define MYXML_UNLIKELY(expr) __builtin_expect(!!(expr), 0)
  	#else
    	#define MYXML_UNLIKELY(expr) (expr)
  	#endif
#endif

/** compile-time constant check for compiler */
#ifndef MYXML_CONSTANT_P
  	#if MYXML_HAS_BUILTIN(__builtin_constant_p) || (MYXML_COMPILER_SINCE(GCC, 3, 0, 0))
    	#define MYXML_HAS_CONSTANT_P 1
    	#define MYXML_CONSTANT_P(value) __builtin_constant_p(value)
  	#else
    	#define MYXML_HAS_CONSTANT_P 0
    	#define MYXML_CONSTANT_P(value) 0
  	#endif
#endif

/** deprecate warning */
#ifndef MYXML_DEPRECATED
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
        #pragma message("MYXML_DEPRECATED is not supported for your compiler.")
    	#define MYXML_DEPRECATED(msg)
  	#endif
#endif

/** @} */


/** char bit check */
#if defined(CHAR_BIT)
  	#if CHAR_BIT != 8
    	#error non 8-bit char is not supported
  	#endif
#endif

/* Strict C compiler warning helpers */

#if MYXML_COMPILER_IS(CLANG) || MYXML_COMPILER_IS(GCC)
  	#define HASATTRIBUTE_UNUSED
#endif

#ifdef HASATTRIBUTE_UNUSED
  	#define MYXML_UNUSED __attribute__((__unused__))
#else
  	#define MYXML_UNUSED
#endif

/* Shim arguments are arguments that must be included in your function,
 * but serve no purpose inside.  Silence compiler warnings. */
#define SHIM(a) /*@unused@*/ a MYXML_UNUSED

/* UNUSED_PARAM() marks a shim argument in the body to silence compiler warnings
 */
#ifdef __clang__
  	#define UNUSED_PARAM(a) (void)(a);
#else
  	#define UNUSED_PARAM(a) if (0) (void)(a);
#endif

// clang-format on

#pragma region Internal

//-------------------------------------------------------------------------
// [SECTION] Defines
//-----------------------------------------------------------------------------

// clang-format off

/** @def MYXML_ENABLE_DEBUG
 * Used for input parameter checking and cheap sanity checks. There are lots of
 * asserts in every part of the code, so this will slow down applications.
 */
#if !defined(MYXML_ENABLE_DEBUG) && !defined(NDEBUG)
#if defined(NDEBUG)
#define MYXML_NDEBUG
#else
#define MYXML_DEBUG
#endif
#endif

/** @def MYXML_SANITIZE
 * Enables expensive checks that can detect issues early. Recommended for
 * running tests or when debugging issues. This will severely slow down code.
 */
#ifdef MYXML_SANITIZE
#ifndef MYXML_DEBUG
#define MYXML_DEBUG /* If sanitized mode is enabled, so is debug mode */
#endif
#endif

#if !defined( NDEBUG ) || defined( MYXML_ENABLE_ASSERT )
// MYXML_API int MyInternalAssert( const char* condition, const char* fileName, int lineNumber );

    #include <assert.h>

    /**
     * @def MYXML_ASSERT
     * @brief Apply the default assert.
     */
    #ifndef MYXML_ASSERT
        #define MYXML_ASSERT( condition ) assert(condition)                                                                                                  
            // do                                                                                                                           \ 
            // {                                                                                                                            \ 
            //     if ( !( condition ) && MyInternalAssert( #condition, __FILE__, (int)__LINE__ ) )                                          \ 
            //         MYXML_BREAKPOINT;                                                                                                       \ 
            // }                                                                                                                            \ 
            // while ( 0 )
	#else
		#define MYXML_ASSERT(x)
    #endif // MYXML_ASSERT
#else
    #define MYXML_ASSERT( ... ) ( (void)0 )
    #define MYXML_HARD_ASSERT( ... ) ( (void)0 )
    #define MYXML_SOFT_ASSERT( ... ) ( (void)0 )
#endif

#define MYXML_SUCCESS 1
#define MYXML_FAILURE 0

// C++ macros
#ifdef __cplusplus
    #define MYXML_CAST(type, x)       static_cast<type>(x)
    #define MYXML_PTRCAST(type, x)    reinterpret_cast<type>(x)
    #define MYXML_ABORT     std::abort()
	#define MYXML_INLINE inline
	#define MYXML_LITERAL(T) T
	#define MYXML_ZERO_INIT {}
#else
    #define MYXML_CAST(type, x)       ((type)x)
    #define MYXML_PTRCAST(type, x)    ((type)x)
    #define MYXML_ABORT     exit(1)
	// #define MYXML_INLINE static inline
	/// Used for C literals like (b2Vec2){1.0f, 2.0f} where C++ requires b2Vec2{1.0f, 2.0f}
	#define MYXML_LITERAL(T) (T)
	#define MYXML_ZERO_INIT {0}
#endif

// see https://github.com/scottt/debugbreak
#if defined( _MSC_VER )
    #define MYXML_BREAKPOINT __debugbreak()
#elif defined( __GNUC__ ) || defined( __clang__ )
    #define MYXML_BREAKPOINT __builtin_trap()
#else
    #if defined( MYXML_ENABLE_ASSERT )
        #include <assert.h>
        #define MYXML_BREAKPOINT MYXML_ASSERT(0)
    #else 
        #define MYXML_BREAKPOINT 
    #endif // MYXML_ENABLE_ASSERT
#endif // _MSC_VER

#ifndef MYXML_MAX_FILE_SIZE
/**
 * @def MYXML_MAX_FILE_SIZE
 * @brief Maximum XML file size in bytes.
 * @note Default is 1073741824 [`2^30`] (1GB).
 */
#define MYXML_MAX_FILE_SIZE 1073741824
#endif // MYXML_MAX_FILE_SIZE

#ifndef MYXML_INPUT_RAW_BUFFER_SIZE
/**
 * @def MYXML_INPUT_RAW_BUFFER_SIZE
 * @brief The size of the input raw buffer.
 * @note Default is 16384 [`2^14`].
 */
#define MYXML_INPUT_RAW_BUFFER_SIZE 16384
#endif // MYXML_INPUT_RAW_BUFFER_SIZE

#ifndef MYXML_OUPUT_BUFFER_SIZE
/**
 * @def MYXML_OUPUT_BUFFER_SIZE
 * @brief The size of the output buffer.
 * @note Default is 16384 [`2^14`].
 */
#define MYXML_OUPUT_BUFFER_SIZE 16384
#endif // MYXML_OUPUT_BUFFER_SIZE

#ifndef MYXML_INPUT_BUFFER_SIZE
/**
 * @def MYXML_INPUT_BUFFER_SIZE
 * @brief The size of the input buffer.
 * @note It should be possible to decode the whole raw buffer.
 * @note Default is 3 times `MYXML_INPUT_RAW_BUFFER_SIZE` .
 */
#define MYXML_INPUT_BUFFER_SIZE (MYXML_INPUT_RAW_BUFFER_SIZE * 3)
#endif // MYXML_INPUT_BUFFER_SIZE

#ifndef MYXML_OUTPUT_RAW_BUFFER_SIZE
/**
 * @def MYXML_OUTPUT_RAW_BUFFER_SIZE
 * @brief The size of the output raw buffer.
 * @note It should be possible to encode the whole output buffer.
 * @note Default is 2 times `MYXML_OUPUT_BUFFER_SIZE` .
 */
#define MYXML_OUTPUT_RAW_BUFFER_SIZE (MYXML_OUPUT_BUFFER_SIZE * 2 + 2)
#endif // MYXML_OUTPUT_RAW_BUFFER_SIZE

#ifndef MYXML_MAX_STRING_LENGTH
/**
 * @def MYXML_MAX_STRING_LENGTH
 * @brief Maximum length for XML string values.
 * @note Default is 4096 [`2^12`].
 */
#define MYXML_MAX_STRING_LENGTH 4096
#endif // MYXML_MAX_STRING_LENGTH

#ifndef MYXML_MAX_NUMBER_LENGTH
/**
 * @def MYXML_MAX_NUMBER_LENGTH
 * @brief Maximum length for XML number values.
 * @note Default is 9.
 */
#define MYXML_MAX_NUMBER_LENGTH 9
#endif // MYXML_MAX_NUMBER_LENGTH

#ifndef MYXML_INITIAL_STACK_SIZE
/**
 * @def MYXML_INITIAL_STACK_SIZE
 * @brief Initial stack size.
 * @note Default is 16.
 */
#define MYXML_INITIAL_STACK_SIZE 16
#endif // MYXML_INITIAL_STACK_SIZE

#ifndef MYXML_INITIAL_QUEUE_SIZE
/**
 * @def MYXML_INITIAL_QUEUE_SIZE
 * @brief Initial queue size.
 * @note Default is 16.
 */
#define MYXML_INITIAL_QUEUE_SIZE 16
#endif // MYXML_INITIAL_QUEUE_SIZE

#ifndef MYXML_INITIAL_STRING_SIZE
/**
 * @def MYXML_INITIAL_STRING_SIZE
 * @brief Initial string size.
 * @note Default is 16.
 */
#define MYXML_INITIAL_STRING_SIZE 16
#endif // MYXML_INITIAL_STRING_SIZE

//-----------------------------------------------------------------------------
// [SECTION] Memory Management
//-----------------------------------------------------------------------------

/*
 * Allocate a dynamic memory block.
 */
#define MYXML_MALLOC(size)  myMalloc(size)

/*
 * Free a dynamic memory block.
 */
#define MYXML_FREE(pointer) myFree(pointer)

/*
 * Reallocate a dynamic memory block.
 */
#define MYXML_REALLOC(pointer) myRealloc(pointer,size)

// clang-format on

//-----------------------------------------------------------------------------
// [SECTION] Parser
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [SECTION] Emitter
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [SECTION] Reader
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [SECTION] Writer
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [SECTION] Data Structures
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [SECTION] C Only Functions
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

//-----------------------------------------------------------------------------
// [SECTION] Declarations
//-----------------------------------------------------------------------------

#pragma region C Dec

#if !defined(MYXML_DISABLE_READER) || !MYXML_DISABLE_READER

//-----------------------------------------------------------------------------
// [SECTION] Scanner
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [SECTION] Parser
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [SECTION] Reader
//-----------------------------------------------------------------------------

#endif  // MYXML_DISABLE_READER

#if !defined(MYXML_DISABLE_WRITER) || !MYXML_DISABLE_WRITER

//-----------------------------------------------------------------------------
// [SECTION] Emitter
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [SECTION] Dumper
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [SECTION] Writer
//-----------------------------------------------------------------------------

#endif  // MYXML_DISABLE_WRITER

#pragma endregion  // C Declarations

#pragma region C Def

#if !defined(MYXML_DISABLE_READER) || !MYXML_DISABLE_READER

#pragma region Scanner

#pragma endregion  // Scanner

#pragma region Parser

#pragma endregion  // Parser

#pragma region Reader

#pragma endregion  // Reader

#endif  // MYXML_DISABLE_READER

#if !defined(MYXML_DISABLE_WRITER) || !MYXML_DISABLE_WRITER

#pragma region Writer

#pragma endregion  // Writer

#pragma region Dumper

#pragma endregion  // Dumper

#pragma region Emitter

#pragma endregion  // Emitter

#endif  // MYXML_DISABLE_WRITER

#pragma endregion  // C Definations

#ifdef __cplusplus
}
#endif  // __cplusplus

//-----------------------------------------------------------------------------
// [SECTION] C++ Only Classes
//-----------------------------------------------------------------------------

#ifdef __cplusplus

#pragma region CxxInternal

namespace myxml {
inline namespace internal {

#if !defined(MYXML_DISABLE_READER) || !MYXML_DISABLE_READER
#endif  // MYXML_DISABLE_READER

#if !defined(MYXML_DISABLE_WRITER) || !MYXML_DISABLE_WRITER
#endif  // MYXML_DISABLE_WRITER

};  // namespace internal
};  // namespace myxml

#pragma endregion  // CxxInternal

#endif  //__cplusplus

#pragma endregion  // Internal

#pragma region Myxml

//-----------------------------------------------------------------------------
// [SECTION] C Only Functions
//-----------------------------------------------------------------------------

#pragma region C

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#ifdef __cplusplus
}
#endif  // __cplusplus

#pragma endregion  // C

//-----------------------------------------------------------------------------
// [SECTION] C++ Only Classes
//-----------------------------------------------------------------------------

#pragma region Cpp

#ifdef __cplusplus

namespace myxml {

#if !defined(MYXML_DISABLE_READER) || !MYXML_DISABLE_READER

#pragma region Reader

#pragma endregion  // Reader

#endif  // MYXML_DISABLE_READER

#pragma region Writer

#if !defined(MYXML_DISABLE_WRITER) || !MYXML_DISABLE_WRITER

#pragma endregion  // Writer

#endif  // MYXML_DISABLE_WRITER

};  // namespace myxml

#endif  //__cplusplus

#pragma endregion  // Cpp

#pragma endregion  // Myxml

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