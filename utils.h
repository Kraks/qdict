/******^-^
 * Filename: utils.h
 * Author: Kraks <kiss.kraks@gmail.com>
 *
 ***/
#include "global.h"

string join(vector<string> v, vector<string>::iterator begin, vector<string>::iterator end, string connector);
vector<string> split(string s, char delim, int rep);
int whitespaceCount(string s);
char *process_cdata(char *cdata);
void stringTolower(string &s);
void dumpVector(vector<string> v);
