#ifndef IMAKE_MDEP_H_NEW
#define IMAKE_MDEP_H_NEW

/* note:  also look at ../makedepend/def.h unless you
 *        divert depend build somehow
 */

#define         ARGUMENTS       50
#define         DEFAULT_CPP   "/usr/bin/cpp"
char           *cpp_argv[ARGUMENTS] = { "cpp", "-I." };
char           *make_argv[ARGUMENTS] = {"make"};

#endif
