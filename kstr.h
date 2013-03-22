/* Kraks' String Library
 * Author: Kraks <kiss.kraks@gmail.com>
 */

struct s_kstr {
	int len;
	int free;
	char buf[];
};

typedef char *kstr;

kstr __newKstr(const void *init, size_t initlen);
kstr newEmptyKstr(void);
kstr newKstr(const char *init);
void updateKstrLen(kstr s);
void clearKstr(kstr s);
kstr dupKstr(const kstr s);
void freeKstr(kstr s);
int kstrlen(const kstr s);
static kstr makeRoomForKstr(kstr s, size_t addlen);
void dumpKstr(kstr s);
