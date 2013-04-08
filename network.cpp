/*
 * Filename: network.cpp
 * Author: Kraks <kiss.kraks@gmail.com>
 */

#include "global.h"
#include "network.h"
#include "utils.h"

t_word_string queryFromNetwork(string word, t_word_string &w)
{
	CURL *curl_handle;
	string url = youdaoDictUrl(word);
	struct MemoryStruct chunk;
	
#ifdef DEBUG
	printf("DEBUG: queryFromNetwork() url: %s\n", url);
#endif

	chunk.memory = (char *)malloc(1);
	chunk.size = 0; 
	curl_global_init(CURL_GLOBAL_ALL);

	curl_handle = curl_easy_init();
	curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
	curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
	curl_easy_perform(curl_handle);
	curl_easy_cleanup(curl_handle);

#ifdef DEBUG
	printf("DEBUG: queryFromNetwork() %lu bytes retrieved\n", (long)chunk.size);
	FILE *fp;
	fp = fopen("_debug_.xml", "w");
	if (fp) {
		fputs((char *)chunk.memory, fp);
		fclose(fp);
	}
#endif
	
	w = resolveYoudaoXML((char *)chunk.memory, w);

	if(chunk.memory)
		free(chunk.memory);

	//curl_global_cleanup();
	return w;
}

string youdaoDictUrl(string word)
{
	string url("http://dict.youdao.com/fsearch?q=");
	url+=word;
	return url;
}

t_word_string resolveYoudaoXML(char *xml, t_word_string &w)
{
	mxml_node_t *tree;
	mxml_node_t *node;
	
	if (xml == NULL)
		cout << "ERROR XML NULL" << endl;

	tree = mxmlLoadString(NULL, xml, youdaoCallbackFunction);
	node = mxmlFindElement(tree, tree, "return-phrase", NULL, NULL, MXML_DESCEND);
	
	if (node) {
		w.original = process_cdata(node->child->value.opaque);
	}
	
	node = mxmlFindElement(tree, tree, "phonetic-symbol", NULL, NULL, MXML_DESCEND);
	if (node && node->child) {

		w.phonetic = node->child->value.text.string;
	}

	node = mxmlFindElement(tree, tree, "content", NULL, NULL, MXML_DESCEND);
	if (node) {
		w.translation = process_cdata(node->child->value.opaque);
		while (node) {
			node = mxmlFindElement(node, tree, "content", NULL, NULL, MXML_DESCEND);
			if (node) {
				w.translation += "\n";
				w.translation += process_cdata(node->child->value.opaque);
			}
		}
	}
	//mxmlDelete(tree);
	return w;
}

mxml_type_t youdaoCallbackFunction(mxml_node_t *node)
{
	const char *type;
	if (node != NULL) {
		type = node->value.element.name;
		//printf("debug %s\n", node->value.element.name);
	}
	if (!strcmp(type, "content"))
		return (MXML_OPAQUE);
	else if (!strcmp(type, "phonetic-symbol"))
		return (MXML_TEXT);
	else
		return (MXML_TEXT);
}

static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)userp;

	mem->memory = (char *)realloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory == NULL) {
	/* out of memory! */ 
	printf("Error: not enough memory (realloc returned NULL)\n");
	exit(EXIT_FAILURE);
	}

	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}
