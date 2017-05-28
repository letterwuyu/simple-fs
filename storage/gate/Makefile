CXX=g++
CXXFLAGS=-g -std=c++11 -Wall -pedantic

ImpDir=../../common/imp
NetDir=../../common/net
DBDir=../../common/db
LogDir=../../common/log4z

MongoDBComplie=-I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/mongocxx -lmongocxx -lbsoncxx

server: libevent_socket.o \
		libevent_network.o \
		common_thread.o \
		common_package.o \
		package_analysis.o \
		mongodb_manager.o \
		mongodb_cxx_manager.o \
		log4z.o \
		gate_event.o \
		gate_server.o \
		storage_manager.o \
		virtual_volume.o \
		virtual_volume_manager.o \
		main.o
	$(CXX) $(CXXFLAGS) libevent_socket.o \
					   libevent_network.o \
					   common_thread.o  \
                       common_package.o \
					   package_analysis.o \
					   mongodb_manager.o \
					   mongodb_cxx_manager.o \
					   log4z.o \
					   gate_event.o \
                       gate_server.o \
                       storage_manager.o \
					   virtual_volume.o \
                       virtual_volume_manager.o \
                       main.o \
                       -o server -levent -lpthread $(MongoDBComplie)
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
mongodb_cxx_manager.o: $(DBDir)/mongodb_cxx_manager.cc $(DBDir)/mongodb_cxx_manager.h
	$(CXX) $(CXXFLAGS) -c $(DBDir)/mongodb_cxx_manager.cc $(MongoDBComplie)
log4z.o: $(LogDir)/log4z.cc $(LogDir)/log4z.h
	$(CXX) $(CXXFLAGS) -c $(LogDir)/log4z.cc
gate_event.o: gate_event.cc gate_event.h
	$(CXX) $(CXXFLAGS) -c gate_event.cc
gate_server.o: gate_server.cc gate_server.h
	$(CXX) $(CXXFLAGS) -c gate_server.cc
storage_manager.o: storage_manager.cc storage_manager.h
	$(CXX) $(CXXFLAGS) -c storage_manager.cc
virtual_volume.o: virtual_volume.cc virtual_volume.h
	$(CXX) $(CXXFLAGS) -c virtual_volume.cc
virtual_volume_manager.o: virtual_volume_manager.cc virtual_volume_manager.h
	$(CXX) $(CXXFLAGS) -c virtual_volume_manager.cc $(MongoDBComplie)
common_package.o: $(NetDir)/common_package.cc $(NetDir)/common_package.h
	$(CXX) $(CXXFLAGS) -c $(NetDir)/common_package.cc
clean:
	rm *.o server

