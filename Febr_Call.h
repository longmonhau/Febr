#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifndef FEBR_API_H
#define FEBR_API_H
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_Febr.h"
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct
{
	zval 		*object;
	zval 		*method;
	zend_uint  	args_num;
	zval 		*args;
} Thread_Param;

typedef void*(*funcPtr)(void*);

void* 	Febr_call_user_function( void *a );

void 	Febr_error_log( const char *file, const char *msg );

int 	check_user_function_exist( char *fname );

#endif