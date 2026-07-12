/*
 정수 오버플로우의 실체를 눈으로 확인하는 프로그램.

**요구사항:**

- `char`, `short`, `int`, `long`, `unsigned int` 각 타입의 `sizeof`와 `INT_MAX` 등 한계값을 출력
- `unsigned int`에 -1을 대입했을 때 어떤 값이 나오는지 출력하고 그 이유를 주석으로 설명
- `signed char c = 127; c++;` 후 값을 출력 (오버플로우 발생 확인)

**통과 기준:** 본인 플랫폼에서 각 타입의 정확한 바이트 크기와 오버플로우 결과값을 설명할 수 있어야 함

*/


#include<limits.h>
#include<stdio.h>


int main(){

  // define unsigned int value 
  unsigned int x = -1;
  signed char c = 127;


  printf("CHAR_MAX: %d \n",CHAR_MAX);
  printf("INT_MAX: %d\n",INT_MAX);
  printf("SHRT_MAX: %d\n",SHRT_MAX);
  printf("LONG_MAX: %ld\n",LONG_MAX);
  printf("UINT_MAX: %u\n", UINT_MAX);

  printf("sizeof char: %zu \n",sizeof(char));
  printf("sizeof int: %zu \n",sizeof(int));
  printf("sizeof short : %zu \n",sizeof(short));
  printf("sizeof long : %zu \n",sizeof(long));
  printf("sizeof unsigned int : %zu \n",sizeof(unsigned int));

  printf("unsigned int value : %u\n",x);
  // unsigned int 의 범위안에 -1 이 없기때문에 오버플로우로 인해서 MAX값으로 전환된다!

  c++;


  printf("signed char c++ value : %d\n",c);


  return 0;
}
 
