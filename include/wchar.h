/*
 *
 * Copyright (C) 2015 PSP2SDK Project
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is modified for PSP2 by PSP2SDK Team
 */

#ifndef _WCHAR_H_
#define _WCHAR_H_

#include <_ansi.h>

#define __need_size_t
#define __need_wchar_t
#define __need_wint_t
#define __need_NULL
#include <stddef.h>

#define __need___va_list
#include <stdarg.h>

/* For _mbstate_t definition. */
#include <sys/_types.h>
#include <sys/cdefs.h>
/* For __STDC_ISO_10646__ */
#include <sys/features.h>

#ifndef WEOF
# define WEOF ((wint_t)-1)
#endif

/* This must match definition in <stdint.h> */
#ifndef WCHAR_MIN
#ifdef __WCHAR_MIN__
#define WCHAR_MIN __WCHAR_MIN__
#elif defined(__WCHAR_UNSIGNED__) || (L'\0' - 1 > 0)
#define WCHAR_MIN (0 + L'\0')
#else
#define WCHAR_MIN (-0x7fffffff - 1 + L'\0')
#endif
#endif

/* This must match definition in <stdint.h> */
#ifndef WCHAR_MAX
#ifdef __WCHAR_MAX__
#define WCHAR_MAX __WCHAR_MAX__
#elif defined(__WCHAR_UNSIGNED__) || (L'\0' - 1 > 0)
#define WCHAR_MAX (0xffffffffu + L'\0')
#else
#define WCHAR_MAX (0x7fffffff + L'\0')
#endif
#endif

_BEGIN_STD_C

typedef struct __FILE FILE;

/* As required by POSIX.1-2008, declare tm as incomplete type.
   The actual definition is in time.h. */
struct tm;

#ifndef _MBSTATE_T
#define _MBSTATE_T
typedef _mbstate_t mbstate_t;
#endif /* _MBSTATE_T */

wint_t	_EXFUN(btowc, (int));
int	_EXFUN(wctob, (wint_t));
size_t	_EXFUN(mbrlen, (const char *__restrict, size_t, mbstate_t *__restrict));
size_t	_EXFUN(mbrtowc, (wchar_t *__restrict, const char *__restrict, size_t,
						mbstate_t *__restrict));
int	_EXFUN(mbsinit, (const mbstate_t *));
size_t	_EXFUN(mbsnrtowcs, (wchar_t *__restrict, const char **__restrict,
				size_t, size_t, mbstate_t *__restrict));
size_t	_EXFUN(mbsrtowcs, (wchar_t *__restrict, const char **__restrict, size_t,
				mbstate_t *__restrict));
size_t	_EXFUN(wcrtomb, (char *__restrict, wchar_t, mbstate_t *__restrict));
size_t	_EXFUN(wcsnrtombs, (char *__restrict, const wchar_t **__restrict,
				size_t, size_t, mbstate_t *__restrict));
size_t	_EXFUN(wcsrtombs, (char *__restrict, const wchar_t **__restrict,
				size_t, mbstate_t *__restrict));
int	_EXFUN(wcscasecmp, (const wchar_t *, const wchar_t *));
wchar_t	*_EXFUN(wcscat, (wchar_t *__restrict, const wchar_t *__restrict));
wchar_t	*_EXFUN(wcschr, (const wchar_t *, wchar_t));
int	_EXFUN(wcscmp, (const wchar_t *, const wchar_t *));
int	_EXFUN(wcscoll, (const wchar_t *, const wchar_t *));
wchar_t	*_EXFUN(wcscpy, (wchar_t *__restrict, const wchar_t *__restrict));
wchar_t	*_EXFUN(wcpcpy, (wchar_t *__restrict,
				 const wchar_t *__restrict));
wchar_t	*_EXFUN(wcsdup, (const wchar_t *));
size_t	_EXFUN(wcscspn, (const wchar_t *, const wchar_t *));
size_t  _EXFUN(wcsftime, (wchar_t *__restrict, size_t,
				const wchar_t *__restrict, const struct tm *__restrict));
size_t	_EXFUN(wcslcat, (wchar_t *, const wchar_t *, size_t));
size_t	_EXFUN(wcslcpy, (wchar_t *, const wchar_t *, size_t));
size_t	_EXFUN(wcslen, (const wchar_t *));
int	_EXFUN(wcsncasecmp, (const wchar_t *, const wchar_t *, size_t));
wchar_t	*_EXFUN(wcsncat, (wchar_t *__restrict,
				 const wchar_t *__restrict, size_t));
int	_EXFUN(wcsncmp, (const wchar_t *, const wchar_t *, size_t));
wchar_t	*_EXFUN(wcsncpy, (wchar_t *__restrict,
				 const wchar_t *__restrict, size_t));
wchar_t	*_EXFUN(wcpncpy, (wchar_t *__restrict,
				 const wchar_t *__restrict, size_t));
