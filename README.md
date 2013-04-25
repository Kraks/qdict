qdict
=====

A CLI Chinese-English dictionary.  
Fast, and easy to use.  

Usage
-----
usage: `qdict [word] [+] [-]`   
the `+` optional symbol means add the word to wordbook.   
the `-` optional symbol means del the word from wordbook.   
the `+` and `-` are confict   
other optional:   
-w, --wordbook       show the wordbook   
-d, --dict           show all the cache word   
-i, --interactive    enter interactive mode to query   
-h, --help           print this help information   

History
-----
version 0.2  
rewrite most of code used c++   
using `db_cxx`
add remove word record function from wordbook   
fix bugs, more stable and fast  

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

