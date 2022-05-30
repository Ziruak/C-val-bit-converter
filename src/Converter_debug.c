#include "Converter.h"
#include <stdio.h>

int main() {

  const size_t test_size = 5;
  int test_material[] = {0, 1, -1, 12345, -12345};
  char* res_str[] = {
      "00000000000000000000000000000000",
      "00000000000000000000000000000001",
      "11111111111111111111111111111111",
      "00000000000000000011000000111001",
      "11111111111111111100111111000111"
  };
  char converted[CONV_BUFF_SIZE];
  int converted_back;
  int convert_res;

  for (size_t i = 0; i < test_size; ++i) {
    convert_int_to_bytes(converted,test_material[i]);
    convert_res = convert_bytes_to_int(res_str[i],&converted_back);
    printf("RES: %d\nORIGINAL: [%d], CONVERTED: [%d]\n\n", convert_res,test_material[i],converted_back);
  }
    return 0;
}

//    
