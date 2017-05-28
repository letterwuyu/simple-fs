mongodb_complie=-I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/mongocxx -lmongocxx -lbsoncxx
server: main.o mongodb_cxx_manager.o mongodb_manager.o log4z.o
	g++ -std=c++11 main.o mongodb_cxx_manager.o mongodb_manager.o log4z.o -o server $(mongodb_complie)
main.o: main.cc
	g++ -std=c++11 -c main.cc -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/mongocxx -lmongocxx -lbsoncxx
mongodb_cxx_manager.o: mongodb_cxx_manager.cc
	g++ -std=c++11 -c mongodb_cxx_manager.cc -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/mongocxx -lmongocxx -lbsoncxx
mongodb_manager.o: mongodb_manager.cc
	g++ -std=c++11 -c mongodb_manager.cc -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/mongocxx -lmongocxx -lbsoncxx
log4z.o: ../log4z/log4z.cc ../log4z/log4z.h
	g++ -std=c++11 -c ../log4z/log4z.cc
clean:
	rm *.o server
