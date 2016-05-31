#ifndef TP_COMPILER
#define TP_COMPILER 1
#endif

#include <tinypy/tp.h>
#include <tinypy/dict.h>
#include <tinypy/misc.h>
#include <tinypy/string.h>
#include <tinypy/builtins.h>
#include <tinypy/gc.h>
#include <tinypy/ops.h>

void tp_compiler(TP);
#include <tinypy/vm.h>

tp_obj tp_None = {TP_NONE};

#include "bc.c"

#if TP_COMPILER

void tp_compiler(TP) {
	tp_import(tp,0,"tokenize",tp_tokenize,sizeof(tp_tokenize));
	tp_import(tp,0,"parse",tp_parse,sizeof(tp_parse));
	tp_import(tp,0,"encode",tp_encode,sizeof(tp_encode));
	tp_import(tp,0,"py2bc",tp_py2bc,sizeof(tp_py2bc));
	tp_ez_call(tp,"py2bc","_init",tp_None);
}
#else
void tp_compiler(TP) { }
#endif

/**/
