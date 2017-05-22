CXX=g++
CXXFLAGS=-g -std=c++11 -Wall -pedantic
NetDir=../imp
server: libevent_network.o libevent_socket.o common_thread.o package_analysis.o main.o
	$(CXX) $(CXXFLAGS) libevent_network.o libevent_socket.o $(NetDir)/common_thread.o package_analysis.o main.o -o server -levent -lpthread
main.o: main.cc
	$(CXX) $(CXXFLAGS) -c main.cc
libevent_nerwork.o: libevent_network.cc libevent_network.h
	$(CXX) $(CXXFLAGS) -c libevent_network.cc
libevent_socket.o: libevent_socket.cc libevent_socket.h
	$(CXX) $(CXXFLAGS) -c libevent_socket.cc
common_thread.o: $(NetDir)/common_thread.cc $(NetDir)/common_thread.h
	$(CXX) $(CXXFLAGS) -c $(NetDir)/common_thread.cc -lpthread
package_analysis.o: package_analysis.cc package_analysis.h
	$(CXX) $(CXXFLAGS) -c package_analysis.cc
clean:
	rm *.o server
