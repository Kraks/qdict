/*
 * Filename: db.h
 * Author: Kraks <kiss.kraks@gmail.com>
 */

void showWordbook();
int isInDB(word_t w, char *db_name);
void queryInDB(word_t *w, char *db_name);
void saveToDB(word_t w, char *db_name);
void printErrorDB(int ret);
void initDBT(DBT * key, DBT * data);
