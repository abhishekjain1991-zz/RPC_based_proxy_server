#!/bin/bash

for j in 128 256 512 1024 2048 4096 8192;
#for j in 1024 ;
do

	./RPCproxy_server $j & ./RPCproxy_client Payload1 && fg
done
