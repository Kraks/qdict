/*
 * Filename: db.c
 * Author: Kraks <kiss.kraks@gmail.com>
 */

#include <iostream>
#include <string>
#include <cstring>
#include <db_cxx.h>

void packString(t_word_string &s, t_word_c_str *c)
{
	std::strcpy(c->original, s.original.c_str());
	std::strcpy(c->phonetic, s.phonetic.c_str());
	std::strcpy(c->translation, s.translation.c_str());
}

void showWordbook()
{
}

bool isInDB(string w, char *db_name)
{
	Db db(NULL, 0);
	u_int32_t oFlags = DB_CREATE;
	Dbt key;
	int ret;

	key.set_data(&w);
	key.set_size(w.size());

	try {
		ret = db.open(NULL, db_name, NULL, DB_BTREE, oFlags, 0);
		ret = db.exists(NULL, &key, 0);
	} catch(DbException &e) {
		cout << "DbException" << endl;
	} catch(std::exception &e) {
		cout << "std::exception" << endl;
	}
	db.close(0);
	if (ret == DB_NOTFOUND)
		return false;
	return true;
}

t_word_c_str queryInDB(string q, char *db_name)
{
	Db db(NULL, 0);
	u_int32_t oFlags = DB_CREATE;
	Dbt key, data;
	int ret;
	t_word_c_str t;

	key.set_data(&q);
	key.set_size(q.size());

	data.set_data(&t);
	data.set_ulen(sizeof(t));
	data.set_flags(DB_DBT_USERMEM); 

	try {
		ret = db.open(NULL, db_name, NULL, DB_BTREE, oFlags, 0);
		ret = db.get(NULL, &key, &data, 0);
	} catch(DbException &e) {
		cout << "DbException" << endl;
	} catch(std::exception &e) {
		cout << "std::exception" << endl;
	}
	db.close(0);
	return (t_word_c_str) t;
}

void saveToDB(t_word_string w, char *db_name)
{
	Db db(NULL, 0);
	u_int32_t oFlags = DB_CREATE;
	t_word_c_str t;
	int ret;

	packString(w, &t);
	Dbt key(&w.original, w.original.size());
	Dbt data(&t, sizeof(t));

	try {
		ret = db.open(NULL, db_name, NULL, DB_BTREE, oFlags, 0);
		ret = db.put(NULL, &key, &data, DB_OVERWRITE_DUP);
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
		printf("ERROR: %s\n",DB::err(ret));
}

