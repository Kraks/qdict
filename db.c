/*
 * Filename: db.c
 * Author: Kraks <kiss.kraks@gmail.com>
 */

#include "global.h"
#include "db.h"
#include "utils.h"
#include "kstr.h"

void showWordbook()
{
	DB *dbp;
	DBC *cur;  
	DBT key, data;
	u_int32_t flags;  
	int ret;
	// ?
	char *word_str;
	word_t w = initWordType(*w, NULL, NULL, NULL);
	
	ret = db_create(&dbp, NULL, 0);
	printErrorDB(ret);
	flags = DB_CREATE;
	ret = dbp->open(dbp, NULL, "wordbook.db", NULL, DB_BTREE, flags, 0); 
	printErrorDB(ret);
	ret = dbp->cursor(dbp, NULL, &cur, 0);
	printErrorDB(ret);
	
	initDBT(&key, &data);
	
	while((ret = cur->get(cur, &key, &data, DB_NEXT)) == 0)
	{
		w = data.data;
		printWordType(w);
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
	printErrorDB(ret);
	flags = DB_CREATE;
	ret = dbp->open(dbp, NULL, db_name, NULL, DB_BTREE, flags, 0); 
	printErrorDB(ret);
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
	DB *dbp;           
	DBT key, data;
	u_int32_t flags;  
	int ret;
	
	ret = db_create(&dbp, NULL, 0);
	printErrorDB(ret);
	flags = DB_CREATE;
	ret = dbp->open(dbp, NULL, db_name, NULL, DB_BTREE, flags, 0); 
	printErrorDB(ret);
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
	DB *dbp;           
	DBT key, data;
	u_int32_t flags;  
	int ret;
	
	ret = db_create(&dbp, NULL, 0);
	printErrorDB(ret);
	flags = DB_CREATE;
	ret = dbp->open(dbp, NULL, db_name, NULL, DB_BTREE, flags, 0); 
	printErrorDB(ret);
	initDBT(&key, &data);
	
	kstr oriWord = w.original;
	key.data = oriWord;
	key.size = kstrlen(oriWord);
 
	data.data = w;
	data.size = kstrlen(w.original) + kstrlen(w.phonetic) + kstrlen(w.translation);
	
	ret = dbp->put(dbp, NULL, &key, &data, DB_OVERWRITE_DUP); 
	printErrorDB(ret);
	
	if(dbp != NULL)
    	dbp->close(dbp, 0);
}

void printErrorDB(int ret)
{
	if(ret != 0)
		printf("ERROR: %s\n",db_strerror(ret));
}

void initDBT(DBT * key, DBT * data)
{
	memset(key, 0, sizeof(DBT));
	memset(data, 0, sizeof(DBT));
}
