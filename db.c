/*
 * Filename: db.c
 * Author: Kraks <kiss.kraks@gmail.com>
 */

#include "global.h"
#include "db.h"
#include "utils.h"

void show_wordbook()
{
	DB *dbp;         
	DBC *cur;  
	DBT key, data;
	u_int32_t flags;  
	int ret;
	
	word_t *w = (word_t *) malloc(sizeof(word_t));
	char *word_str = (char *) malloc(sizeof(char) * MAX_WORD_LENGTH);
	
	ret = db_create(&dbp, NULL, 0);
	print_db_error(ret);
	flags = DB_CREATE;
	ret = dbp->open(dbp, NULL, "wordbook.db", NULL, DB_BTREE, flags, 0); 
	print_db_error(ret);
	ret = dbp->cursor(dbp, NULL, &cur, 0);
	print_db_error(ret);
	
	init_DBT(&key, &data);
	
	while((ret = cur->get(cur, &key, &data, DB_NEXT)) == 0)
	{
		w = data.data;
		print_result(w);
		printf("\n");
	}
	
	cur->close(cur);
	dbp->close(dbp, 0);
}

int is_in_db(char *word_str, char *db_name)
{
	DB *dbp;           
	DBT key, data;
	u_int32_t flags;  
	int ret;
	
	ret = db_create(&dbp, NULL, 0);
	print_db_error(ret);
	flags = DB_CREATE;
	ret = dbp->open(dbp, NULL, db_name, NULL, DB_BTREE, flags, 0); 
	print_db_error(ret);
	init_DBT(&key, &data);
	
	key.data = word_str;
	key.size = strlen(word_str)+1;

	ret = dbp->exists(dbp, NULL, &key, 0);
	
	printf("%d\n", ret);
	if(dbp != NULL)
    	dbp->close(dbp, 0); 

	if (ret == DB_NOTFOUND) {
		printf("DEBUG: %s is NOT in %s\n", word_str, db_name);
		return FALSE;
	}
	else {
		printf("DEBUG: %s is in %s\n", word_str, db_name);
		return TRUE;
	}
}

void query_in_db(char *word_str, word_t *w, char *db_name)
{
	DB *dbp;           
	DBT key, data;
	u_int32_t flags;  
	int ret;
	
	ret = db_create(&dbp, NULL, 0);
	print_db_error(ret);
	flags = DB_CREATE;
	ret = dbp->open(dbp, NULL, db_name, NULL, DB_BTREE, flags, 0); 
	print_db_error(ret);
	init_DBT(&key, &data);
	
	key.size = strlen(word_str)+1;
	key.data = word_str;
	key.flags = DB_DBT_USERMEM;
	
	data.data = w;
	data.ulen = sizeof(word_t); 
	data.flags = DB_DBT_USERMEM;
	
	dbp->get(dbp, NULL, &key, &data, 0);
	
	if(dbp != NULL)
    	dbp->close(dbp, 0);
    
}

void save_to_db(word_t *w, char *db_name)
{
	DB *dbp;           
	DBT key, data;
	u_int32_t flags;  
	int ret;
	
	ret = db_create(&dbp, NULL, 0);
	print_db_error(ret);
	flags = DB_CREATE;
	ret = dbp->open(dbp, NULL, db_name, NULL, DB_BTREE, flags, 0); 
	print_db_error(ret);
	init_DBT(&key, &data);
	
	key.data = w->original;
	key.size = strlen(w->original)+1;
 
	data.data = w;
	data.size = sizeof(word_t);
#ifdef DEBUG
	printf("DEBUG save_to_db() %s will save to %s\n", (char *) data.data, db_name);
#endif
	
	ret = dbp->put(dbp, NULL, &key, &data, DB_OVERWRITE_DUP); 
	print_db_error(ret);
	
	if(dbp != NULL)
    	dbp->close(dbp, 0);
}

void print_db_error(int ret)
{
	if(ret != 0)
		printf("ERROR: %s\n",db_strerror(ret));
}

void init_DBT(DBT * key, DBT * data)
{
	memset(key, 0, sizeof(DBT));
	memset(data, 0, sizeof(DBT));
}
