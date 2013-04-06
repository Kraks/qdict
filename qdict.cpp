/*
 * Filename: qdict.cpp
 * Author: Kraks <kiss.kraks@gmail.com>
 */

#define DEBUG

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void praseArgs(vector<string> v)
{
	string buf;
	int flag;
	int size = v.size();
	if (size == 1) {
		buf.asign(v[0]);
		flag = NOT_SAVE_TO_WORDBOOK;
	}
	else if (size == 2 && !v[1].compare("+")) {
		buf.assign(v[0]);
		flag = SAVE_TO_WORDBOOK;
	}
	else if (size >= 2 && v[v.size()-1].compare("+")) {	
		buf = kstrJoinWithStr(argc, argv, WHITESPACE); // XXX
		flag = NOT_SAVE_TO_WORDBOOK;
	}
	else if (size > 2 && !v[v.size()-1].compare("+")) {
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
	string buf;
	while (1) {
		cout << ">> ";
		getline(cin, buf);
		if (buf.empty()) {
			cout << ">> ";
			continue;
		}
		if (!buf.compare("exit")) {
			cout << "Now exit" << endl;
			exit(0);
		}
		// split
		// praseArgs
		buf.erase();
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
		vector<string> v(argv+1, argv+argc);
		praseArgs(v);
	}
	return 0;
}


