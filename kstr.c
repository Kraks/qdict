/* Kraks' String Library
 * Author: Kraks <kiss.kraks@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include "kstr.h"

kstr __kstrNew(const void *init, size_t initlen)
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

kstr kstrNewEmpty(void)
{
	return __kstrNew("", 0);
}

kstr kstrNew(const char *init)
{
	size_t initlen = (init == NULL) ? 0 : strlen(init);
	return __kstrNew(init, initlen);
}

kstr __kstrCat(kstr s, void *t, size_t len)
{
	struct s_kstr *k;
	size_t cur_len = kstrlen(s);

	s = kstrMakeRoom(s, len);
	if (s == NULL)
		return NULL;

	k = (void *) (s-(sizeof(struct s_kstr)));
	memcpy(s+cur_len, t, len);
	k->len = cur_len + len;
	k->free = k->free - len;
	s[cur_len + len] = '\0';
	return s;
}

kstr kstrCatKstr(kstr s, kstr t)
{
	return __kstrCat(s, t, kstrlen(t));
}

kstr kstrCatStr(kstr s, char *t)
{
	return __kstrCat(s, t, strlen(t));
}

void kstrUpdateLen(kstr s)
{
	struct s_kstr *k = (void *) (s-(sizeof(struct s_kstr)));
	int reallen = strlen(s);
	k->free += (k->len - reallen);
	k->len = reallen;
}

void kstrClear(kstr s)
{
	struct s_kstr *k = (void *) (s-(sizeof(struct s_kstr)));
	k->free += k->len;
	k->len = 0;
	k->buf[0] = '\0';
}

kstr kstrDup(const kstr s)
{
	return __kstrNew(s, kstrlen(s));
}

void kstrFree(kstr s)
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
static kstr kstrMakeRoom(kstr s, size_t addlen) 
{
	struct s_kstr *k, *newk, *t;
	k = (void *) (s-(sizeof(struct s_kstr)));

	size_t free = k->free;
	size_t len, newlen;

	if (free >= addlen)
		return s;

	len = kstrlen(s);
	newlen = (len+addlen) * 2; // XXX
	newk = realloc(k, sizeof(struct s_kstr) + newlen + 1);
	newk->free = newlen - len;
	return newk->buf;
}

// Make a kstr have the lenght of 'len'
kstr kstrGrow(kstr s, size_t len) 
{
	struct s_kstr *k = (void *) (s-(sizeof(struct s_kstr)));
	size_t total_len, cur_len = k->len;

	if (len <= cur_len)
		return s;
	s = kstrMakeRoom(s, len - cur_len);
	if (s == NULL)
		return NULL;
	
	k = (void *) (s-(sizeof(struct s_kstr)));
	memset(s+cur_len, 0, (len-cur_len+1));
	total_len = k->len + k->free;
	k->len = len;
	k->free = total_len - k->len;
	return s;
}

kstr __kstrCpy(kstr s, char *t, size_t len)
{
	struct s_kstr *k = (void *) (s-(sizeof(struct s_kstr)));
	size_t total_len = k->len + k->free;

	if (total_len < len) {
		s = kstrMakeRoom(s, len - k->len);
		if (s == NULL)
			return NULL;
		k = (void *) (s-(sizeof(struct s_kstr)));
		total_len = k->free + k->len;
	}
	memcpy(s, t, len);
	s[len] = '\0';
	k->len = len;
	k->free = total_len - len;
	return s;
}

kstr kstrCpy(kstr s, char *t)
{
	return __kstrCpy(s, t, strlen(t));
}

kstr kstrCatVprintf(kstr s, const char *fmt, va_list ap)
{
	va_list cpy;
	char *buf, *t;
	size_t buflen = 16;

	while (1) {
		buf = malloc(buflen);
		if (buf == NULL)
			return NULL;

		buf[buflen - 2] = '\0';
		va_copy(cpy, ap);
		vsnprintf(buf, buflen, fmt, cpy);
		if (buf[buflen -2] != '\0') {
			free(buf);
			buflen *= 2;
			continue;
		}
		break;
	}
	t = kstrCatStr(s, buf);
	free(buf);
	return t;
}

kstr kstrCatPrintf(kstr s, const char *fmt, ...)
{
	va_list ap;
	char *t;
	va_start(ap, fmt);
	t = kstrCatVprintf(s, fmt, ap);
	va_end(ap);
	return t;
}

void kstrToLower(kstr s)
{
	int j, len = kstrlen(s);
	for (j = 0; j < len; j++)
		s[j] = tolower(s[j]);
}

void kstrToUpper(kstr s)
{
	int j, len = kstrlen(s);
	for (j = 0; j < len; j++)
		s[j] = toupper(s[j]);
}

int kstrCmp(kstr a, kstr b)
{
	size_t l1, l2, minlen;
	int cmp;

	l1 = kstrlen(a);
	l2 = kstrlen(b);
	minlen = (l1 < l2) ? l1 : l2;
	cmp = memcmp(a, b, minlen);
	if (cmp == 0)
		return l1-l2;
	return cmp;
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
#undef DEBUG
#ifdef DEBUG
int main(int argc, char **argv)
{
	kstr s1 = kstrNew("Hello World");
	kstr s2 = kstrNew("\nThis is just a string test");
	dumpKstr(s1);
	dumpKstr(s2);
	s2 = kstrCatKstr(s1, s2);
	dumpKstr(s2);
	return 0;
}
#endif
