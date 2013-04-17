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
	void put(t_word_string w);
	void getByFilter(const string filter);
	void getByCount(const int count);
	void del(string w);
	size_t count();
	t_word_string operator()(string w);
	t_word_string get(string w);
private:
	Db *db;
	t_word_string __get(string w);
	void unpacktoString(t_word_string &s, t_word_c_str *c);
	void packtoCstr(t_word_string &s, t_word_c_str *c);
};

#if 0
void showWordbook();
#endif
