/*
 * File: runtime-entry.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */

#include <atomos/kernel.h>
#include <stdio.h>
#include <setjmp.h>

#include <tinypy/tp.h>
#include <tinypy/dict.h>
#include <tinypy/vm.h>

void *code_p;
long code_l;
jmp_buf except_jmp;

#include <tinypy/modules.h>

void init_modules(TP)
{
	unsigned i;
	for(i = 0; modules_init_vector[i]; i++)
		modules_init_vector[i](tp);
}

#include <stdlib.h>
#include <string.h>

char *sub_interpreter(char *buf, unsigned len_)
{
	unsigned len, len__, code_size = 1024;
	char subbuf[81];
	char *subbuf_r = malloc(sizeof(char) * code_size);
	subbuf[0] = '\0';

	strcpy(subbuf_r, buf);
	len = len_;

	do
	{
		printf("... ");
		gets(subbuf);

		len__ = strlen(subbuf);
		len += (len_+1);

		/* add new line char */
		subbuf[len__] = '\n';
		subbuf[len__+1] = '\0';

		if (len > code_size)
		{
			subbuf_r = realloc(subbuf_r, code_size + 80);
			code_size += 80;
		}
      
		strcat(subbuf_r, subbuf);
      
	} while(subbuf[0] != '\n');

	return subbuf_r;
}

char *interpreter_launch_code = "_INTERPRETER_ = True\n";

/* prelude code */
char *prelude_code =
	"def credits():\n"
	"  print(\"Thanks to Tinypy for the base interpreter, BSDs and Apple for the library, \")\n"
	"  print(\"and stos project for the build system.\")\n"
	"  print(\"All the remaining code was made by Fabien Siron (me).\")\n"
	"  print(\"If you want to contact me, please send me an email: fabien.siron@epita.fr\")\n"
	"\n"
	"def help():\n"
	"  print(\"You probably looking for that because some python's feature doesn't work.\")\n"
	"  print(\"It's totally normal as tinypy is just an experimental system for the moment.\")\n"
	"  print(\"So, be patient, or if you want, send me an email at fabien.siron@epita.fr\")\n"
	"\n"
	"def contribute():\n"
	"  print(\"If you want to contribute, it's fairly simple: you have to send patch with\")\n"
	"  print(\"Github pull request feature at https://github.com/Saruta/pyr0.\")\n"
	"\n"
	"def why():\n"
	"  print(\"Why pyr0?\")\n"
	"  print(\"> why not :-)\")\n"
	"\n";

static
void print_header(char *name, char *version)
{
	/* XXX: add author in cmdline or config.h */
	printf(
	"%s %s (April 2016)\nType \"help\", \"credits\", \"contribute\" or "
	"\"why\" for more information.\n"
	"Author: Fabien Siron <fabien.siron@epita.fr>\n",
	name, version);
}

void start_interpreter_loop(struct runtime_opt *opt)
{
	char _buf[81];
	char *buf = _buf;
	tp_vm *tp;
	tp_obj globals;
	char *argv[] = {"tinypy", "_INTERPRETER_"};
	unsigned char sub_i;
	unsigned len;

	/* sadly, the init of the interpreter can be long */
	printf("Loading runtime interpreter...\n");

	/* set prelude mode */
	code_p = interpreter_launch_code;
	code_l = strlen(interpreter_launch_code);

	/* run launch */
	tp = tp_init(2, argv);

	tp_ez_call(tp,"py2bc", "tinypy", tp_None);

	/* init modules */
	init_modules(tp);

	/* run prelude */

	globals = tp_dict(tp);

	tp_eval(tp, prelude_code, globals);

	print_header(opt->os_name, opt->os_version);

	/* run main loop */

	while (1)
	{
		setjmp(except_jmp);
      
		if (sub_i)
		{
			free(buf);
			sub_i = 0;
			buf = _buf;
		}
      
		printf(">>> ");
      
		buf[0] = '\0';

		gets(buf);
		len = strlen(buf);
      
		if (len == 0)
			continue;

		/* XXX: handle trailing spaces after semi-colon */

		if (buf[len - 1] == ':')
		{
			buf[len] = '\n';
			buf[len+1] = '\0';
			buf = sub_interpreter(buf, len+1);
			sub_i = 1;
		}

		if (strcmp(buf, "quit()") == 0)
			goto release;

		tp_eval(tp, buf, globals);
	}

	/* release all */
release:
	tp_deinit(tp);
}

void start_file_loader(void *p, long len, char *name)
{
	printf ("load %s!\n", name);
  
	code_p = p;
	code_l = len;

	char *argv[] = {"tinypy", name};

	tp_vm *tp = tp_init(2, argv);
	tp_ez_call(tp,"py2bc", "tinypy", tp_None);

	tp_deinit(tp);
}

#include <asm/system.h>

void start_runtime(void *p, long len, char *name, struct runtime_opt *opts)
{
	if (p == NULL && len == 0 && name == NULL)
		start_interpreter_loop(opts);
	else
	{
		if (p && len == 0)
			panic("Panic: file size is zero, abort\n");
		else if (p && len && name == NULL)
			panic("Panic: no file name is given, abort\n");
		else
			start_file_loader(p, len, name);
	}
	printf("Exit Tinypy\n");
	printf("Exit Pyr0\n");

	hlt();

	/* Not reached */
}
