/*
 * Filename: network.h
 * Author: Kraks <kiss.kraks@gmail.com>
 */

struct MemoryStruct {
  char *memory;
  size_t size;
};


word_t *queryFromNetwork(char *word_str, word_t *w);
char *youdaoDictUrl(char *word);
word_t *resolveYoudaoXML(char *xml, word_t *w);
mxml_type_t youdaoCallbackFunction(mxml_node_t *node);
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
