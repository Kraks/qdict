/*
 * Filename: db.h
 * Author: Kraks <kiss.kraks@gmail.com>
 */

void show_wordbook();
int is_in_db(char *word_str, char *db_name);
void query_in_db(char *word_str, word_t *w, char *db_name);
void save_to_db(word_t *w, char *db_name);
void print_db_error(int ret);
void init_DBT(DBT * key, DBT * data);
