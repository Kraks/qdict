// qdict
// Filename: qdict.h
// Version: 0.02
// Author: Kraks <kiss.kraks@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

//Using Mini-XML lib
#include <mxml.h>

//Using libcurl
#include <curl/curl.h>

void query_word(char *word);

void query_phrases(int argc, char **argv);

int check_cache(char *word);

int get_xml(char *word, char *filename);

char *catenate_phrase(int phrase_num, char **phrases, char *connector);

char *construct_url(char *word);

char *construct_filename(char *word);

int print_trans(char *word, int is_phrase);

void print_word(char *word);

void print_help();

static size_t write_xml_file(void *ptr, size_t size, size_t nmemb, void *stream);

char *process_cdata(char *cdata);

mxml_type_t type_callback(mxml_node_t *node);

int get_ws_num(char *str);

char *trim(char *str);

char **split_phrases(int n, char *str);
