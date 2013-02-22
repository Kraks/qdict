/*
 * Filename: network.h
 * Author: Kraks <kiss.kraks@gmail.com>
 */

struct MemoryStruct {
  char *memory;
  size_t size;
};

word_t *query_from_network(char *word_str, word_t *w);
char *youdao_dict_url(char *word);
word_t *resolve_youdao_xml(char *xml, word_t *w);
mxml_type_t youdao_callback(mxml_node_t *node);
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
