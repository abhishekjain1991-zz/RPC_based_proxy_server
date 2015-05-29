GEN_SRC := RPCproxy.cpp RPCproxy_thrift_file_constants.cpp RPCproxy_thrift_file_types.cpp cache.cpp doc_fetch.cpp
GEN_OBJ := $(patsubst %.cpp,%.o, $(GEN_SRC))

THRIFT_DIR := /usr/local/include/thrift
BOOST_DIR := /usr/local/include

INC := -I$(THRIFT_DIR) -I$(BOOST_DIR)

.PHONY: all clean

all: RPCproxy_server RPCproxy_client

%.o: %.cpp
	$(CXX) -Wall -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H $(INC) -std=c++11 -c $< -o $@ -lcurl

RPCproxy_server: RPCproxy_server.o $(GEN_OBJ)
	$(CXX) $^ -o $@ -L/usr/local/lib -lthrift -lcurl

RPCproxy_client: RPCproxy_client.o $(GEN_OBJ)
	$(CXX) $^  -o $@ -L/usr/local/lib -lthrift -lcurl

clean:
	$(RM) *.o RPCproxy_server RPCproxy_client
