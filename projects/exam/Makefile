subdir = ./  
  
export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
  
SOURCES = $(wildcard $(subdir)*.cc)  
SRCOBJS = $(patsubst %.cc,%.o,$(SOURCES))  
CC = g++  
  
%.o:%.cc  
	$(CC) -std=c++11 -I/usr/local/include -pthread -c $< -o $@  
  
all: client server  
  
client: example.grpc.pb.o example.pb.o client.o  
	$(CC) $^ -L/usr/local/lib `pkg-config --libs grpc++ grpc` -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -lprotobuf -lpthread -ldl  -o $@  
  
server: example.grpc.pb.o example.pb.o server.o  
	$(CC) $^ -L/usr/local/lib `pkg-config --libs grpc++ grpc` -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -lprotobuf -lpthread -ldl  -o $@  
#chmod 777 $@  
  
clean:  
	sudo rm *.o
