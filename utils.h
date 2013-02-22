/*
 * Filename: utils.h
 * Author: Kraks <kiss.kraks@gmail.com>
 */

int get_ws_count(char *str);
char *trim(char *str);
char *k_strcat(char *dest, char *src);
char *k_strcpy(char *dest, char *src);
char **split(int n, char *str);
char *join(int num, char **phrases, char *separator);
char *process_cdata(char *cdata);
