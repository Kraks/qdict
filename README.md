qdict
=====

version 0.1

A fast, simple English-Chinese dictionary.

Need network and Youdao dictionary web service for query, and then will save the translation to local db.

Use Berkeley DB, libcurl and mini-XML library.

Usage
-----
qdict [word] [+]  
add [+] at the end of query content, will add the translation into wordbook  
-i, --interactive  
-w, --wordbook  
-h, --help  

History
-----
version 0.1  
new code construction  
add local berkeleyDB as cache  
add psersonal wordbook  
fixed bugs in phrases query function 

version 0.02  
could query phrases and its translation  
local xml file cache

version 0.01  
could query basic word translation from youdao dict web service.

