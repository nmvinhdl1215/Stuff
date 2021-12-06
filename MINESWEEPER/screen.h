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
/* Checkout https://docs.microsoft.com/en-us/windows/console/clearing-the-screen for more information on the following code */
inline int clear_screen() {
    HANDLE hStdOut;

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // Fetch existing console mode so we correctly add a flag and not turn off others
    DWORD mode = 0;
    if (!GetConsoleMode(hStdOut, &mode))
    {
        return ::GetLastError();
    }

    // Hold original mode to restore on exit to be cooperative with other command-line apps.
    const DWORD originalMode = mode;
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    // Try to set the mode.
    if (!SetConsoleMode(hStdOut, mode))
    {
        return ::GetLastError();
    }

    // Write the sequence for clearing the display.
    DWORD written = 0;
    PCWSTR sequence = L"\x1b[2J";
    if (!WriteConsoleW(hStdOut, sequence, (DWORD)wcslen(sequence), &written, NULL))
    {
        // If we fail, try to restore the mode on the way out.
        SetConsoleMode(hStdOut, originalMode);
        return ::GetLastError();
    }

    // To also clear the scroll back, emit L"\x1b[3J" as well.
    // 2J only clears the visible window and 3J only clears the scroll back.

    // Restore the mode on the way out to be nice to other command-line applications.
    SetConsoleMode(hStdOut, originalMode);
#endif

    return 0;
}
#endif