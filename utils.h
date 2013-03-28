/*
 * Filename: utils.h
 * Author: Kraks <kiss.kraks@gmail.com>
 */

int get_ws_count(char *str);
char *trim(char *str);
char *join(int num, char **phrases, char *separator);
char *process_cdata(char *cdata);

// new version
char **split(char *str, int *count)
