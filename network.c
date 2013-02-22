/*
 * Filename: network.c
 * Author: Kraks <kiss.kraks@gmail.com>
 */

#include "global.h"
#include "network.h"
#include "utils.h"

word_t *query_from_network(char *word_str, word_t *w)
{
	CURL *curl_handle;
	char *url = youdao_dict_url(word_str);
	struct MemoryStruct chunk;
	
#ifdef DEBUG
	printf("DEBUG: query_from_network() url: %s\n", url);
#endif

	chunk.memory = malloc(1);
	chunk.size = 0; 
	curl_global_init(CURL_GLOBAL_ALL);

	curl_handle = curl_easy_init();
	curl_easy_setopt(curl_handle, CURLOPT_URL, url);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
	curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
	curl_easy_perform(curl_handle);
	curl_easy_cleanup(curl_handle);

#ifdef DEBUG
	printf("DEBUG: query_from_network() %lu bytes retrieved\n", (long)chunk.size);
	FILE *fp;
	fp = fopen("_debug_.xml", "w");
	if (fp) {
		fputs((char *)chunk.memory, fp);
		fclose(fp);
	}
#endif
	
	w = resolve_youdao_xml((char *)chunk.memory, w);

	//curl_global_cleanup();
	if(chunk.memory)
		free(chunk.memory);

	return w;
}

char *youdao_dict_url(char *word)
{
	char base[] = "http://dict.youdao.com/fsearch?q=";
	char *url = malloc((strlen(base) + strlen(word) + 1) * sizeof(char));
	memset(url, 0, (strlen(base) + strlen(word) + 1));
	strncpy(url, base, strlen(base));
	strncat(url, word, strlen(word));
	return url;
}

word_t *resolve_youdao_xml(char *xml, word_t *w)
{
	mxml_node_t *tree;
	mxml_node_t *node;
	
	if (w == NULL)
		return NULL;

	tree = mxmlLoadString(NULL, xml, youdao_callback);
	node = mxmlFindElement(tree, tree, "return-phrase", NULL, NULL, MXML_DESCEND);
	
	if (node) {
		k_strcpy(w->original, process_cdata(node->child->value.opaque));
	}
	
	node = mxmlFindElement(tree, tree, "phonetic-symbol", NULL, NULL, MXML_DESCEND);
	if (node && node->child) {

		k_strcat(w->phonetic, node->child->value.text.string);
	}

	node = mxmlFindElement(tree, tree, "content", NULL, NULL, MXML_DESCEND);
	if (node) {
		k_strcpy(w->translation, process_cdata(node->child->value.opaque));
		while (node) {
			node = mxmlFindElement(node, tree, "content", NULL, NULL, MXML_DESCEND);
			if (node) {
				k_strcat(w->translation, "\n");
				k_strcat(w->translation, process_cdata(node->child->value.opaque));
			}
		}
	}
	//mxmlDelete(tree);
	return w;
}

mxml_type_t youdao_callback(mxml_node_t *node)
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

	mem->memory = realloc(mem->memory, mem->size + realsize + 1);
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
