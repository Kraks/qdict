qdict:qdict.c qdict.h
	gcc qdict.c -o qdict -I/usr/local/include -L/usr/local/lib -lcurl -D_THREAD_SAFE -D_REENTRANT -I/usr/local/include -L/usr/local/lib -lmxml -lpthread -Wall
