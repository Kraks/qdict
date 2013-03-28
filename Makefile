qdict:main.o utils.o network.o db.o
	gcc -o qdict main.o utils.o network.o db.o -g -I/usr/local/include -L/usr/local/lib -lcurl -D_THREAD_SAFE -D_REENTRANT -I/usr/local/include -L/usr/local/lib -lmxml -ldb -lpthread -Wall

main.o:qdict.c qdict.h
	gcc -c qdict.c -o main.o

utils.o:utils.c utils.h
	gcc -c utils.c -o utils.o
	

network.o:network.c network.h
	gcc -c network.c -o network.o

db.o:db.c db.h
	gcc -c db.c -o db.o

clean:
	rm -r -f *~
	rm -r -f *.o

cleandb:
	rm -r -f *.db

statistic:
	find -name "*.H" -or -name "*.cpp" -or -name "*.c" -or -name "*.h" | xargs wc -l

utilstest:
	gcc -o utils_test utils.c

kstrtest:
	gcc -o kstr_test kstr.c
