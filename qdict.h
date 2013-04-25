/******^-^
 * Filename: qdict.h
 * Author: Kraks <kiss.kraks@gmail.com>
 *
 ***/

#define SAVE_TO_WORDBOOK 1
#define NOT_SAVE_TO_WORDBOOK 0

#define DB_WORDBOOK "wordbook.db"
#define DB_CACHE "dict.db"

void praseArgs(vector<string> v);
void query(string word, int saveToWordbook);
void interactive(void);
void printHelp(const string programm_name);
void printWord(t_word_string w);
void initWordType(t_word_string &w, string o, string p, string t);
bool checkNull(t_word_string &w);
void delWord(const char *dbName, string w);
void showDict(const char *db_name);
