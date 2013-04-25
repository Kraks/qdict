/******^-^
 * Filename: global.h
 * Author: Kraks <kiss.kraks@gmail.com>
 *
 ***/

#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <db_cxx.h>
#include <mxml.h>
#include <curl/curl.h>

using namespace std;

#define MAX_WORD_LENGTH 32
#define MAX_PHONETIC_LENGTH 32
#define MAX_TRANSLATION_LENGTH 128
#define QDICT_BUFFER_SZ 255

typedef struct {
	string original;
	string phonetic;
	string translation;
} t_word_string;

#define WHITESPACE " "

#define TRUE 1
#define FALSE 0
#define QDICT_BUFFER_SZ 255
typedef struct {
	char original[128];
	char phonetic[128];
	char translation[1024];
} t_word_c_str;

void printWord(t_word_string w);
void initWordType(t_word_string &w, string o, string p, string t);
//#define DEBUG
#endif
