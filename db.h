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
	void getByCount(const string filter);
	void getByCount(const int count);
private:
	Db *db;
	void unpacktoString(t_word_string &s, t_word_c_str *c);
	void packtoCstr(t_word_string &s, t_word_c_str *c);
};

#if 0
void showWordbook();
#endif
