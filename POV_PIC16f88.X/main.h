/* 
 * File:   main.h
 * Author: Jc
 *
 * Created on 29 de octubre de 2013, 1:01
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

    char dictionary[9][10] = {
        {'A', 0x00, 0x1f, 0x3f, 0x6c, 0xcc, 0x6c, 0x3f, 0x1f, '\0'},
        {'B', 0x00, 0xff, 0xff, 0x99, 0x99, 0x99, 0x99, 0x99, '\0'},
        {'E', 0x00, 0xff, 0xff, 0x99, 0x99, 0x99, 0x99, 0x99, '\0'},
        {'L', 0x00, 0xff, 0xff, 0xff, 0x03, 0x03, 0x03, 0x03, '\0'},
        {'H', 0x00, 0xff, 0xff, 0x18, 0x18, 0x18, 0xff, 0xff, '\0'},
        {'O', 0x00, 0xff, 0xff, 0xc3, 0xc3, 0xc3, 0xff, 0xff, '\0'}
    };
    //char _A[9] = {0x00, 0x1f, 0x3f, 0x6c, 0xcc, 0x6c, 0x3f, 0x1f, '\0'};
    //char _E[9] = {0x00, 0xff, 0xff, 0x99, 0x99, 0x99, 0x99, 0x99, '\0'};
    //char _H[9] = {0x00, 0xff, 0xff, 0x18, 0x18, 0x18, 0xff, 0xff, '\0'};
    //char _L[9] = {0x00, 0xff, 0xff, 0xff, 0x03, 0x03, 0x03, 0x03, '\0'};
    //char _M[9] = {0x00, 0xff, 0xff, 0x60, 0x30, 0x60, 0xff, 0xff, '\0'};
    //char _N[9] = {0x00, 0xff, 0xff, 0x30, 0x18, 0x0c, 0xff, 0xff, '\0'};
    //char _O[9] = {0x00, 0xff, 0xff, 0xc3, 0xc3, 0xc3, 0xff, 0xff, '\0'};
    //char _P[9] = {0x00, 0xff, 0xff, 0xc8, 0xc8, 0xc8, 0xf8, 0xf8, '\0'};
    //char _R[9] = {0x00, 0xff, 0xff, 0xc8, 0xcc, 0xcE, 0xfb, 0xf9, '\0'};
    //char _EMPTY[9] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, '\0'};



#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

