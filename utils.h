/*
 * Filename: utils.h
 * Author: Kraks <kiss.kraks@gmail.com>
 */
#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

using namespace std;

string join(vector<string> v, vector<string>::iterator begin, vector<string>::iterator end);
vector<string> split(string s, char delim, int rep);
int whitespaceCount(string s);
char *process_cdata(char *cdata);
