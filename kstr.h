/* Kraks' String Library
 * Author: Kraks <kiss.kraks@gmail.com>
 */

struct s_kstr {
	int len;
	int free;
	char buf[];
};

typedef char *kstr;

