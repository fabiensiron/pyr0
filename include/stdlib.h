/*
 * Copyright (C) 2008 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#ifndef _STDLIB_H_
#define _STDLIB_H_

#include <kernel/kernel.h>

#include <malloc.h>
#include <string.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define exit(i) panic("return code: %d\n")
#define abort(i) panic("abort code: %d\n")

extern long strtol(const char *, char **, int);
extern long long strtoll(const char *, char **, int);
extern unsigned long strtoul(const char *, char **, int);
extern unsigned long long strtoull(const char *, char **, int);
extern double strtod(const char *nptr, char **endptr);

static inline float strtof(const char *nptr, char **endptr)
{
    return (float)strtod(nptr, endptr);
}

extern int atoi(const char *);
extern long atol(const char *);
extern long long atoll(const char *);

static inline double atof(const char *nptr)
{
    return (strtod(nptr, NULL));
}

static inline int abs(int __n) {
    return (__n < 0) ? -__n : __n;
}

static inline long labs(long __n) {
    return (__n < 0L) ? -__n : __n;
}

static inline long long llabs(long long __n) {
    return (__n < 0LL) ? -__n : __n;
}

//extern int system(const char * string);
#define system(s) (0)

extern void qsort(void *, size_t, size_t, int (*)(const void *, const void *));


#endif /* _STDLIB_H_ */
