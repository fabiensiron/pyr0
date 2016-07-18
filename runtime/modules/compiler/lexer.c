#include <tinypy/tp.h>
#include <tinypy/dict.h>
#include <tinypy/string.h>

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DEBUG_TOKENS

enum tokentype {
	EMPTY = 0,
	/* KEYWORDS */
#define K_DEF "def"
	DEF = 1,
#define K_CLASS "class"
	CLASS,
#define K_YIELD "yield"
	YIELD,
#define K_RETURN "return"
	RETURN,
#define K_PASS "pass"
	PASS,
#define K_AND "and"
	AND,
#define K_OR "or"
	OR,
#define K_NOT "not"
	NOT,
#define K_IN "in"
	IN,
#define K_IMPORT "import"
	IMPORT,
#define K_IS "is"
	IS,
#define K_WHILE "while"
	WHILE,
#define K_BREAK "break"
	BREAK,
#define K_FOR "for"
	FOR,
#define K_CONTINUE "continue"
	CONTINUE,
#define K_IF "if"
	IF,
#define K_ELSE "else"
	ELSE,
#define K_ELIF "elif"
	ELIF,
#define K_TRY "try"
	TRY,
#define K_EXCEPT "except"
	EXCEPT,
#define K_RAISE "raise"
	RAISE,
#define K_TRUE "True"
	TRUE,
#define K_FALSE "False"
	FALSE,
#define K_NONE "None"
	NONE,
#define K_GLOBAL "global"
	GLOBAL,
#define K_DEL "del"
	DEL,
#define K_FROM "from"
	FROM,
	/* OPS */
	MINUS,
	PLUS,
	TIMES,
	POWER,
	DIVIDE,
	MODULO,
	PERCENT,
	LSHIFT,
	RSHIFT,
	SUBTO,
	ADDTO,
	TIMESTO,
	DIVIDETO,
	EQUAL,
	ISEQUAL,
	ISNOTEQUAL,
	ST,
	BT,
	ORTO,
	ANDTO,
	XORTO,
	SE,
	BE,
	LSQBRACKET,
	RSQBRACKET,
	LCURBRACKET,
	RCURBRACKET,
	LPAR,
	RPAR,
	DOT,
	COLON,
	COMMA,
	SEMICOLON,
	BITAND,
	BITOR,
	EXCL,
	XOR,
	/* MISC */
	NUMBER,
	STRING,
	NAME,
	TAB
};

struct token {
	enum tokentype type;
	char *val;
	/* add position */
};

struct {
	char *val;
	unsigned len;
} keywords[] = {
	[DEF] = {K_DEF, sizeof(K_DEF) - 1},
	[CLASS] = {K_CLASS, sizeof(K_CLASS) - 1},
	[YIELD] = {K_YIELD, sizeof(K_YIELD) - 1},
	[RETURN] = {K_RETURN, sizeof(K_RETURN) - 1},
	[PASS] = {K_PASS, sizeof(K_PASS) - 1},
	[AND] = {K_AND, sizeof(K_AND) - 1},
	[OR] = {K_OR, sizeof(K_OR) - 1},
	[NOT] = {K_NOT, sizeof(K_NOT) - 1},
	[IN] = {K_IN, sizeof(K_IN) - 1},
	[IMPORT] = {K_IMPORT, sizeof(K_IMPORT) - 1},
	[IS] = {K_IS, sizeof(K_IS) - 1},
	[WHILE] = {K_WHILE, sizeof(K_WHILE) - 1},
	[BREAK] = {K_BREAK, sizeof(K_BREAK) - 1},
	[FOR] = {K_FOR, sizeof(K_FOR) - 1},
	[CONTINUE] = {K_CONTINUE, sizeof(K_CONTINUE) - 1},
	[IF] = {K_IF, sizeof(K_IF) - 1},
	[ELSE] = {K_ELSE, sizeof(K_ELSE) - 1},
	[ELIF] = {K_ELIF, sizeof(K_ELIF) - 1},
	[TRY] = {K_TRY, sizeof(K_TRY) - 1},
	[EXCEPT] = {K_EXCEPT, sizeof(K_EXCEPT) - 1},
	[RAISE] = {K_RAISE, sizeof(K_RAISE) - 1},
	[TRUE] = {K_TRUE, sizeof(K_TRUE) - 1},
	[FALSE] = {K_FALSE, sizeof(K_FALSE) - 1},
	[NONE] = {K_NONE, sizeof(K_NONE) - 1},
	[GLOBAL] = {K_GLOBAL, sizeof(K_GLOBAL) - 1},
	[DEL] = {K_DEL, sizeof(K_DEL) - 1},
	[FROM] = {K_FROM, sizeof(K_FROM) - 1},
	{NULL, }
};

