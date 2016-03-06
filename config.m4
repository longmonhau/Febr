dnl $Id$
dnl config.m4 for extension Febr

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(Febr, for Febr support,
dnl Make sure that the comment is aligned:
dnl [  --with-Febr             Include Febr support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(Febr, whether to enable Febr support,
dnl Make sure that the comment is aligned:
dnl [  --enable-Febr           Enable Febr support])

if test "$PHP_FEBR" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-Febr -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/Febr.h"  # you most likely want to change this
  dnl if test -r $PHP_FEBR/$SEARCH_FOR; then # path given as parameter
  dnl   FEBR_DIR=$PHP_FEBR
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for Febr files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       FEBR_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$FEBR_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the Febr distribution])
  dnl fi

  dnl # --with-Febr -> add include path
  dnl PHP_ADD_INCLUDE($FEBR_DIR/include)

  dnl # --with-Febr -> check for lib and symbol presence
  dnl LIBNAME=Febr # you may want to change this
  dnl LIBSYMBOL=Febr # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $FEBR_DIR/$PHP_LIBDIR, FEBR_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_FEBRLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong Febr lib version or lib not found])
  dnl ],[
  dnl   -L$FEBR_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(FEBR_SHARED_LIBADD)

  PHP_NEW_EXTENSION(Febr, Febr.c, $ext_shared)
fi
