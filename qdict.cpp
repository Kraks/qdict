/******^-^
 * Filename: qdict.cpp
 * Author: Kraks <kiss.kraks@gmail.com>
 *
 ***/

#include "global.h"

#include "qdict.h"
#include "db.h"
#include "utils.h"
#include "network.h"

void praseArgs(vector<string> v)
{
	string buf;
	string space(" ");
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
		buf = join(v, v.begin(), v.end(), space);
		flag = NOT_SAVE_TO_WORDBOOK;
	}
	else if (size > 2 && v[v.size()-1] == "+") {
		buf = join(v, v.begin(), v.end()-1, space);
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
	stringTolower(word);
	t_word_string w;
	initWordType(w, word, "", "");
	myDB cache(DB_CACHE);
	myDB wordbook(DB_WORDBOOK);

#ifdef DEBUG
		cout << "DEBUG: query in " << DB_CACHE << endl;
#endif

	if (cache.exist(w.original)) {
		//w = cache.get(w.original);
		w = cache(w.original);
	}
	else {
		w = queryFromNetwork(word, w);
		if (!checkNull(w)) {
#ifdef DEBUG
			cout << "DEBUG: query result not null" << endl;
#endif
			cache.put(w);
			printWord(w);
		} else {
#ifdef DEBUG
			cout << "DEBUG: query result null" << endl;
#endif
		}
	}

	if (saveToWordbook)
		wordbook.put(w);
}

void queryRobot()
{
	
}

void showDict(string db_name)
{
	size_t count;
	if (db_name == DB_CACHE) {
		myDB cache(DB_CACHE);
		cache.getByFilter("all");
		count = cache.count();
		cout << "Total " << count << " words" << endl;
	}
	else if (db_name == DB_WORDBOOK) {
		myDB wordbook(DB_WORDBOOK);
		wordbook.getByFilter("all");
		count = wordbook.count();
		cout << "Total " << count << " words" << endl;
	}
}

void showWordBook()
{
	showDict(DB_WORDBOOK);
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
	printf(" -d, --dict           show all the cache word\n");
	printf(" -i, --interactive    enter interactive mode to query\n");
	printf(" -h, --help           print this help information\n");
}

void printWord(t_word_string w)
{
#ifdef DEBUG
	cout << "DEBUG printWord " << endl;
#endif
	if (w.original != "")
		cout << w.original << endl;
	if (w.phonetic != "")
		cout << w.phonetic << endl;
	if (w.translation != "")
		cout << w.translation << endl;
}

bool checkNull(t_word_string w)
{
	if (w.original == "")
		return true;
	if (w.translation == "")
		return true;
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
		showWordBook();
	}
	else if (!strcmp(argv[1], "-d") || !strcmp(argv[1], "--dict")) {
		showDict(DB_CACHE);
	}
	else if (!strcmp(argv[1], "-i") || !strcmp(argv[1], "--interactive")) {
		interactive();
	}
	else if ((argv[1][0] == '-') || (argv[1][0] == '-' && argv[1][1] == '-')) {
		printHelp(argv[0]);
	}
	else {
		vector<string> v(argv+1, argv+argc);
#ifdef DEBUG
		dumpVector(v);
#endif
		praseArgs(v);
	}
	return 0;
}


