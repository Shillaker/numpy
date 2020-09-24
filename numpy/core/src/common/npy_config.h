#ifndef _NPY_NPY_CONFIG_H_
#define _NPY_NPY_CONFIG_H_

#include "config.h"
#include "npy_cpu_features.h"
#include "numpy/numpyconfig.h"
#include "numpy/npy_cpu.h"
#include "numpy/npy_os.h"

/* blacklist */

/* Disable broken Sun Workshop Pro math functions */
#ifdef __SUNPRO_C

#undef HAVE_ATAN2
#undef HAVE_ATAN2F
#undef HAVE_ATAN2L

#endif

/* Disable broken MS math functions */
#if (defined(_MSC_VER) && (_MSC_VER < 1900)) || defined(__MINGW32_VERSION)

#undef HAVE_ATAN2
#undef HAVE_ATAN2F
#undef HAVE_ATAN2L

#undef HAVE_HYPOT
#undef HAVE_HYPOTF
#undef HAVE_HYPOTL

#endif

#if defined(_MSC_VER) && (_MSC_VER >= 1900)

#undef HAVE_CASIN
#undef HAVE_CASINF
#undef HAVE_CASINL
#undef HAVE_CASINH
#undef HAVE_CASINHF
#undef HAVE_CASINHL
#undef HAVE_CATAN
#undef HAVE_CATANF
#undef HAVE_CATANL
#undef HAVE_CATANH
#undef HAVE_CATANHF
#undef HAVE_CATANHL
#undef HAVE_CSQRT
#undef HAVE_CSQRTF
#undef HAVE_CSQRTL
#undef HAVE_CLOG
#undef HAVE_CLOGF
#undef HAVE_CLOGL
#undef HAVE_CACOS
#undef HAVE_CACOSF
#undef HAVE_CACOSL
#undef HAVE_CACOSH
#undef HAVE_CACOSHF
#undef HAVE_CACOSHL

#endif

/* MSVC _hypot messes with fp precision mode on 32-bit, see gh-9567 */
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(_WIN64)

#undef HAVE_CABS
#undef HAVE_CABSF
#undef HAVE_CABSL

#undef HAVE_HYPOT
#undef HAVE_HYPOTF
#undef HAVE_HYPOTL

#endif


/* Intel C for Windows uses POW for 64 bits longdouble*/
#if defined(_MSC_VER) && defined(__INTEL_COMPILER)
#if defined(HAVE_POWL) && (NPY_SIZEOF_LONGDOUBLE == 8)
#undef HAVE_POWL
#endif
#endif /* defined(_MSC_VER) && defined(__INTEL_COMPILER) */

/* powl gives zero division warning on OS X, see gh-8307 */
#if defined(HAVE_POWL) && defined(NPY_OS_DARWIN)
#undef HAVE_POWL
#endif

/* Disable broken gnu trig functions */
#if defined(HAVE_FEATURES_H)
#include <features.h>

#if defined(__GLIBC__)
#if !__GLIBC_PREREQ(2, 18)

#undef HAVE_CASIN
#undef HAVE_CASINF
#undef HAVE_CASINL
#undef HAVE_CASINH
#undef HAVE_CASINHF
#undef HAVE_CASINHL
#undef HAVE_CATAN
#undef HAVE_CATANF
#undef HAVE_CATANL
#undef HAVE_CATANH
#undef HAVE_CATANHF
#undef HAVE_CATANHL
#undef HAVE_CACOS
#undef HAVE_CACOSF
#undef HAVE_CACOSL
#undef HAVE_CACOSH
#undef HAVE_CACOSHF
#undef HAVE_CACOSHL

#endif /* __GLIBC_PREREQ(2, 18) */
#endif /* defined(__GLIBC_PREREQ) */

#endif /* defined(HAVE_FEATURES_H) */

// WebAssembly overrides
#ifdef __wasm__

#define SIZEOF_PY_INTPTR_T 4
#define SIZEOF_OFF_T 4
#define SIZEOF_PY_LONG_LONG 8

// Switch off all long-related maths functions
#undef HAVE_SINL
#undef HAVE_COSL
#undef HAVE_TANL
#undef HAVE_SINHL
#undef HAVE_COSHL
#undef HAVE_TANHL
#undef HAVE_FABSL
#undef HAVE_FLOORL
#undef HAVE_CEILL
#undef HAVE_RINTL
#undef HAVE_TRUNCL
#undef HAVE_SQRTL
#undef HAVE_LOG10L
#undef HAVE_LOGL
#undef HAVE_LOG1PL
#undef HAVE_EXPL
#undef HAVE_EXPM1L
#undef HAVE_ASINL
#undef HAVE_ACOSL
#undef HAVE_ATANL
#undef HAVE_ASINHL
#undef HAVE_ACOSHL
#undef HAVE_ATANHL
#undef HAVE_HYPOTL
#undef HAVE_ATAN2L
#undef HAVE_POWL
#undef HAVE_FMODL
#undef HAVE_MODFL
#undef HAVE_FREXPL
#undef HAVE_LDEXPL
#undef HAVE_EXP2L
#undef HAVE_LOG2L
#undef HAVE_COPYSIGNL
#undef HAVE_NEXTAFTERL
#undef HAVE_CBRTL
#undef HAVE_CABSL
#undef HAVE_CACOSL
#undef HAVE_CACOSHL
#undef HAVE_CARGL
#undef HAVE_CASINL
#undef HAVE_CASINHL
#undef HAVE_CATANL
#undef HAVE_CATANHL
#undef HAVE_CCOSL
#undef HAVE_CCOSHL
#undef HAVE_CEXPL
#undef HAVE_CIMAGL
#undef HAVE_CLOGL
#undef HAVE_CONJL
#undef HAVE_CPOWL
#undef HAVE_CPROJL
#undef HAVE_CREALL
#undef HAVE_CSINL
#undef HAVE_CSINHL
#undef HAVE_CSQRTL
#undef HAVE_CTANL
#undef HAVE_CTANHL

#define NPY_RELAXED_STRIDES_CHECKING 1

// Use libc float printing
#define HAVE_STRTOLL 1
#define HAVE_STRTOULL 1
#define HAVE_STRTOLD_L 1

// Don't let numpy guess the long double format
#define HAVE_LDOUBLE_IEEE_DOUBLE_LE 1

#define NPY_PY3K 1

#endif // __wasm__

#endif
