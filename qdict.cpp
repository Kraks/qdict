/******^-^
 * Filename: qdict.cpp
 * Author: Kraks <kiss.kraks@gmail.com>
 *
 ***/

#define DEBUG

#include "global.h"

#include "qdict.h"
#include "db.h"
#include "utils.h"
#include "network.h"

void praseArgs(vector<string> v)
{
	string buf;
	int flag;
	vector<string>::size_type size = v.size();

	if (size == 1) {
		buf.assign(v[0]);
		flag = NOT_SAVE_TO_WORDBOOK;
	}
	else if (size == 2 && v[1] == "+") {
		buf.assign(v[0]);
		flag = SAVE_TO_WORDBOOK;
	}
	else if (size >= 2 && v[v.size()-1] != "+") {
		buf = join(v, v.begin(), v.end());
		flag = NOT_SAVE_TO_WORDBOOK;
	}
	else if (size > 2 && v[v.size()-1] == "+") {
		buf = join(v, v.begin(), v.end()-1);
		flag = SAVE_TO_WORDBOOK;
	}
	else {
		printf("--^_^--\n");
		exit(0);
	}
#ifdef DEBUG
	cout << "DEBUG: praseArgs " << buf << endl;
#endif
	query(buf, flag);
}

void query(string word, int saveToWordbook)
{
	t_word_string w;
	initWordType(w, word, "", "");
	
#ifdef DEBUG
		cout << "DEBUG: query in " << DB_CACHE << endl;
#endif

	if (isInDB(w.original, DB_CACHE)) {
		w = queryInDB(w.original, DB_CACHE);
	}
	else {
		w = queryFromNetwork(word, w);
		saveToDB(w, DB_CACHE);
	}

	if (saveToWordbook)
		saveToDB(w, DB_WORDBOOK);

	printWord(w);
}

void interactive(void)
{
	string buf;
	vector<string> v;
	while (1) {
		cout << ">> ";
		getline(cin, buf);
		if (buf.empty()) {
			continue;
		}
		if (!buf.compare("exit")) {
			cout << "Now exit" << endl;
			exit(0);
		}
		//trim(buf);
		if (whitespaceCount(buf) >= 1) {
			v = split(buf, ' ', 0);
			praseArgs(v);
		}
		else {
			query(buf, NOT_SAVE_TO_WORDBOOK);
		}
		buf.erase();
	}
	exit(0);
}

void printHelp(const string program_name)
{
	printf(" usage: %s [word] [+]\n", program_name.c_str());
	printf(" the last [+] optional symbol means add the word to wordbook.\n");
	printf(" other optional:\n");
	printf(" -w, --wordbook       show the wordbook\n");
	printf(" -i, --interactive    enter interactive mode to query\n");
	printf(" -h, --help           print this help information\n");
}

void printWord(t_word_string w)
{
	cout << w.original << endl;
	cout << w.phonetic << endl;
	cout << w.translation << endl;
}

void initWordType(t_word_string &w, string o, string p, string t)
{
	w.original = o;
	w.phonetic = p;
	w.translation = t;
}

int main(int argc, char **argv)
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
#ifdef DEBUG
		for (vector<string>::iterator it = v.begin(); it != v.end(); it++)
			cout << *it << endl;
#endif
		praseArgs(v);
	}
	return 0;
}


