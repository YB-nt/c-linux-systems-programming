/*
1~50번 학생에 대해 (학생 번호를 임의 조건으로 활용):
- 번호가 4의 배수면 "출석 우수"
- 번호가 6의 배수면 "과제 우수"
- 둘 다 해당하면 "모범생"
- 둘 다 아니면 "보통"

비트 플래그: attend = 1, homework = 2
switch로 분기
*/

#include<stdio.h>

#define ATTEND 1
#define HOMEWORK 2


int main(){

  for (int i=1;i<=50;i++){

    int flag =0;
    if (i%4==0) flag |=ATTEND;
    if (i%6==0) flag |=HOMEWORK;

    switch(flag){
      case 0:  printf("보통\n"); break;
      case 1: printf("출석 우수\n"); break;
      case 2: printf("과제우수\n"); break;
      case 3: printf("모범생\n"); break;
    }


  }
  return 0;

}



// 0000 0010
// 0000 0001
// 0000 0011