int getalphanum(const char *src)
{
	int i = 0;

	while(src[i] != '\0' && isalnum(src[i]))
		i++;

	return i;
}
#if 0
int do_xnumber(char *src, enum tokentype *type, unsigned int *num)
{
	unsigned long num = 0;
	int added = 0;
	int i = 0;

	while(isxdigit(src[i])) {
		if (isdigit(src[i]))
			added = src[i] - '0';
		switch (src[i]) {
		case 'a':
			added = 10;
			break;
		case 'b':
			added = 11;
			break;
		case 'c':
			added = 12;
			break;
		case 'd':
			added = 13;
			break;
		case 'e':
			added = 14;
			break;
		case 'f':
			added = 15;
			break;
		default:
			/* XXX bug */
		}
		*num = *num * 16 + added;
		i++
	}
	return i;
}
#endif
int do_number(const char *src, enum tokentype *type, unsigned int *num)
{
	*num = 0;
	int i = 0;

	while(src[i] != '\0' && isdigit(src[i])) {
		*num = *num * 10 + (src[i] - '0');
		i++;
	}

	return i;
}

int do_keyword(const char *src, int target_len, enum tokentype *type)
{
	int i, keyword_len;
	for (i = 0; keywords[i].val != NULL; i++)
	{
		keyword_len = keywords[i].len;
		if (target_len != keyword_len) continue;
		if (strncmp(keywords[i].val, src, target_len) == 0) {
			*type = i;
			return target_len;
		}
	}
	return 0;
}

int do_op(char op, enum tokentype *type)
{
	static enum tokentype ops[255] = {
		['-'] = MINUS,
		['+'] = PLUS,
		['*'] = TIMES,
		['/'] = DIVIDE,
		['%'] = MODULO,
		['='] = EQUAL,
		['<'] = ST,
		['>'] = BT,
		['['] = LSQBRACKET,
		[']'] = RSQBRACKET,
		['{'] = LCURBRACKET,
		['}'] = RCURBRACKET,
		['('] = LPAR,
		[')'] = RPAR,
		['.'] = DOT,
		[':'] = COLON,
		[';'] = SEMICOLON,
		[','] = COMMA,
		['&'] = BITAND,
		['|'] = BITOR,
		['!'] = EXCL,
		['^'] = XOR,
	};

	return (*type = ops[(unsigned)op]);
}

int do_doubleOp(const char op[], enum tokentype *type)
{
	enum tokentype type0, type1;
	if (!do_op(op[0], &type0) || !(do_op(op[1], &type1)))
		return 0;

	/* manage xxxTO case (e.g. "+=", "-=" ...) */
	if (type1 == EQUAL) {
		switch(type0) {
		case EQUAL:
			*type = ISEQUAL;
			return 1;
		case MINUS:
			*type = SUBTO;
			return 1;
		case PLUS:
			*type = ADDTO;
			return 1;
		default:
#ifdef DEBUG_TOKENS
			printf("<BAD>\n");
#endif
			/* XXX error */
			return 0;
		}
	}

	/* manage shifts */
	if (type0 == ST && type1 == ST) {
		*type = LSHIFT;
		return 1;
	}
	if (type0 == BT && type1 == BT) {
		*type = RSHIFT;
		return 1;
	}
	/* manage power */
	if (type0 == TIMES && type1 == TIMES) {
		*type = POWER;
		return 1;
	}

#ifdef	DEBUG_TOKENS
	printf("<BAD>\n");
#endif

	return 0;
}

int do_tokenize(const char *src, int len)
{
	enum tokentype type;
	int i = 0;
	int offset = 0;
	while (i < len)
	{
		if (src[i] == ' ') {
			i++;
		} else if (isalpha(src[i])) {
			int target_len;
			target_len = getalphanum(src + i);
			if ((offset = do_keyword(src+i, target_len, &type))) {
#ifdef DEBUG_TOKENS
				printf("<KEYWORD \"%s\", %d>\n", keywords[type].val, offset);
#endif
				i += offset;
			} else {
				char buf[target_len + 1];
				memcpy(buf, src+i, target_len);
				buf[target_len] = '\0';
#ifdef DEBUG_TOKENS
				printf("<NAME: \"%s\", %d>\n", buf, target_len);
#endif
				i += target_len;
			}
		} else if (ispunct(src[i])) {
			if ((len - i - 1) > 0 && ispunct(src[i+1]) &&
			    do_doubleOp(src + i, &type)) {
#ifdef DEBUG_TOKENS
				printf("<OP: \"%c%c\">\n", src[i], src[i+1]);
#endif
				i += 2;
			} else if (do_op(src[i], &type)) {
#ifdef DEBUG_TOKENS
				printf("<OP: \"%c\">\n", src[i]);
#endif
				i += 1;
			} else {
#ifdef DEBUG_TOKENS
				printf("<BAD>\n");
#endif
				return 0;
			}
		} else if (isdigit(src[i])) {
			/* XXX manage xdigits */
			unsigned int num;
			int r = do_number(src + i, &type, &num);
#ifdef DEBUG_TOKENS
			printf("<NUM: \"%u\">\n", num);
#endif
			if (!r) {
#ifdef DEBUG_TOKENS
				printf("Fail\n");
#endif
				return 0;
			}
			i += r;
		} else {
			return 0;
		}
	}
	return 1;
}

tp_obj compiler_tokenize(TP)
{
	tp_obj src = TP_STR();
	int len = TP_NUM();
	const char *code = src.string.val;

	printf("src code: \"%s\", len: %d\n", code, len);

	do_tokenize(code, len);

	return tp_None;
}
