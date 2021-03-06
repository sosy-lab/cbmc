#include <string.h>

void * malloc(unsigned);

char * make_str() {
  unsigned short len;
  char * str;
  
  __CPROVER_assume(len > 0);
  str = malloc(len);
  __CPROVER_assume(__CPROVER_buffer_size(str) == len);
  str[len - 1] = '\0';
  __CPROVER_is_zero_string(str) = 1;
  __CPROVER_zero_string_length(str) = len - 1;

  return str;
}

int main(int argc, char* argv[]) {
  char dest[10];
  char * name;
  char * dest2;

  __CPROVER_assume(__CPROVER_buffer_size(dest)==10);
  dest2=malloc(10);
  __CPROVER_assume(__CPROVER_buffer_size(dest2)==10);
  name = make_str();
  __CPROVER_assume(strlen(name) < 10);

  strcpy(dest, name);
  assert(__CPROVER_is_zero_string(dest));
  
  strcpy(dest2, name);
  assert(__CPROVER_is_zero_string(dest2));

  return 0;
}

