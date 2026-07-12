/*
 문제 1-2. 진법 변환기 (사칙연산 없이)

정수를 입력받아 2진수, 8진수, 16진수로 출력하는 프로그램. `printf`의 `%x`, `%o` 포맷 지정자는 사용 금지 — 비트 연산으로 직접 구현.

**요구사항:**

- 함수 시그니처: `void print_binary(unsigned int n);`
- 비트 연산자(`&`, `>>`, `<<`)만 사용
- 32비트 전체를 출력 (앞자리 0 포함)

**통과 기준:** `print_binary(5)` → `00000000000000000000000000000101`

 * */

#include<stdio.h>




void print_binary(unsigned int n){
 
  // char bits[33];
  // bits[32] = '\0';


  for (int i = 0; i <= 31; i++) {
        // bits[i] = ((n >> (31 - i)) & 1) + '0';
      printf("%c",((n>>(31-i))&1)+'0'); 
    }

  printf("\n");
    // printf("bits: %s\n", bits);
}
//   for (int i=31;i>=0;i--){
//     printf("i :%d\n",i);
//     printf("n :%d\n",n);
//     if(n==0){
//       bits[i] = n;
//       printf("bits[i] : %d\n",n);
//     } 
//     if (n==1){
//       bits[i]=n;
//       printf("bits[i] : %d\n",n);
//       n=0;
//     }
//
//     bits[i] = n%2;
//     printf("bits[i] : %d\n",n%2);
//
//     n = n/2;
//   } 
//   printf("\n");
//
//   printf("bits : %s",bits);
//
//   printf("\n");
// }
//
int main(){
  unsigned int n =0;
  printf("input value: ");
  scanf("%u",&n);


  print_binary(n);




  return 0;
}

