#include "qdict.h"

#define WORD_LENGTH 64

int main(int argc, char **argv)
{
	int i;
	char c;
	char *buf;
	if (argc != 2) {
		print_help();
		exit(0);
	}
	
	if (argv[1][0] == '-') {
		//interactive mode
		if (argv[1][1] == 'i') {
			buf = malloc(WORD_LENGTH * sizeof(char));
			printf("> ");
			while ((c = getchar()) != EOF) {
				memset(buf, 0, WORD_LENGTH);
				i = 0;
				buf[i++] = c;
				while ((c = getchar()) != '\n' && i < WORD_LENGTH)
					buf[i++] = c;
				buf[i] = '\0';
				//printf("debug %s\n", buf);
				query_word(buf);
				printf("> ");
			}
			exit(0);
		}
		if (argv[1][1] == 'h') {
			print_help();
			exit(0);
		}
	}
	
	query_word(argv[1]);
	return 0;
}

void query_word(char *word)
{
	//query word translation
	if (check_cache(word)) {
		print_word(word);
		print_trans(word);
	} else {
		//printf("debug %s\n", argv[1]);
		get_xml(word);
		print_word(word);
		print_trans(word);
	}
}

void print_help()
{
	fprintf(stdout, "Useage: qdict <query word>\n");
}

int get_xml(char *word)
{
	//printf("debug get_xml\n");
	
	char *url = construct_url(word);
	char *filename = construct_filename(word);
	CURL *curl_handle;
	FILE *xml_file;
	
	curl_global_init(CURL_GLOBAL_ALL);
	curl_handle = curl_easy_init();
	curl_easy_setopt(curl_handle, CURLOPT_URL, url);
	
	//printf("debug %s\n", url);
	
	//debug output
  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 0L);
  //disable progress meter, set to 0L to enable and disable debug output
  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
  
  //send all data to this function
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_xml_file);
  
  xml_file = fopen(filename, "w+");
  if (xml_file) {
		curl_easy_setopt(curl_handle, CURLOPT_FILE, xml_file);
		curl_easy_perform(curl_handle);
		fclose(xml_file);
		curl_easy_cleanup(curl_handle);
		return 0;
	}
	else {
		fprintf(stderr, "Error: can not write the file\n");
		exit(-1);
	}
}

char *construct_url(char *word)
{
	char base[] = "http://dict.youdao.com/fsearch?q=";
	char *url = malloc((strlen(base) + strlen(word) + 1) * sizeof(char));
	strncpy(url, base, strlen(base));
	strncat(url, word, strlen(word));
	return url;
}

char *construct_filename(char *word)
{
	char *filename = malloc((strlen(word) + 11) * sizeof(char));
	strncpy(filename, "cache/", 6);
	strncat(filename, word, strlen(word));
	strncat(filename, ".xml", 4);
	return filename;
}

static size_t write_xml_file(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

int print_trans(char *word)
{
	char *filename = construct_filename(word);
	//printf("debug filename: %s\n", filename);
	FILE *xml_fp;
	mxml_node_t *tree;
	mxml_node_t *node;
	
	xml_fp = fopen(filename, "r");
	tree = mxmlLoadFile(NULL, xml_fp, type_callback);
	
	//print phonetic
	node = mxmlFindElement(tree, tree, "phonetic-symbol", NULL, NULL, MXML_DESCEND);
	if (node != NULL)
		printf("%s\n", node->child->value.text.string);
	else
		fprintf(stderr, "Error: no phonetic for this word\n");
	
	//print translation
	node = mxmlFindElement(node, tree, "content", NULL, NULL, MXML_DESCEND);
	if (node != NULL) {
		while (node != NULL) {
			printf("%s\n", process_cdata(node->child->value.opaque));
			node = mxmlFindElement(node, tree, "content", NULL, NULL, MXML_DESCEND);
		}
		fclose(xml_fp);
		return 0;
	}
	else {
		fprintf(stderr, "Error: no translation for this word\n");
		fclose(xml_fp);
		return 0;
	}
}

int check_cache(char *word)
{
	char *filename = construct_filename(word);
	if (access("cache", F_OK) != 0)
		mkdir("cache", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if (access(filename, R_OK) < 0)
		return 0;
	else
		return 1;
}

char *process_cdata(char *cdata)
{
	char *dest = malloc((strlen(cdata) - 9) * sizeof(char));
	int i, j = 0; 
	for (i = 8; i < strlen(cdata)-2; i++)
		dest[j++] = cdata[i];
	dest[j] = '\0';
	return dest;
}

mxml_type_t type_callback(mxml_node_t *node)
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

void print_word(char *word)
{
	printf("%s\n", word);
}
