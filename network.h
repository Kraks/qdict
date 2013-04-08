/*
 * Filename: network.h
 * Author: Kraks <kiss.kraks@gmail.com>
 */

struct MemoryStruct {
  char *memory;
  size_t size;
};

t_word_string *queryFromNetwork(string word, t_word_string &w);
string youdaoDictUrl(string word);
t_word_string resolveYoudaoXML(char *xml, t_word_string &w);
mxml_type_t youdaoCallbackFunction(mxml_node_t *node);
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
