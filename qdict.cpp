/*
 * Filename: qdict.cpp
 * Author: Kraks <kiss.kraks@gmail.com>
 */

#define DEBUG

#include <iostream>
#include <string>

using namespace std;

void praseArgs(int argc, char **argv)
{
	string buf;
	int flag;

#ifdef DEBUG
	int i;
	for (i = 0; i < argc; i++)
		printf("DEBUG: prase_args(), argv[%d], %s\n", i, argv[i]);
#endif

	if (argc == 1) {
		buf.asign(argv[0]);
		flag = NOT_SAVE_TO_WORDBOOK;
	}
	else if (argc == 2 && !strcmp(argv[1], "+")) {
		buf.assign(argv[0]);
		flag = SAVE_TO_WORDBOOK;
	}
	else if (argc >= 2 && strcmp(argv[argc-1], "+")) {	
		buf = kstrJoinWithStr(argc, argv, WHITESPACE); // XXX
		flag = NOT_SAVE_TO_WORDBOOK;
	}
	else if (argc > 2 && !strcmp(argv[argc-1], "+")) {
		buf = kstrJoinWithStr(argc-1, argv, WHITESPACE); // XXX
		flag = SAVE_TO_WORDBOOK;
	}
	else {
		printf("--^_^--\n");
		exit(0);
	}
	query(buf, flag);
}

void query(string word, int saveToWordbook)
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

	// XXX
	string buf;
	string argv[];
	while (cin >> buf) {
		if (buf.empty())
			continue;
		if (buf.compare("exit"))
			exit(0);
		argv = split(buf, &argc); // LIST
		prase_args(argc, argv);
		cout << ">>";
		buf.clear();
	}
	exit(0);
}

void printHelp(const string programm_name)
{
	printf(" usage: %s [word] [+]\n", program_name);
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

void initWordType(word_t &w, string o, string p, string t)
{
	w.original = o;
	w.phonetic = p;
	w.translation = t;
}

// May not need
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


