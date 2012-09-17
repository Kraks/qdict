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

int check_cache(char *word);

int get_xml(char *word);

char *construct_url(char *word);

char *construct_filename(char *word);

int print_trans(char *xml_file_name);

void print_word(char *word);

void print_help();

static size_t write_xml_file(void *ptr, size_t size, size_t nmemb, void *stream);

char *process_cdata(char *cdata);

mxml_type_t type_callback(mxml_node_t *node);

