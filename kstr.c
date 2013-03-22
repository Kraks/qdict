/* Kraks' String Library
 * Author: Kraks <kiss.kraks@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kstr.h"

kstr __newKstr(const void *init, size_t initlen)
{
	struct s_kstr *k;
	k = malloc(sizeof(struct s_kstr) + initlen +1);
	k->len = initlen;
	k->free = 0;
	if (initlen) {
		if (init)
			memcpy(k->buf, init, initlen);
		else
			memset(k->buf, 0, initlen);
	}
	k->buf[initlen] = '\0';
	return (char *)k->buf;
}

kstr newEmptyKstr(void)
{
	return __newKstr("", 0);
}

kstr newKstr(const char *init)
{
	size_t initlen = (init == NULL) ? 0 : strlen(init);
	return __newKstr(init, initlen);
}

void updateKstrLen(kstr s)
{
	struct s_kstr *k = (void *) (s-(sizeof(struct s_kstr)));
	int reallen = strlen(s);
	k->free += (k->len - reallen);
	k->len = reallen;
}

void clearKstr(kstr s)
{
	struct s_kstr *k = (void *) (s-(sizeof(struct s_kstr)));
	k->free += k->len;
	k->len = 0;
	k->buf[0] = '\0';
}

kstr dupKstr(const kstr s)
{
	return __newKstr(s, kstrlen(s));
}

void freeKstr(kstr s)
{
	if (s == NULL)
		return;
	else
		free(s-sizeof(struct s_kstr));
}

int kstrlen(const kstr s)
{
	return strlen((char *) s);
}

// WHY STATIC ?
static kstr makeRoomForKstr(kstr s, size_t addlen) 
{
	struct s_kstr *k, *newk, *t;
	k = (void *) (s-(sizeof(struct s_kstr)));

	size_t free = k->free;
	size_t len, newlen;

	if (free >= addlen)
		return s;

	len = kstrlen(s);
	newlen = (len+addlen) * 2;
	newk = realloc(k, sizeof(struct s_kstr) + newlen + 1);
	newk->free = newlen - len;
	return newk->buf;
}

void dumpKstr(kstr s)
{
	struct s_kstr *k = (void *) (s-(sizeof(struct s_kstr)));
	printf("===========================\n");
	printf("orignial string: %s\n", (char *) (k->buf));
	printf("kstr len: %d\n", k->len);
	printf("kstr free: %d\n", k->free);
	printf("===========================\n");
}

#define DEBUG

#ifdef DEBUG
int main(int argc, char **argv)
{
	kstr s = newKstr("Hello World");
	dumpKstr(s);
	return 0;
}
#endif
