#include "defs.h"


extern struct sbiret sbi_call(uint64_t ext, uint64_t fid, uint64_t arg0,
                              uint64_t arg1, uint64_t arg2, uint64_t arg3,
                              uint64_t arg4, uint64_t arg5);

int puts(char *str) {
  int i = 0;

  while(str[i]!='\0'){
    sbi_call(1,0,str[i],0,0,0,0,0);
    i++;
  }
  return 0;
}

int put_num(uint64_t n) {

  int i = 0;
  // uint64_t的范围是应该是0 - 18446744073709551615， 所以最多二十位数，加上最后的\0 最多需要21
  char r_str[21];
  char str[21];

  while(n>0){
    //获得反向的数列
    r_str[i++] = (n%10 + '0') ; //转换为ACII编码
    n = n/10; 
  }
  r_str[i] = '\0'; //末尾的string结束



  //数列取反
  int j=0;
  for(j=0;j<i;j++) str[j] = r_str[i-j-1];
  str[i] = '\0';

  /* for debug */

  //puts("test: in put_num , before put str\n");
  //puts(r_str);


  puts(str);
  puts("\n");

  /* for debug */

  //puts("test: in put_num , after put str\n");

  return 0;
}