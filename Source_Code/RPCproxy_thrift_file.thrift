#!/usr/local/bin/thrift --gen cpp

namespace cpp Test

service RPCproxy {
  string ping(1:string URL)
  i32 miss_count()
  i32 byte_count()
  void kill_server()
}
