/*
 * Filename: qdict.c
 * Author: Kraks <kiss.kraks@gmail.com>
 */
#include "global.h"
#include "qdict.h"
#include "utils.h"
#include "network.h"
#include "db.h"

void prase_args(int argc, char **argv)
{
	char *buf = NULL;
	
#ifdef DEBUG
	int i;
	for (i = 0; i < argc; i++)
		printf("DEBUG: prase_args() argv[%d]: %s\n", i, argv[i]);
#endif

	if (argc == 1) {
		query(argv[0], NOT_SAVE_TO_WORDBOOK);
	}
	else if (argc == 2 && !strcmp(argv[1], "+")) {
		query(argv[0], SAVE_TO_WORDBOOK);
	}
	else if (argc >= 2 && strcmp(argv[argc-1], "+")) {
		buf = join(argc, argv, WHITESPACE);
		query(buf, NOT_SAVE_TO_WORDBOOK);
		if (buf)
			free(buf);
	}
	else if (argc >= 3 && !strcmp(argv[argc-1], "+")) {
		buf = join(argc-1, argv, WHITESPACE);
		query(buf, SAVE_TO_WORDBOOK);
		if (buf)
			free(buf);
	}
	else {
		printf("Oh Ooooops, what's the matter!\n");
	}
}

void query(char *word_str, int save_to_wordbook)
{
	word_t *w;
	w = init_word_t(w);
	char *trimed_word = trim(word_str);

#ifdef DEBUG
	printf("DEBUG: query() word_str:%s\n", trimed_word);
#endif

	if (is_in_db(trimed_word, DB_CACHE)) {
		query_in_db(trimed_word, w, DB_CACHE);
	}
	else {
		query_from_network(trimed_word, w);
		save_to_db(w, DB_CACHE);
	}

	if (save_to_wordbook)
		save_to_db(w, DB_WORDBOOK);
		
	if (is_in_db(trimed_word, DB_WORDBOOK))
		printf("DEBUG: query() %s is in %s\n", trimed_word, DB_WORDBOOK);
	else 
		printf("DEBUG: query() %s is NOT %s\n", trimed_word, DB_WORDBOOK);
	print_result(w);
	
	// XXX
	//free_word_t(w);
}

void print_help()
{
	
}

void interactive()
{
	int i;
	int whitespace_count;
	char c;
	char *buf;
	char **phrases = NULL;
	
	buf = malloc(MAX_WORD_LENGTH * sizeof(char));
	printf(">> ");
	while ((c = getchar()) != EOF) {
		memset(buf, 0, MAX_WORD_LENGTH);
		i = 0;
		buf[i++] = c;
		while ((c = getchar()) != '\n' && i < MAX_WORD_LENGTH)
			buf[i++] = c;
		buf[i] = '\0';
		buf = trim(buf);

		if (strstr(buf, WHITESPACE)) {
			whitespace_count = get_ws_count(buf);
			phrases = split(whitespace_count + 1, buf);
			prase_args(whitespace_count + 1, phrases);
		} else {
			query(buf, NOT_SAVE_TO_WORDBOOK);
		}
		if (phrases)
			free(phrases);
		printf(">> ");
	}
}

void print_result(word_t *w)
{
	if (w->original)
		printf("%s\n", w->original);
	if (w->phonetic && strcmp(w->phonetic,""))
		printf("%s\n", w->phonetic);
	if (w->translation)
		printf("%s\n", w->translation);	
}

word_t *init_word_t(word_t *w)
{
	w = (word_t *) malloc(sizeof(word_t));
	memset(w, 0, sizeof(word_t));
	return w;
}

word_t *clone_word_t(word_t *w)
{
	word_t *t;
	t = (word_t *) malloc(sizeof(word_t));
	memset(w, 0, sizeof(word_t));
	k_strcpy(t->original, w->original);
	k_strcpy(t->phonetic, w->phonetic);
	k_strcpy(t->translation, w->translation);
	return t;
}

void free_word_t(word_t *w)
{
	if (w)
		free(w);
}

int main(int argc, char **argv)
{
	if (argc == 1 ||
		!strcmp(argv[1], "-h") ||
		!strcmp(argv[1], "--help")) {
		print_help();
	}
	else if (!strcmp(argv[1], "-w") || !strcmp(argv[1], "--wordbook")) {
		show_wordbook();
	}
	else if (!strcmp(argv[1], "-i") || !strcmp(argv[1], "--interactive")) {
		interactive();
	}
	else {
		prase_args(argc-1, argv+1);
	}
}
