#ifndef _screen_h_
#define _screen_h_
// screen.h - console manipulation header
#include "debug.h"
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
#include <stdlib.h>
#include <stdio.h>
#ifdef __GNUC__
__attribute__((always_inline))
#endif /* not __GNUC__ */
INLINE void clear_screen() {
#ifndef MINE_DEBUG
	printf("\033c");
#endif /*MINE_DEBUG */
}
#elif defined _WIN32
#ifdef MINE_DEBUG
INLINE DWORD clear_screen() {}
#elif /* not MINE_DEBUG */
DWORD clear_screen();
#endif /* not MINE_DEBUG*/
#endif /* not __unix__ */

#endif
