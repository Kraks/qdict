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

#define MAX_WORD_LENGTH 32
#define MAX_PHONETIC_LENGTH 32
#define MAX_TRANSLATION_LENGTH 128

typedef struct WORD {
	char original[MAX_WORD_LENGTH];
	char phonetic[MAX_PHONETIC_LENGTH];
	char translation[MAX_TRANSLATION_LENGTH];
} word_t;

word_t *init_word_t(word_t *w);
void free_word_t(word_t *w);
word_t *clone_word_t(word_t *w);
#define WHITESPACE " "

#define TRUE 1
#define FALSE 0

#define DEBUG
