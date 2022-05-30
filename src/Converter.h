#ifndef CONVERTER_H
#define CONVERTER_H

#define CONV_BUFF_SIZE 256

union converter_union {
double DOUBLE;
char CHAR;
int INT;
long LONG;
float FLOAT;
unsigned char BYTES[8];
};

typedef enum cur_type {
    CONV_DOUBLE,
    CONV_CHAR,
    CONV_INT,
    CONV_LONG,
    CONV_FLOAT
} convert_type;

char* convert_char_to_bytes(char* dest, char c);
char* convert_int_to_bytes(char* dest, int i);
char* convert_uint_to_bytes(char* dest, unsigned int ui);
char* convert_long_to_bytes(char* dest, long l);
char* convert_ulong_to_bytes(char* dest, unsigned long ul);
char* convert_float_to_bytes(char* dest, float f);
char* convert_double_to_bytes(char* dest, double d);

int convert_bytes_to_char(const char* src, char* c);
int convert_bytes_to_int(const char* src, int* i);
int convert_bytes_to_uint(const char* src, unsigned int* ui);
int convert_bytes_to_long(const char* src, long* l);
int convert_bytes_to_ulong(const char* src, unsigned long* ul);
int convert_bytes_to_float(const char* src, float* f);
int convert_bytes_to_double(const char* src, double* d);


#endif