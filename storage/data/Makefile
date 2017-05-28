CXX=g++
CXXFLAGS=-g -std=c++11 -Wall -pedantic

ImpDir=../../common/imp
NetDir=../../common/net
DBDir=../../common/db
LogDir=../../common/log4z

MongoDBComplie=-I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/mongocxx -lmongocxx -lbsoncxx

server: main.o \
		libevent_network.o \
		libevent_socket.o \
		common_thread.o \
		package_analysis.o \
		mongodb_manager.o \
		mongodb_cxx_manager.o \
		leveldb_manager.o \
		log4z.o \
		data_event.o \
		data_server.o \
        unit.o \
		unit_manager.o \
		volume.o \
		volume_manager.o \
        common_package.o
	$(CXX) $(CXXFLAGS) main.o \
					   libevent_network.o \
					   libevent_socket.o \
                       common_thread.o \
                       package_analysis.o \
                       mongodb_manager.o \
                       mongodb_cxx_manager.o \
					   leveldb_manager.o \
                       log4z.o \
                       data_event.o \
                       data_server.o \
					   unit.o \
                       unit_manager.o \
                       volume.o \
                       volume_manager.o \
                       common_package.o \
					   -o server -levent -lpthread $(MongoDBComplie) -lleveldb
main.o: main.cc
	$(CXX) $(CXXFLAGS) -c main.cc
libevent_network.o: $(NetDir)/libevent_network.cc $(NetDir)/libevent_network.h
	$(CXX) $(CXXFLAGS) -c $(NetDir)/libevent_network.cc
libevent_socket.o: $(NetDir)/libevent_socket.cc $(NetDir)/libevent_socket.h
	$(CXX) $(CXXFLAGS) -c $(NetDir)/libevent_socket.cc
common_thread.o: $(ImpDir)/common_thread.cc $(ImpDir)/common_thread.h
	$(CXX) $(CXXFLAGS) -c $(ImpDir)/common_thread.cc -lpthread
package_analysis.o: $(NetDir)/package_analysis.cc $(NetDir)/package_analysis.h
	$(CXX) $(CXXFLAGS) -c $(NetDir)/package_analysis.cc

mongodb_manager.o: $(DBDir)/mongodb_manager.cc $(DBDir)/mongodb_manager.h
	$(CXX) -std=c++11 -c $(DBDir)/mongodb_manager.cc $(MongoDBComplie)
mongodb_cxx_manager.o: $(DBDir)/mongodb_cxx_manager.cc
	$(CXX) -std=c++11 -c $(DBDir)/mongodb_cxx_manager.cc $(MongoDBComplie)
leveldb_manager.o: $(DBDir)/leveldb_manager.cc $(DBDir)/leveldb_manager.h
	$(CXX) -std=c++11 -c $(DBDir)/leveldb_manager.cc -lleveldb
log4z.o: $(LogDir)/log4z.cc $(LogDir)/log4z.h
	$(CXX) $(CXXFLAGS) -c $(LogDir)/log4z.cc
data_event.o: data_event.cc data_event.h
	$(CXX) $(CXXFLAGS) -c data_event.cc
data_server.o: data_server.cc data_server.h
	$(CXX) $(CXXFLAGS) -c data_server.cc
unit.o: unit.cc unit.h
	$(CXX) $(CXXFLAGS) -c unit.cc
unit_manager.o: unit_manager.cc unit_manager.h
	$(CXX) $(CXXFLAGS) -c unit_manager.cc
volume.o: volume.cc volume.h $(DBDir)/mongodb_cxx_manager.h 
	$(CXX) -std=c++11 -c volume.cc $(MongoDBComplie)
volume_manager.o: volume_manager.cc volume_manager.h
	$(CXX) $(CXXFLAGS) -c volume_manager.cc
common_package.o: $(NetDir)/common_package.cc $(NetDir)/common_package.h
	$(CXX) $(CXXFLAGS) -c $(NetDir)/common_package.cc
clean:
	rm *.o server

