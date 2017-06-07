CXX=g++
CXXFLAGS=-g -std=c++11 -Wall -pedantic

ImpDir=../../common/imp
NetDir=../../common/net
LogDir=../../common/log4z

simple_fs: simple_fs.o \
		libevent_network.o \
        libevent_socket.o \
        cxx_thread.o \
        common_package.o \
        package_analysis.o \
        log4z.o \
        client_event.o \
        client_network.o
	$(CXX) $(CXXFLAGS) simple_fs.o \
                       libevent_network.o \
                       libevent_socket.o \
                       cxx_thread.o \
                       common_package.o \
                       package_analysis.o \
                       log4z.o \
                       client_event.o \
                       client_network.o \
                       -o simple_fs -levent -lpthread
lient: main.o \
		libevent_network.o \
		libevent_socket.o \
        cxx_thread.o \
        common_package.o \
        package_analysis.o \
        log4z.o \
        client_event.o \
        client_network.o
	$(CXX) $(CXXFLAGS) main.o \
                       libevent_network.o \
					   libevent_socket.o \
                       cxx_thread.o \
                       common_package.o \
                       package_analysis.o \
                       log4z.o \
                       client_event.o \
                       client_network.o \
                       -o client -levent -lpthread
main.o: main.cc
	$(CXX) $(CXXFLAGS) -c main.cc
simple_fs.o: simple_fs.cc
	$(CXX) $(CXXFLAGS) -c simple_fs.cc
libevent_network.o: $(NetDir)/libevent_network.cc
	$(CXX) $(CXXFLAGS) -c $(NetDir)/libevent_network.cc
libevent_socket.o: $(NetDir)/libevent_socket.cc
	$(CXX) $(CXXFLAGS) -c $(NetDir)/libevent_socket.cc
cxx_thread.o: $(ImpDir)/cxx_thread.cc
	$(CXX) $(CXXFLAGS) -c $(ImpDir)/cxx_thread.cc
common_package.o: $(NetDir)/common_package.cc
	$(CXX) $(CXXFLAGS) -c $(NetDir)/common_package.cc
package_analysis.o: $(NetDir)/package_analysis.cc
	$(CXX) $(CXXFLAGS) -c $(NetDir)/package_analysis.cc
log4z.o: $(LogDir)/log4z.cc
	$(CXX) $(CXXFLAGS) -c $(LogDir)/log4z.cc
client_event.o: client_event.cc
	$(CXX) $(CXXFLAGS) -c client_event.cc
client_network.o: client_network.cc
	$(CXX) $(CXXFLAGS) -c client_network.cc
clean:
	rm *.o client
