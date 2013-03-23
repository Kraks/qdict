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
kstr kstrGrow(kstr s, size_t len);
kstr __kstrCpy(kstr s, char *t, size_t len);
kstr kstrCpy(kstr s, char *t);
kstr kstrCatVprintf(kstr s, const char *fmt, va_list ap);
kstr kstrCatPrintf(kstr s, const char *fmt, ...);
void kstrToUpper(kstr s);
int kstrCmp(kstr a, kstr b);
void dumpKstr(kstr s);
