/*
 * Filename: utils.h
 * Author: Kraks <kiss.kraks@gmail.com>
 */

string join(vector<string> v, vector<string>::iterator begin, vector<string>::iterator end);
vector<string> split(string s, char delim, int rep=0);
int whitespaceCount(string s);
char *process_cdata(char *cdata);
