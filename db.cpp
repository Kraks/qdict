/*
 * Filename: db.c
 * Author: Kraks <kiss.kraks@gmail.com>
 */

#include <iostream>
#include <string>
#include <db_cxx.h>

void showWordbook()
{
	DB *dbp;         
	DBC *cur;  
	DBT key, data;
	u_int32_t flags;  
	int ret;
	
	word_t *w = (word_t *) malloc(sizeof(word_t));
	char *word_str = (char *) malloc(sizeof(char) * MAX_WORD_LENGTH);
	
	ret = db_create(&dbp, NULL, 0);
	printDBError(ret);
	flags = DB_CREATE;
	ret = dbp->open(dbp, NULL, "wordbook.db", NULL, DB_BTREE, flags, 0); 
	printDBError(ret);
	ret = dbp->cursor(dbp, NULL, &cur, 0);
	printDBError(ret);
	
	initDBT(&key, &data);
	
	while((ret = cur->get(cur, &key, &data, DB_NEXT)) == 0)
	{
		w = data.data;
		print_result(w);
		printf("\n");
	}
	
	cur->close(cur);
	dbp->close(dbp, 0);
}

int isInDB(word_t w, char *db_name)
{
	DB *dbp;           
	DBT key, data;
	u_int32_t flags;  
	int ret;
	
	ret = db_create(&dbp, NULL, 0);
	printDBError(ret);
	flags = DB_CREATE;
	ret = dbp->open(dbp, NULL, db_name, NULL, DB_BTREE, flags, 0); 
	printDBError(ret);
	initDBT(&key, &data);
	
	kstr oriWord = w.original;
	key.data = oriWord;
	key.size = kstrlen(oriWord);

	ret = dbp->exists(dbp, NULL, &key, 0);
	
	printf("%d\n", ret);
	if(dbp != NULL)
    	dbp->close(dbp, 0); 

	if (ret == DB_NOTFOUND) {
		return FALSE;
	}
	else {
		return TRUE;
	}
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
	db.close();
	// old c version
	DB *dbp;           
	DBT key, data;
	u_int32_t flags;  
	int ret;
	
	ret = db_create(&dbp, NULL, 0);
	printDBError(ret);
	flags = DB_CREATE;
	ret = dbp->open(dbp, NULL, db_name, NULL, DB_BTREE, flags, 0); 
	printDBError(ret);
	initDBT(&key, &data);
	
	kstr oriWord = w->original;
	key.data = oriWord;
	key.size = kstrlen(oriWord);
	key.flags = DB_DBT_USERMEM;

	data.data = w;
	data.ulen = sizeof(word_t); //XXX
	data.flags = DB_DBT_USERMEM;
	
	dbp->get(dbp, NULL, &key, &data, 0);
	
	if(dbp != NULL)
    	dbp->close(dbp, 0);
    
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
	db.close();
}

void printDBError(int ret)
{
	if(ret != 0)
		printf("ERROR: %s\n",db_strerror(ret));
}

void initDBT(DBT * key, DBT * data)
{
	memset(key, 0, sizeof(DBT));
	memset(data, 0, sizeof(DBT));
}
