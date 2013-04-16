qdict
=====

A CLI Chinese-English dictionary.
Fast, and easy to use.

Usage
-----
usage: ./qdict [word] [+]
 the last [+] optional symbol means add the word and its translation to wordbook.
other optional:
 -w, --wordbook       show the wordbook
 -d, --dict           show all the cache word
 -i, --interactive    enter interactive mode to query
 -h, --help           print this help information

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

