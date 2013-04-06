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
#include <db.h>
#include <mxml.h>
#include <curl/curl.h>

typedef struct {
	kstr original;
	kstr phonetic;
	kstr translation;
} word_t;

void printWordType(word_t w);
void initWordType(word_t *w, const char *o, const char *p, const char *t);
void freeWordType(word_t *w);

#define WHITESPACE " "

#define TRUE 1
#define FALSE 0
#define QDICT_BUFFER_SZ 255

