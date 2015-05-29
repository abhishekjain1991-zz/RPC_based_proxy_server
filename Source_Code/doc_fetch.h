#include <unistd.h>
#include <sys/select.h>
#include <curl/curl.h>
#include <string>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <curl/curl.h>



struct wd_in {
  size_t size;
  size_t len;
  char *data;
};

std::string fetch_doc(std::string URL);
