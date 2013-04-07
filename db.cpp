/*
 * Filename: db.c
 * Author: Kraks <kiss.kraks@gmail.com>
 */

#include <iostream>
#include <string>
#include <db_cxx.h>

void packString(t_word_srting &s, t_word_c_str *c)
{
	std::strcpy(c->original, s.original.c_str());
	std::strcpy(c->phonetic, s.phonetic.c_str());
	std::strcpy(c->translation, s.translation.c_str());
}

void showWordbook()
{
}

int isInDB(word_t w, char *db_name)
{
}

void queryInDB(word_t *w, char *db_name)
{
	Db db(NULL, 0);
	u_int32_t oFlags = DB_CREATE;
	Dbt key, data;
	key.set_data(w->original);
	key.set_size(w->original.size());
	data.set_data(w);
	//data.set_ulen();
	data.set_flags(DB_DBT_USERMEM); // XXX
	int ret;

	try {
		ret = db.open(NULL, db_name, NULL, DB_BTREE, oFlags, 0);
		printDBError(ret);
		ret = db.get(NULL, &key, &data, 0);
	} catch(DbException &e) {
		cout << "DbException" << endl;
	} catch(std::exception &e) {
		cout << "std::exception" << endl;
	}
	db.close(0);
}

void saveToDB(word_t w, char *db_name)
{
	Db db(NULL, 0);
	u_int32_t oFlags = DB_CREATE;
	Dbt key(&w.original, w.original.size());
	Dbt data(&w, sizeof(w));
	int ret;

	try {
		ret = db.open(NULL, db_name, NULL, DB_BTREE, oFlags, 0);
		printDBError(ret);
		ret = db.put(NULL, &key, &data, DB_OVERWRITE_DUP);
		printDBError(ret);
	} catch(DbException &e) {
		cout << "DbException" << endl;
	} catch(std::exception &e) {
		cout << "std::exception" << endl;
	}
	db.close(0);
}

void printDBError(int ret)
{
	if(ret != 0)
		printf("ERROR: %s\n",db_strerror(ret));
}

