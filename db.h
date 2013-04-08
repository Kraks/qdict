/*
 * Filename: db.h
 * Author: Kraks <kiss.kraks@gmail.com>
 */

void packtoCstr(t_word_string &s, t_word_c_str *c);
void unpacktoString(t_word_string &s, t_word_c_str *c);
void showWordbook();
bool isInDB(string w, char *db_name);
t_word_c_str queryInDB(string q, char *db_name);
void saveToDB(t_word_string w, char *db_name);
void printDBError(int ret);
