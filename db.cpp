/******^-^
 * Filename: db.cpp
 * Author: Kraks <kiss.kraks@gmail.com>
 *
 ***/

#include "global.h"
#include "qdict.h"
#include "db.h"
#include "utils.h"


#if 0
/*
void printDBError(int ret)
{
	if(ret != 0)
		printf("ERROR: %s\n",DB::err(ret));
}
*/
#endif

#define NEW_CPP_DB_CLASS
#ifdef NEW_CPP_DB_CLASS

myDB::myDB(const char *db_name)
{
	db = new Db(NULL, 0);
	u_int32_t o_flags = DB_CREATE;
	db->open(NULL, db_name, NULL, DB_BTREE, o_flags, 0);
}

myDB::~myDB()
{
	db->close(0);
}

bool myDB::exist(string w) const
{
	int ret;
	Dbt key;
	char *ckey = new char[w.length()+1];

	strcpy(ckey, w.c_str());
	key.set_data(ckey);
	key.set_size(w.length()+1);

#ifdef DEBUG
	cout << "DEBUG: exist key " << w << " " << w.length()+1 << endl;
#endif

	try {
		ret = db->exists(NULL, &key, 0);
	} catch(DbException &e) {
		cout << "DbException" << endl;
	} catch(std::exception &e) {
		cout << "std::exception" << endl;
	}
#ifdef DEBUG
	cout << "DEBUG: exist ret " << ret << endl;
#endif
	if (ret == DB_NOTFOUND)
		return false;
	return true;
}

t_word_string myDB::operator()(string key)
{
	return __get(key);
}


t_word_string myDB::get(string key)
{
	return __get(key);
}

t_word_string myDB::__get(string w)
{
	t_word_string res;
	t_word_c_str c;
	char *ckey = new char[w.length()+1];
	strcpy(ckey, w.c_str());
	Dbt key, data;
	key.set_data(ckey);
	key.set_size(w.length()+1);

	data.set_data(&c);
	data.set_ulen(sizeof(c));
	data.set_flags(DB_DBT_USERMEM); 
	try {
		db->get(NULL, &key, &data, 0);
	} catch(DbException &e) {
		cout << "DbException" << endl;
	} catch(std::exception &e) {
		cout << "std::exception" << endl;
	}
	unpacktoString(res, &c);
	return res;
}

void myDB::put(t_word_string w)
{
	t_word_c_str t;
	char *ckey = new char[w.original.length()+1];
	
	stringTolower(w.original);
	strcpy(ckey, w.original.c_str());
	packtoCstr(w, &t);
	
	Dbt key(ckey, w.original.length()+1);
	Dbt data(&t, sizeof(t));

#ifdef DEBUG
	cout << "DEBUG: put ";
	cout << t.original << " " << t.phonetic << " " << t.translation << endl;
#endif

	try {
		db->put(NULL, &key, &data, DB_OVERWRITE_DUP);
	} catch(DbException &e) {
		cout << "DbException" << endl;
	} catch(std::exception &e) {
		cout << "std::exception" << endl;
	}
}

void myDB::packtoCstr(t_word_string &s, t_word_c_str *c)
{
	strcpy(c->original, s.original.c_str());
	strcpy(c->phonetic, s.phonetic.c_str());
	strcpy(c->translation, s.translation.c_str());
}

void myDB::unpacktoString(t_word_string &s, t_word_c_str *c)
{
	s.original.assign(c->original);
	s.phonetic.assign(c->phonetic);
	s.translation.assign(c->translation);
}

void myDB::getByCount(const int count)
{
	
}

void myDB::getByFilter(const string filter)
{
	if ("all" == filter) {
		Dbc *cur;
		Dbt key, data;
		int ret;
		t_word_c_str t;
		t_word_string w;

		try {
			ret = db->cursor(NULL, &cur, 0);
			while ((ret = cur->get(&key, &data, DB_NEXT)) == 0) {
				t = *(t_word_c_str *) data.get_data();
				unpacktoString(w, &t);
				printWord(w);
				cout << endl;
			}
		} catch(DbException &e) {
			cout << "DbException" << endl;
		} catch(std::exception &e) {
			cout << "std::exception" << endl;
		}
		if (cur != NULL)
			cur->close();
	}
}

size_t myDB::count()
{
	Dbc *cur;
	Dbt key, data;
	int ret;
	size_t count;

	try {
		ret = db->cursor(NULL, &cur, 0);
		while ((ret = cur->get(&key, &data, DB_NEXT)) == 0) {
			count++;
		}
	} catch(DbException &e) {
		cout << "DbException" << endl;
	} catch(std::exception &e) {
		cout << "std::exception" << endl;
	}
	if (cur != NULL)
		cur->close();
	return count;
}

#ifdef DB_TEST
int main(int argc, char **argv)
{
	string word("good");
	t_word_string t;
	myDB db("dict.db");
	if (db.exist(word))
		t = db.get(word);
	cout << t.original << t.phonetic << t.translation << endl;
	return 0;
}
#endif

#endif
