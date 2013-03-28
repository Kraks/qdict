/*
 * Filename: qdict.c
 * Author: Kraks <kiss.kraks@gmail.com>
 */

#define DEBUG

#include <stdio.h>
#include "kstr.h"
#include "global.h"


void praseArgs(int argc, char **argv)
{
	kstr buf = kstrNewEmpty();
#ifdef DEBUG
	int i;
	for (i = 0; i < argc; i++)
		printf("DEBUG: prase_args(), argv[%d], %s\n", i, argv[i]);
#endif
	if (argc == 1) {
		query(argv[0], NOT_SAVE_TO_WORDBOOK);
	}
	else if (argc == 2 && !strcmp(argv[1], "+")) {
		query(argv[0], SAVE_TO_WORDBOOK);
	}
	else if (argc >= 2 && strcmp(argv[argc-1], "+")) {
		buf = kstrJoinWithStr(argc, argv, WHITESPACE);
		//kstrTrim(buf);
		query(buf, NOT_SAVE_TO_WORDBOOK);
	}
	else if (argc > 2 && !strcmp(argv[argc-1], "+")) {
		buf = kstrJoinWithStr(argc-1, argv, WHITESPACE);
		//kstrTrim(buf);
		query(buf, SAVE_TO_WORDBOOK);
	}
	else {
		printf("--^_^--\n");
	}
}

void query(kstr word, int saveToWordbook)
{
	word_t w;
	initWordType(&w, word, NULL, NULL);
	
	if (isInDB(w, DB_CACHE)) {
		queryInDB(w, DB_CACHE);
	}
	else {
		queryFromNetwork(w);
		saveToDB(w, DB_CACHE);
	}

	if (saveToWrdbook)
		saveToDB(w, DB_WORDBOOK);

	printWordType(w);
	freeWordType(&w);
}

void interactive(void)
{
	char buf[QDICT_BUFFER_SZ];
	char **argv;
	int argc;
	printf(">> ");
	
	while (strcmp((buf = fgets(buf, QDICT_BUFFER_SZ, stdin)), "exit")) {
		argv = split(buf, &argc);
		prase_args(argc, argv);
		printf(">> ");
		memset(buf, 0, QDICT_BUFFER_SZ);
	}
	exit(0);
}

void printHelp(const char *name)
{
	printf(" usage: %s [word] [+]\n", name);
	printf(" the last [+] optional symbol means add the word to wordbook.\n");
	printf(" other optional:\n");
	printf(" -w, --wordbook       show the wordbook\n");
	printf(" -i, --interactive    enter interactive mode to query\n");
	printf(" -h, --help           print this help information\n");
}

void printWordType(word_t w)
{
	printKstr(w.original);
	printf("\n");
	printKstr(w.phonetic);
	printf("\n");
	printKstr(w.translation);
}

void initWordType(word_t *w, const char *o, const char *p, const char *t)
{
	w->original = kstrNew(o);
	w->phonetic = kstrNew(p);
	w->translation = kstrNew(t);
}

void freeWordType(word_t *w)
{
	kstrFree(w->original);
	kstrFree(w->phonetic);
	kstrFree(w->translation);
}

int main(int argc, char *argv)
{
	if (argc == 1 || 
		!strcmp(argv[1], "-h") ||
		!strcmp(argv[1], "--help")) {
		printHelp(argv[0]);
	}
	else if (!strcmp(argv[1], "-w") || !strcmp(argv[1], "--wordbook")) {
		showWordbook();
	}
	else if (!strcmp(argv[1], "-i") || !strcmp(argv[1], "--interactive")) {
		interactive();
	}
	else {
		praseArgs(argc-1, argv+1);
	}
	return 0;
}


