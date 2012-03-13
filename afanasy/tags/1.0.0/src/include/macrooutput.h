//###################################################################################
#include <stdio.h>
//#################### OUPUT ERRORS FORMATING ######################################

#define AFERROR( msg) {fprintf(stderr,"AFERROR: %s",msg);fflush( stderr);}
#define AFERRAR( msg, ...) {fprintf(stderr,"AFERROR: ");fprintf( stderr, msg, __VA_ARGS__);fflush( stderr);}
#define AFERRPE( msg) {fprintf(stderr,"AFERROR: ");fflush( stderr);perror( msg );fflush( stderr);}
#define AFERRPA( msg, ...) {fprintf(stderr,"AFERROR: ");fprintf( stderr, msg, __VA_ARGS__);fflush( stderr);perror(0);fflush( stderr);}
//
//############## OUPUT INFO FORMATING, if AFOUTPUT only ##############################
#ifdef AFOUTPUT
#define AFINFA( msg, ...) {fprintf(stdout,"AFINFO: ");fprintf(stdout,msg,__VA_ARGS__);fflush( stderr);}
#else
#define AFINFA( msg, ...) {}
#endif
//
#ifdef AFOUTPUT
#define AFINFO( msg) {fprintf(stdout,"AFINFO: %s", msg);fflush( stdout);}
#else
#define AFINFO( msg) {}
#endif
//###################################################################################
//
//###################################################################################
