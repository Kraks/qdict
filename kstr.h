/* Kraks' String Library
 * Author: Kraks <kiss.kraks@gmail.com>
 */

struct s_kstr {
	int len;
	int free;
	char buf[];
};

typedef char *kstr;

kstr __kstrNew(const void *init, size_t initlen);
kstr kstrNewEmpty(void);
kstr kstrNew(const char *init);
kstr __kstrCat(kstr s, void *t, size_t len);
kstr kstrCatKstr(kstr s, kstr t);
kstr kstrCatStr(kstr s, char *t);
void kstrUpdateLen(kstr s);
void kstrClear(kstr s);
kstr kstrDup(const kstr s);
void kstrFree(kstr s);
int kstrlen(const kstr s);
static kstr kstrMakeRoom(kstr s, size_t addlen);
void dumpKstr(kstr s);