size_t	_EXFUN(wcsnlen, (const wchar_t *, size_t));
wchar_t	*_EXFUN(wcspbrk, (const wchar_t *, const wchar_t *));
wchar_t	*_EXFUN(wcsrchr, (const wchar_t *, wchar_t));
size_t	_EXFUN(wcsspn, (const wchar_t *, const wchar_t *));
wchar_t	*_EXFUN(wcsstr, (const wchar_t *__restrict,
				 const wchar_t *__restrict));
wchar_t	*_EXFUN(wcstok, (wchar_t *__restrict, const wchar_t *__restrict,
				 wchar_t **__restrict));
double _EXFUN(wcstod, (const wchar_t *__restrict, wchar_t **__restrict));
float _EXFUN(wcstof, (const wchar_t *__restrict, wchar_t **__restrict));
int	_EXFUN(wcswidth, (const wchar_t *, size_t));
size_t	_EXFUN(wcsxfrm, (wchar_t *__restrict, const wchar_t *__restrict,
				size_t));
int	_EXFUN(wcwidth, (const wchar_t));
wchar_t	*_EXFUN(wmemchr, (const wchar_t *, wchar_t, size_t));
int	_EXFUN(wmemcmp, (const wchar_t *, const wchar_t *, size_t));
wchar_t	*_EXFUN(wmemcpy, (wchar_t *__restrict, const wchar_t *__restrict,
				 size_t));
wchar_t	*_EXFUN(wmemmove, (wchar_t *, const wchar_t *, size_t));
wchar_t	*_EXFUN(wmemset, (wchar_t *, wchar_t, size_t));

long    _EXFUN(wcstol, (const wchar_t *__restrict, wchar_t **__restrict, int));
long long _EXFUN(wcstoll, (const wchar_t *__restrict, wchar_t **__restrict,
				  int));
unsigned long _EXFUN(wcstoul, (const wchar_t *__restrict, wchar_t **__restrict,
					  int));
unsigned long long _EXFUN(wcstoull, (const wchar_t *__restrict,
						   wchar_t **__restrict, int));
/* On platforms where long double equals double.  */
#ifdef _LDBL_EQ_DBL
long double _EXFUN(wcstold, (const wchar_t *, wchar_t **));
#endif /* _LDBL_EQ_DBL */

wint_t _EXFUN(fgetwc, (FILE *));
wchar_t *_EXFUN(fgetws, (wchar_t *__restrict, int, FILE *__restrict));
wint_t _EXFUN(fputwc, (wchar_t, FILE *));
int _EXFUN(fputws, (const wchar_t *__restrict, FILE *__restrict));
int _EXFUN (fwide, (FILE *, int));
wint_t _EXFUN (getwc, (FILE *));
wint_t _EXFUN (getwchar, (void));
wint_t _EXFUN(putwc, (wchar_t, FILE *));
wint_t _EXFUN(putwchar, (wchar_t));
wint_t _EXFUN (ungetwc, (wint_t wc, FILE *));

FILE *_EXFUN (open_wmemstream, (wchar_t **, size_t *));

#ifndef __VALIST
#ifdef __GNUC__
#define __VALIST __gnuc_va_list
#else
#define __VALIST char*
#endif
#endif

int	_EXFUN(fwprintf, (FILE *__restrict, const wchar_t *__restrict, ...));
int	_EXFUN(swprintf, (wchar_t *__restrict, size_t,
			const wchar_t *__restrict, ...));
int	_EXFUN(vfwprintf, (FILE *__restrict, const wchar_t *__restrict,
			__VALIST));
int	_EXFUN(vswprintf, (wchar_t *__restrict, size_t,
			const wchar_t *__restrict, __VALIST));
int	_EXFUN(vwprintf, (const wchar_t *__restrict, __VALIST));
int	_EXFUN(wprintf, (const wchar_t *__restrict, ...));

int	_EXFUN(fwscanf, (FILE *__restrict, const wchar_t *__restrict, ...));
int	_EXFUN(swscanf, (const wchar_t *__restrict,
			const wchar_t *__restrict, ...));
int	_EXFUN(vfwscanf, (FILE *__restrict, const wchar_t *__restrict,
			__VALIST));
int	_EXFUN(vswscanf, (const wchar_t *__restrict, const wchar_t *__restrict,
			__VALIST));
int	_EXFUN(vwscanf, (const wchar_t *__restrict, __VALIST));
int	_EXFUN(wscanf, (const wchar_t *__restrict, ...));

extern FILE _Stdin, _Stdout;

#define getwc(fp)	fgetwc(fp)
#define putwc(wc,fp)	fputwc((wc), (fp))
#define getwchar()	fgetwc(&_Stdin)
#define putwchar(wc)	fputwc((wc), &_Stdout)

_END_STD_C

#endif /* _WCHAR_H_ */
