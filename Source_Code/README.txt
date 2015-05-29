The Makefile generates the server and the client side code.
If the URLs need to be modified, the file "random_urls.txt" will need to be modified.
1) The scripts Test_Payload1.sh and Test_Payload2.sh runs the client code for varying number of cache sizes.
These cache sizes vary from 128 to 8192 KB.
Eg: ./Test_Payload1.sh
The hit ratio and byte hit ratio are obtained at the end of varying sizes of cache and results are stored in a text file of similar name.
