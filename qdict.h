/*
 * Filename: qdict.h
 * Author: Kraks <kiss.kraks@gmail.com>
 */

#define SAVE_TO_WORDBOOK 1
#define NOT_SAVE_TO_WORDBOOK 0

#define DB_WORDBOOK "wordbook.db"
#define DB_CACHE "dict.db"


void praseArgs(int argc, char **argv);
void query(kstr word, int saveToWordbook);
void interactive(void);
void printHelp(const char *name);
void printWordType(word_t w)l
void initWordType(word_t *w, const char *o, const char *p, const char *t);
void freeWordType(word_t *w);
