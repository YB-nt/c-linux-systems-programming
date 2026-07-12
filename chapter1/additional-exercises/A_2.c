/*
1~100까지 출력하되:
- 3의 배수면 "A"
- 5의 배수면 "B"
- 7의 배수면 "C"
- 여러 개 해당하면 순서대로 이어붙여 출력 (예: "AB", "ABC")
- 아무것도 해당 안 되면 숫자 그대로 출력

비트 플래그: flag_a = 1, flag_b = 2, flag_c = 4
switch로 분기 (case가 몇 개나 필요할지 직접 계산해보기)
*/



#include<stdio.h>

#define FLAG_A 1
#define FLAG_B 2
#define FLAG_C 4


int main(){

  for (int i=1; i<=100;i++){
    int flag =0;
    if (i%4==0) flag |= FLAG_A; 
    if (i%5==0) flag |= FLAG_B;
    if (i%7==0) flag |= FLAG_C;


    switch(flag){
      case 0: printf("%d\n",i); break;
      case 1: printf("A\n"); break;
      case 2: printf("B\n"); break;
      case 3: printf("AB\n"); break;
      case 4: printf("C\n"); break;
      case 5: printf("AC\n"); break;
      case 6: printf("BC\n"); break;
      case 7: printf("ABC\n"); break;

    }

  }

  return 0;
}

// 0000 0001 1
// 0000 0010 2
// 0000 0011 3
// 0000 0110 6
// 0000 0101 5
// 0000 0100 4
// 0000 0111 7
