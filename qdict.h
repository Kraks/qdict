#define SAVE_TO_WORDBOOK 1
#define NOT_SAVE_TO_WORDBOOK 0

#define DB_WORDBOOK "wordbook.db"
#define DB_CACHE "dict.db"

void print_result(word_t *w);

void interactive();
void print_help();
void query(char *word_str, int save_to_wordbook);
void prase_args(int argc, char **argv);
