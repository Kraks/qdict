/*
 * Filename: db.h
 * Author: Kraks <kiss.kraks@gmail.com>
 */

void showWordbook();
int isInDB(char *word_str, char *db_name);
void queryInDB(char *word_str, word_t *w, char *db_name);
void saveToDB(word_t *w, char *db_name);
void printErrorDB(int ret);
void initDBT(DBT * key, DBT * data);
