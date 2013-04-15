CC = g++

all:qdict

qdict:main.o utils.o network.o db.o
	$(CC) -o qdict main.o utils.o network.o db.o -g -I/usr/local/include -L/usr/local/lib -lcurl -D_THREAD_SAFE -D_REENTRANT -I/usr/local/include -L/usr/local/lib -lmxml -ldb_cxx -lpthread -Wall

main.o:qdict.cpp qdict.h global.h
	$(CC) -c qdict.cpp -o main.o

utils.o:utils.cpp utils.h global.h
	$(CC) -c utils.cpp -o utils.o
	

network.o:network.cpp network.h global.h
	$(CC) -c network.cpp -o network.o

db.o:db.cpp db.h global.h
	$(CC) -c db.cpp -o db.o

clean:
	rm -r -f *~
	rm -r -f *.o

cleandb:
	rm -r -f *.db

statistic:
	find -name "*.H" -or -name "*.cpp" -or -name "*.c" -or -name "*.h" | xargs wc -l

dbtest:
	g++ db.cpp -ldb_cxx utils.o -o db_test
