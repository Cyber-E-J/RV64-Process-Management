#include "defs.h"
#include "stdio.h"

extern struct sbiret sbi_call(uint64_t ext, uint64_t fid, uint64_t arg0,
                              uint64_t arg1, uint64_t arg2, uint64_t arg3,
                              uint64_t arg4, uint64_t arg5);

void put_num(uint64_t num) {
  // your code
  int i = 0;
  // uint64_t的范围是应该是0 - 18446744073709551615， 所以最多二十位数，加上最后的\0 最多需要21
  char r_str[21];
  char str[21];

  while(num>0){
    //获得反向的数列
    r_str[i++] = (num%10 + '0') ; //转换为ACII编码
    num = num/10; 
  }
  r_str[i] = '\0'; //末尾的string结束

  //数列取反
  int j=0;
  for(j=0;j<i;j++) str[j] = r_str[i-j-1];
  str[i] = '\0';
  puts(str);
  puts("\n");
  return 0;
}

int putchar(int ch) {
  sbi_call(1, 0, ch, 0, 0, 0, 0, 0);
  return 1;
}

int puts(const char* s) {
  while (*s) putchar(*s++);
}

static int vprintfmt(int (*putch)(int), const char* fmt, va_list vl) {
  int in_format = 0, longarg = 0;
  size_t pos = 0;
  for (; *fmt; fmt++) {
    if (in_format) {
      switch (*fmt) {
        case 'l': {
          longarg = 1;
          break;
        }

        case 'x': {
          long num = longarg ? va_arg(vl, long) : va_arg(vl, int);

          int hexdigits = 2 * (longarg ? sizeof(long) : sizeof(int)) - 1;
          for (int halfbyte = hexdigits; halfbyte >= 0; halfbyte--) {
            int hex = (num >> (4 * halfbyte)) & 0xF;
            char hexchar = (hex < 10 ? '0' + hex : 'a' + hex - 10);
            putch(hexchar);
            pos++;
          }
          longarg = 0;
          in_format = 0;
          break;
        }

        case 'd': {
          long num = longarg ? va_arg(vl, long) : va_arg(vl, int);
          if (num < 0) {
            num = -num;
            putch('-');
            pos++;
          }
          int bits = 0;
          char decchar[25] = {'0', 0};
          for (long tmp = num; tmp; bits++) {
            decchar[bits] = (tmp % 10) + '0';
            tmp /= 10;
          }

          for (int i = bits; i >= 0; i--) {
            putch(decchar[i]);
          }
          pos += bits + 1;
          longarg = 0;
          in_format = 0;
          break;
        }

        case 'u': {
          unsigned long num = longarg ? va_arg(vl, long) : va_arg(vl, int);
          int bits = 0;
          char decchar[25] = {'0', 0};
          for (long tmp = num; tmp; bits++) {
            decchar[bits] = (tmp % 10) + '0';
            tmp /= 10;
          }

          for (int i = bits; i >= 0; i--) {
            putch(decchar[i]);
          }
          pos += bits + 1;
          longarg = 0;
          in_format = 0;
          break;
        }

        case 's': {
          const char* str = va_arg(vl, const char*);
          while (*str) {
            putch(*str);
            pos++;
            str++;
          }
          longarg = 0;
          in_format = 0;
          break;
        }

        case 'c': {
          char ch = (char)va_arg(vl, int);
          putch(ch);
          pos++;
          longarg = 0;
          in_format = 0;
          break;
        }
        default:
          break;
      }
    } else if (*fmt == '%') {
      in_format = 1;
    } else {
      putch(*fmt);
      pos++;
    }
  }
  return pos;
}

int printf(const char* s, ...) {
  int res = 0;
  va_list vl;
  va_start(vl, s);
  res = vprintfmt(putchar, s, vl);
  va_end(vl);
  return res;
}