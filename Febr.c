/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#include "Febr_Call.H"

/* If you declare any globals in php_Febr.h uncomment this:*/
ZEND_DECLARE_MODULE_GLOBALS(Febr)


/* True global resources - no need for thread safety here */
static int le_Febr;
char *log_file;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini*/
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("Febr.error_log_file", "/tmp/febr_error", PHP_INI_ALL, NULL, FebrErrorOutPutPath, zend_Febr_globals, Febr_globals)
PHP_INI_END()
/**/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_Febr_compiled(string arg)
   Return a string to confirm that the module is compiled in */
/*PHP_FUNCTION(confirm_Febr_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "Febr", arg);
	RETURN_STRINGL(strg, len, 0);
}*/
ZEND_FUNCTION(Febr_Call)
{
	zval *func, *args;
	MAKE_STD_ZVAL(args);
	ZVAL_NULL(args);

	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"z|z",&func,&args) == FAILURE )
	{
		//php_error_docref(NULL TSRMLS_CC, E_ERROR,"Call to undefined function: %s()", func->value.str.val);
		return;
	}
	
	Thread_Param *p = (Thread_Param*)emalloc(sizeof(Thread_Param));

	if( Z_TYPE_P(func) == IS_STRING )
	{
		char *fname = func->value.str.val;
		if(check_user_function_exist(fname) == -1 )
		{
			char msg[100];
			sprintf(msg,"Calling an undefined function %s()", fname);
			//php_printf("Calling a undefined function %s()",msg);
			Febr_error_log( log_file, msg);
			return;
		}

		p->object = NULL;
		p->method = func;

		if( Z_TYPE_P(args) == IS_NULL )
		{
			p->args_num = 0;
			p->args = NULL;
		}
		if(Z_TYPE_P(args) == IS_STRING )
		{
			p->args_num = 1;
			p->args = args;
		}
		if( Z_TYPE_P(args) == IS_ARRAY )
		{
			//
		}
	}
	pthread_t febr_thread;
	funcPtr fp = &Febr_call_user_function;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if( pthread_create(&febr_thread, &attr, fp, p) != 0 )
	{
		php_printf("creating pthread failed");
		return;
	}
	php_printf("thread id: %p\n",&febr_thread);
	pthread_attr_destroy (&attr);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_Febr_init_globals
 */
/* Uncomment this function if you have INI entries*/
static void php_Febr_init_globals(zend_Febr_globals *Febr_globals)
{
	//Febr_globals->ThreadNum = 10;
	//Febr_globals->ErrorOutPutPath = NULL;
}
/**/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(Febr)
{
	/* If you have INI entries, uncomment these lines */
	REGISTER_INI_ENTRIES();
	log_file = INI_STR("Febr.error_log_file");
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(Febr)
{
	/* uncomment this line if you have INI entries*/
	UNREGISTER_INI_ENTRIES();
	
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(Febr)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(Febr)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(Febr)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "Febr support", "enabled");
	php_info_print_table_row(2, "Halo world", "I just met a girl named JiaYi!");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini*/
	DISPLAY_INI_ENTRIES();
	
}
/* }}} */

/* {{{ Febr_functions[]
 *
 * Every user visible function must have an entry in Febr_functions[].
 */
const zend_function_entry Febr_functions[] = {
	//PHP_FE(confirm_Febr_compiled,	NULL)		/* For testing, remove later. */
	ZEND_FE(Febr_Call, NULL)
	PHP_FE_END	/* Must be the last line in Febr_functions[] */
};
/* }}} */

/* {{{ Febr_module_entry
 */
zend_module_entry Febr_module_entry = {
	STANDARD_MODULE_HEADER,
	"Febr",
	Febr_functions,
	PHP_MINIT(Febr),
	PHP_MSHUTDOWN(Febr),
	PHP_RINIT(Febr),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(Febr),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(Febr),
	PHP_FEBR_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_FEBR
ZEND_GET_MODULE(Febr)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
