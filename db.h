/******^-^
 * Filename: db.h
 * Author: Kraks <kiss.kraks@gmail.com>
 *
 ***/

class myDB
{
public:
	myDB(const char *db_name);
	~myDB();
	bool exist(string w) const;
	t_word_string get(string w);
	void put(t_word_string w);
private:
	Db *db;
	void unpacktoString(t_word_string &s, t_word_c_str *c);
	void packtoCstr(t_word_string &s, t_word_c_str *c);
};

#if 0
void packtoCstr(t_word_string &s, t_word_c_str *c);
void unpacktoString(t_word_string &s, t_word_c_str *c);
void showWordbook();
bool isInDB(string w, const char *db_name);
t_word_string queryInDB(string q, const char *db_name);
void saveToDB(t_word_string w, const char *db_name);
void printDBError(int ret);
#endif
