/*
문제 1-3. FizzBuzz 변형 — 비트마스크 버전

1~100까지 출력하되, 3의 배수면 "Fizz", 5의 배수면 "Buzz", 15의 배수면 "FizzBuzz".
단 `if-else` 체인 대신 비트 플래그(`fizz = 1, buzz = 2`)를 만들어서 `switch`로 처리.

**통과 기준:** 표준 FizzBuzz와 출력 동일, 단 분기 로직이 switch 기반이어야 함
*/



#include<stdio.h>

int main(){

  unsigned int fizz = 1;
  unsigned int bizz =2;


  for (int i = 1; i <= 100; i++) {
      int flag = 0;

      if (i % 3 == 0) flag |= fizz;   // fizz 비트 켜기
      if (i % 5 == 0) flag |= bizz;   // buzz 비트 켜기

      switch (flag) {
          case 0:                  // 둘 다 아님
              printf("%d\n", i);
              break;
          case 1:                  // fizz만
              printf("Fizz\n");
              break;
          case 2:                  // buzz만
              printf("Buzz\n");
              break;
          case 3:                  // fizz + buzz
              printf("FizzBuzz\n");
              break;
      }
  }

}
