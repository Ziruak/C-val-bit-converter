#include <check.h>

#include "Converter.h"

START_TEST(char_test) {
  const size_t test_size = 4;
  char test_material[] = {'a', ' ', '0', '\t'};
  char* res_str[] = {
      "01100001",
      "00100000",
      "00110000",
      "00001001"
  };
  char converted[CONV_BUFF_SIZE];
  char converted_back;
  int convert_res;

  for (size_t i = 0; i < test_size; ++i) {
    convert_char_to_bytes(converted,test_material[i]);
    ck_assert_str_eq(converted,res_str[i]);
    convert_res = convert_bytes_to_char(res_str[i],&converted_back);
    ck_assert(convert_res);
    ck_assert(test_material[i]==converted_back);
  }
}
END_TEST

START_TEST(int_test) {
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
    ck_assert_str_eq(converted,res_str[i]);
    convert_res = convert_bytes_to_int(res_str[i],&converted_back);
    ck_assert(convert_res);
    ck_assert(test_material[i]==converted_back);
  }
}
END_TEST

START_TEST(uint_test) {
  const size_t test_size = 5;
  unsigned int test_material[] = {0u, 1u, 4294967295u, 12345u, 4294954951u};
  char* res_str[] = {
      "00000000000000000000000000000000",
      "00000000000000000000000000000001",
      "11111111111111111111111111111111",
      "00000000000000000011000000111001",
      "11111111111111111100111111000111"
  };
  char converted[CONV_BUFF_SIZE];
  unsigned int converted_back;
  int convert_res;

  for (size_t i = 0; i < test_size; ++i) {
    convert_uint_to_bytes(converted,test_material[i]);
    ck_assert_str_eq(converted,res_str[i]);
    convert_res = convert_bytes_to_uint(res_str[i],&converted_back);
    ck_assert(convert_res);
    ck_assert(test_material[i]==converted_back);
  }
}
END_TEST

START_TEST(long_test) {
  const size_t test_size = 7;
  long test_material[] = {0l, 1l, -1l, 12345l, -12345l, 1343563543853214l, -1343563543853214l};
  char* res_str[] = {
      "0000000000000000000000000000000000000000000000000000000000000000",
      "0000000000000000000000000000000000000000000000000000000000000001",
      "1111111111111111111111111111111111111111111111111111111111111111",
      "0000000000000000000000000000000000000000000000000011000000111001",
      "1111111111111111111111111111111111111111111111111100111111000111",
      "0000000000000100110001011111011011000011110000111011100010011110",
      "1111111111111011001110100000100100111100001111000100011101100010"
  };
  char converted[CONV_BUFF_SIZE];
  long converted_back;
  int convert_res;

  for (size_t i = 0; i < test_size; ++i) {
    convert_ulong_to_bytes(converted,test_material[i]);
    ck_assert_str_eq(converted,res_str[i]);
    convert_res = convert_bytes_to_long(res_str[i],&converted_back);
    ck_assert(convert_res);
    ck_assert(test_material[i]==converted_back);
  }
}
END_TEST

START_TEST(ulong_test) {
  const size_t test_size = 7;
  unsigned long test_material[] = {0ul, 1ul, 18446744073709551615ul, 12345ul, 18446744073709539271ul, 1343563543853214ul, 18445400510165698402ul};
  char* res_str[] = {
      "0000000000000000000000000000000000000000000000000000000000000000",
      "0000000000000000000000000000000000000000000000000000000000000001",
      "1111111111111111111111111111111111111111111111111111111111111111",
      "0000000000000000000000000000000000000000000000000011000000111001",
      "1111111111111111111111111111111111111111111111111100111111000111",
      "0000000000000100110001011111011011000011110000111011100010011110",
      "1111111111111011001110100000100100111100001111000100011101100010"
  };
  char converted[CONV_BUFF_SIZE];
  unsigned long converted_back;
  int convert_res;

  for (size_t i = 0; i < test_size; ++i) {
    convert_long_to_bytes(converted,test_material[i]);
    ck_assert_str_eq(converted,res_str[i]);
    convert_res = convert_bytes_to_ulong(res_str[i],&converted_back);
    ck_assert(convert_res);
    ck_assert(test_material[i]==converted_back);
  }
}
END_TEST

START_TEST(float_test) {
  const size_t test_size = 5;
  float test_material[] = {0.f, 1.f, -1.f, 2e-34f, -2e+34f, 1.f/0.f, -1.f/0.f, 0.f/0.f};
  char* res_str[] = {
      "00000000000000000000000000000000",
      "00111111100000000000000000000000",
      "10111111100000000000000000000000",
      "00000111100001001110110000111101",
      "11111000011101101000010011011111",
      "01111111100000000000000000000000",
      "11111111100000000000000000000000",
      "01111111110000000000000000000000"

  };
  char converted[CONV_BUFF_SIZE];
  float converted_back;
  int convert_res;

  for (size_t i = 0; i < test_size; ++i) {
    convert_float_to_bytes(converted,test_material[i]);
    ck_assert_str_eq(converted,res_str[i]);
    convert_res = convert_bytes_to_float(res_str[i],&converted_back);
    ck_assert(convert_res);
    if (test_material[i] == test_material[i]) {
    ck_assert_float_eq_tol(test_material[i],converted_back,1e-6);
    } else {
      ck_assert_float_nan(converted_back);
    }
  }
}
END_TEST

START_TEST(double_test) {
  const size_t test_size = 5;
  double test_material[] = {0., 1., -1., 2e-304, -2e+304, 1./0., -1./0., 0./0.};
  char* res_str[] = {
      "0000000000000000000000000000000000000000000000000000000000000000",
      "0011111111110000000000000000000000000000000000000000000000000000",
      "1011111111110000000000000000000000000000000000000000000000000000",
      "0000000011100001100011100011101110011011001101110100000101101001",
      "1111111100011101001010100001101111100100000001001000111110010000",
      "0111111111110000000000000000000000000000000000000000000000000000",
      "1111111111110000000000000000000000000000000000000000000000000000",
      "1111111111111000000000000000000000000000000000000000000000000000"

  };
  char converted[CONV_BUFF_SIZE];
  double converted_back;
  int convert_res;

  for (size_t i = 0; i < test_size; ++i) {
    convert_double_to_bytes(converted,test_material[i]);
    ck_assert_str_eq(converted,res_str[i]);
    convert_res = convert_bytes_to_double(res_str[i],&converted_back);
    ck_assert(convert_res);
    if (test_material[i] == test_material[i]) {
    ck_assert_double_eq_tol(test_material[i],converted_back,1e-8);
    } else {
      ck_assert_double_nan(converted_back);
    }
  }
}
END_TEST

int main(void) {
  Suite *coverter_s = suite_create("calculator");

  TCase *tc_int_tests = tcase_create("integer_tests"),
        *tc_float_tests = tcase_create("float_tests");

  SRunner *sr = srunner_create(coverter_s);

  suite_add_tcase(coverter_s, tc_int_tests);
  tcase_add_test(tc_int_tests, char_test);
  tcase_add_test(tc_int_tests,int_test);
  tcase_add_test(tc_int_tests,uint_test);
  tcase_add_test(tc_int_tests,long_test);
  tcase_add_test(tc_int_tests,ulong_test);
 

  suite_add_tcase(coverter_s, tc_float_tests);
  tcase_add_test(tc_float_tests,float_test);
  tcase_add_test(tc_float_tests,double_test);

  srunner_run_all(sr, CK_ENV);
  srunner_ntests_failed(sr);
  srunner_free(sr);

  return 0;
}