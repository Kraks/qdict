/*
 * Filename: global.h
 * Author: Kraks <kiss.kraks@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <db_cxx.h>
#include <mxml.h>
#include <curl/curl.h>
#include <string>

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

typedef struct {
	char original[128];
	char phonetic[128];
	char translation[1024];
} t_word_c_str;

