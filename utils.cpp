/******^-^
 * Filename: utils.cpp
 * Author: Kraks <kiss.kraks@gmail.com>
 *
 ***/

#include "utils.h"
#include <locale>
#define CPP_VERSION
#ifdef CPP_VERSION

string join(vector<string> v, vector<string>::iterator begin, vector<string>::iterator end, string connector)
{
	string buf;
	for (vector<string>::iterator it = begin; it != end; it++) {
		buf += *it;
		buf += connector;
	}
	return buf;
}


vector<string> split(string s, char delim, int rep)
{
	vector<string> v;
	//if (!v.empty())
	//	v.clear();
	string work = s;
	string buf = "";
	int i = 0;
	while(i < work.length()) {
		if (work[i] != delim)
			buf+=work[i];
		else if (rep == 1) {
			v.push_back(buf);
			buf = "";
		}
		else if (buf.length() > 0) {
			v.push_back(buf);
			buf = "";
		}
		i++;
	}
	if (!buf.empty())
		v.push_back(buf);
	return v;
}

int whitespaceCount(string s)
{
	int count = 0;
	for (string::size_type ix = 0; ix != s.size(); ix++)
		if (s[ix] == ' ')
			count++;
	return count;
}

void trimPunctuation(string &s)
{
	size_t i = s.length()-1;
	cout << s[i] << endl;
	if (s[i] == ',' || s[i] == '.' || s[i] == '?' || s[i] == '!') {
		s = s.substr(0, i);
	}
}

void stringTolower(string &s)
{
	locale loc;
	for (size_t i = 0; i < s.length(); i++) {
		if (isupper(s[i]))
			s[i] = tolower(s[i]);
	}
}

char *process_cdata(char *cdata)
{
	char *dest = (char *)malloc((strlen(cdata) - 9) * sizeof(char));
	memset(dest, 0, strlen(cdata)-9);
	int i, j = 0; 
	for (i = 8; i < strlen(cdata)-2; i++)
		dest[j++] = cdata[i];
	dest[j] = '\0';
	return dest;
}


//template<typename T>
void dumpVector(vector<string> t)
{
	for (vector<string>::iterator it = t.begin(); it != t.end(); it++) {
		cout << *it;
		cout << endl;
	}
}

#endif

#undef OLD_C_CODE
#ifdef OLD_C_CODE
int get_ws_count(char *str)
{
	int i, n = 0, str_len = strlen(str);
	for (i = 0; i < str_len; i++, str++)
		if (*str == 0x20)
			n++;
	return n;	
}

char *trim(char *str)
{
	char *str_last, *str_cur;
	if (str != NULL) {
		for ( ; *str == 0x20; ++str);
		for (str_last = str_cur = str; *str_cur != '\0'; ++str_cur)
			if (*str_cur != 0x20)
				str_last = str_cur;
		*++str_last = '\0';
		return str;
	}
	return NULL;
}

// split the str into a two-d array
char **split(char *str, int *count)
{
	char **t;
	int i = 0, j, n = 0;
	t = (char **) malloc (sizeof(char) * QDICT_BUFFER_SZ);
	memset(t, 0, QDICT_BUFFER_SZ);
	while(*str != '\0') {
		if (*str != '\0' && *str != 0x20) {
			t[i] = (char *) malloc(QDICT_BUFFER_SZ * sizeof(char));
			memset(t[i], 0, QDICT_BUFFER_SZ);
			for (j = 0; *str != '\0' && *str != 0x20; str++) {
				t[i][j++] = *str;
			}
			t[i][j] = '\0';
			i++;
		}
		str++;
	}
	*count = i;
	return t;
}

char *join(int num, char **phrases, char *separator)
{
	int i, phrase_whole_len = 0;
	char *p;
	for (i = 0; i < num; i++)
		phrase_whole_len += strlen(phrases[i]);
	p = (char *) malloc((phrase_whole_len + num) * sizeof(char));
	memset(p, 0, (phrase_whole_len + num));
	strncpy(p, phrases[0], strlen(phrases[0]));
	for (i = 1; i < num; i++) {
		strncat(p, separator, strlen(separator));
		strncat(p, phrases[i], strlen(phrases[i]));
	}
	p[strlen(p)] = '\0';
	return p;
}


char *process_cdata(char *cdata)
{
	char *dest = malloc((strlen(cdata) - 9) * sizeof(char));
	memset(dest, 0, strlen(cdata)-9);
	int i, j = 0; 
	for (i = 8; i < strlen(cdata)-2; i++)
		dest[j++] = cdata[i];
	dest[j] = '\0';
	return dest;
}

#endif


#undef DEBUG
#define DEBUG
#ifdef DEBUG
// JUST TEST CODE
int main(int argc, char **argv)
{
	/*
	char buf[] = "Hello world the big C";
	int count = 0, i = 0;
	char **result;
	result = split(buf, &count);
	printf("count: %d\n", count);
	for (i = 0; i < count; i++)
		printf("%s", result[i]);
	*/
	vector<string> s;
	s.push_back("Hello");
	s.push_back("Good");
	dumpVector(s);
	string str("good?");
	trimPunctuation(str);
	cout << str << endl;
	return 0;
}
#endif
