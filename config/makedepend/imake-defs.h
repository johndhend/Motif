#ifndef IMAKE_Z_MDEP_H
#define IMAKE_Z_MDEP_H
struct symtab	predefs[] = {

#if defined(__BIG_ENDIAN__)
	{"__BIG_ENDIAN__", "1"},
#endif
#if defined(__LITTLE_ENDIAN__)
	{"__LITTLE_ENDIAN__", "1"},
#endif

{NULL, NULL} };
#endif
