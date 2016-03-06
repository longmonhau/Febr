#include "Febr_Call.h"

extern char *log_file;

void* Febr_call_user_function( void *a )
{
	Thread_Param *p = (Thread_Param*)a;
	zval *reval;
	MAKE_STD_ZVAL(reval);
	if( call_user_function(CG(function_table), &(p->object), p->method, reval, p->args_num, &(p->args) TSRMLS_DC ) == FAILURE )
	{
		Febr_error_log(log_file, "Calling user func failed.");
		php_printf("call usr function failed!");
	}
	php_printf("called function success!");
	return NULL;
}

void Febr_error_log( const char *file, const char *msg )
{
	FILE *fp;
	fp = fopen(file, "a+");
	if( !fp )
	{
		return;
	}
	time_t timep;
	time(&timep);
	fprintf(fp, "%s: %s\n",ctime(&timep), msg );
	fclose(fp);
}

int check_user_function_exist( char *fname )
{
	//php_printf("checking php function %s", fname );
	zval **reval;
	int fname_len = sizeof(*fname);
	//php_printf("func name length: %d",fname_len);
	if( !zend_hash_find(CG(function_table), "fuck", sizeof("fuck"), (void **)&reval ) == SUCCESS )
	{
		return -1;
	}
	return 0;
}