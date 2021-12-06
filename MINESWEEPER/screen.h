#ifndef _screen_h_
#define _screen_h_
// screen.h - console manipulation header

#include <stdlib.h>
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif
/* Inlining in different compiler
 * Checkout https://www.greenend.org.uk/rjk/tech/inline.html
 */
#if __GNUC__ && !__GNUC_STDC_INLINE__
	#define INLINE extern inline
#else
	#define INLINE inline
#endif

/** clear_screen - Clear terminal
 */
#ifdef __unix__
#ifdef __GNUC__
__attribute__((always_inline))
#endif /* not __GNUC__ */
INLINE void clear_screen() {
	printf("\033c");}
#elif defined _WIN32
DWORD clear_screen();
#endif

#endif
