/*
 * Filename: utils.c
 * Author: Kraks <kiss.kraks@gmail.com>
 */

#include "utils.h"
#include "global.h"
int get_ws_count(char *str)
{
	int i, n = 0, str_len = strlen(str);
	for (i = 0; i < str_len; i++, str++)
		if (*str == 0x20)
			n++;
	return n;	
}

char *trim(char *str)
{
	char *str_last, *str_cur;
	if (str != NULL) {
		for ( ; *str == 0x20; ++str);
		for (str_last = str_cur = str; *str_cur != '\0'; ++str_cur)
			if (*str_cur != 0x20)
				str_last = str_cur;
		*++str_last = '\0';
		return str;
	}
	return NULL;
}

char *k_strcat(char *dest, char *src)
{
	return strncat(dest, src, strlen(src));
}

char *k_strcpy(char *dest, char *src)
{
	return strncpy(dest, src, strlen(src));
}

char **split(int n, char *str)
{
	char **t;
	int i, j, len = strlen(str);
	t = (char **) malloc ((len + 1) * sizeof(char));
	for (i = 0; i < n; i++) { 
		t[i] = (char *) malloc(MAX_WORD_LENGTH * sizeof(char));
		for (j = 0; *str != '\0' && *str != 0x20; str++) {
			t[i][j++] = *str;
		}
		t[i][j] = '\0';
		str++;
	}
	return t;
}

char *join(int num, char **phrases, char *separator)
{
	int i, phrase_whole_len = 0;
	char *p;
	for (i = 0; i < num; i++)
		phrase_whole_len += strlen(phrases[i]);
	p = (char *) malloc((phrase_whole_len + num) * sizeof(char));
	memset(p, 0, (phrase_whole_len + num));
	strncpy(p, phrases[0], strlen(phrases[0]));
	for (i = 1; i < num; i++) {
		strncat(p, separator, strlen(separator));
		strncat(p, phrases[i], strlen(phrases[i]));
	}
	p[strlen(p)] = '\0';
	return p;
}

char *process_cdata(char *cdata)
{
	char *dest = malloc((strlen(cdata) - 9) * sizeof(char));
	memset(dest, 0, strlen(cdata)-9);
	int i, j = 0; 
	for (i = 8; i < strlen(cdata)-2; i++)
		dest[j++] = cdata[i];
	dest[j] = '\0';
	return dest;
}
