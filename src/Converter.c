#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "Converter.h"

union converter_union converter_u;


unsigned char* convert_to_bin_str(uint64_t num,unsigned char* dest) {
    dest[0] = '\0';
    unsigned char tmp[64];
    size_t lastidx = 64;
    while (num) {
        tmp[lastidx-1] = '0' + (num & 1);
        num = num >> 1u;
        lastidx--;
    }
    if (lastidx < 64) {
    for (size_t i = 0; lastidx + i < 64; ++i) {
        dest[i] = tmp[lastidx+i];
    }
    dest[64-lastidx] = '\0';
    } else {
        dest[0]= '0';
        dest[1]='\0';
    }
    return dest;
 }

unsigned char* convert_to_bytes(unsigned char* dest, convert_type type) {
    size_t cpy_count = 0;
    switch (type) {
        case CONV_CHAR:
            cpy_count = sizeof(char);
            break;
        case CONV_INT:
            cpy_count = sizeof(int);
            break;
        case CONV_LONG:
            cpy_count = sizeof(long);
            break;
        case CONV_FLOAT:
            cpy_count = sizeof(float);
            break;
        case CONV_DOUBLE:
            cpy_count = sizeof(double);
            break;
    }
    dest[0] = '\0';
    for (int i = cpy_count-1; i >= 0; --i) {
        unsigned char byte[9],byte_with_nulls[9];
        convert_to_bin_str(converter_u.BYTES[i],byte);
        snprintf((char*)byte_with_nulls,9, "%8s", byte);
        for (size_t k = 0; k < 9; ++k) if(byte_with_nulls[k] == ' ') byte_with_nulls[k] = '0';
        strncat((char*)dest,(char*)byte_with_nulls,CONV_BUFF_SIZE);
    }
    return dest;
}

unsigned char get_byte(const unsigned char* src) {
    unsigned char res  = 0;
    for (int i = 0; i < 8; ++i) {
        res += (src[i] - '0') << (7 - i);
    }
    return res;
}

int convert_from_bytes(const unsigned char* src, convert_type type) {
    int res = 0;
    size_t cpy_count = 0;
    unsigned char tmp[8];
    switch (type) {
        case CONV_CHAR:
            cpy_count = sizeof(char);
            break;
        case CONV_INT:
            cpy_count = sizeof(int);
            break;
        case CONV_LONG:
            cpy_count = sizeof(long);
            break;
        case CONV_FLOAT:
            cpy_count = sizeof(float);
            break;
        case CONV_DOUBLE:
            cpy_count = sizeof(double);
            break;
    }
    if (strlen((const char*)src) == cpy_count*8 && cpy_count) {
        res = 1;
        for (size_t i=0; i < cpy_count*8 && res; ++i) {
            if (src[i] != '0' && src[i] != '1') res = 0;
        }
        for (size_t i = 0; i < cpy_count && res; ++i) {
            tmp[cpy_count-i-1] = get_byte(src);
            src+=8;
        }
        if (res) memcpy(converter_u.BYTES,tmp,cpy_count);
    }
    return res;
}

char* convert_char_to_bytes(char* dest, char c) {
    converter_u.CHAR = c;
    convert_to_bytes((unsigned char*)dest,CONV_CHAR);
    return dest;
}

char* convert_int_to_bytes(char* dest, int i) {
    converter_u.INT = i;
    convert_to_bytes((unsigned char*)dest,CONV_INT);
    return dest;
}

char* convert_long_to_bytes(char* dest, long l) {
    converter_u.LONG = l;
    convert_to_bytes((unsigned char*)dest,CONV_LONG);
    return dest;
}

char* convert_float_to_bytes(char* dest, float f) {
    converter_u.FLOAT = f;
    convert_to_bytes((unsigned char*)dest,CONV_FLOAT);
    return dest;
}

char* convert_double_to_bytes(char* dest, double d) {
    converter_u.DOUBLE = d;
    convert_to_bytes((unsigned char*)dest,CONV_DOUBLE);
    return dest;
}

char* convert_uint_to_bytes(char* dest, unsigned int ui) {
    converter_u.INT = (int)ui;
    convert_to_bytes((unsigned char*)dest,CONV_INT);
    return dest;
}
char* convert_ulong_to_bytes(char* dest, unsigned long ul) {
    converter_u.LONG = (long)ul;
    convert_to_bytes((unsigned char*)dest,CONV_LONG);
    return dest;
}

int convert_bytes_to_char(const char* src, char* c) {
    int res = convert_from_bytes((unsigned char*)src,CONV_CHAR);
    if (res) *c=converter_u.CHAR;
    return res;
}
int convert_bytes_to_int(const char* src, int* i) {
    int res = convert_from_bytes((unsigned char*)src,CONV_INT);
    if (res) *i=converter_u.INT;
    return res;
}
int convert_bytes_to_long(const char* src, long* l) {
    int res = convert_from_bytes((unsigned char*)src,CONV_LONG);
    if (res) *l=converter_u.LONG;
    return res;
}

int convert_bytes_to_float(const char* src, float* f) {
    int res = convert_from_bytes((unsigned char*)src,CONV_FLOAT);
    if (res) *f=converter_u.FLOAT;
    return res;
}

int convert_bytes_to_double(const char* src, double* d) {
    int res = convert_from_bytes((unsigned char*)src,CONV_DOUBLE);
    if (res) *d=converter_u.DOUBLE;
    return res;
}

int convert_bytes_to_uint(const char* src, unsigned int* ui) {
    int res = convert_from_bytes((unsigned char*)src,CONV_INT);
    if (res) *ui=(unsigned int)converter_u.INT;
    return res;
}
int convert_bytes_to_ulong(const char* src, unsigned long* ul) {
    int res = convert_from_bytes((unsigned char*)src,CONV_LONG);
    if (res) *ul=(unsigned long)converter_u.LONG;
    return res;
}
