// //
// // Copyright (C) 1999 and onwards Google, Inc.

#ifndef BASE_PORT_H_
#define BASE_PORT_H_

// //
// // Tell the compiler to do printf format string checking if the
// // compiler supports it; see the 'format' attribute in
// // <http://gcc.gnu.org/onlinedocs/gcc-4.3.0/gcc/Function-Attributes.html>.
// //
// // N.B.: As the GCC manual states, "[s]ince non-static C++ methods
// // have an implicit 'this' argument, the arguments of such methods
// // should be counted from two, not one."
// //
// //
// // Prevent the compiler from padding a structure to natural alignment
// //
#ifdef _MSC_VER

    #define PRINTF_ATTRIBUTE(string_index, first_to_check) \

    #define PACK( __Declaration__ ) \
        __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )


#elif defined(__GNUC__)

    #define PRINTF_ATTRIBUTE(string_index, first_to_check) \
        __attribute__((__format__ (__printf__, string_index, first_to_check)))

    #define PACK( __Declaration__ ) \
        __Declaration__ __attribute__((__packed__))

#endif

#endif  // BASE_PORT_H_
