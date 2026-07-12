
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<limits.h>

int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);

int calculate(int a, int b, char op);   // op: '+', '-', '*'


int main(){

  printf("3 + 4 = %d\n", calculate(3, 4, '+'));
  printf("10 - 6 = %d\n", calculate(10, 6, '-'));
  printf("5 * 6 = %d\n", calculate(5, 6, '*'));

  int result = calculate(1, 2, '%');   // 지원하지 않는 연산자
                                       //
  if (result == INT_MIN) {
      printf("잘못된 연산자입니다.\n");
  }else
   printf("result : %d\n",result);

  return 0;
}


int add(int a,int b){
  return a+b;
}

int sub(int a,int b){
  return a-b;
}

int mul(int a,int b){
  return a*b;
}


int calculate(int a, int b,char op){

  int(*fp)(int,int)=NULL;

  switch (op)
  {
    case '+': fp = add;
              break;
    case '-': fp = sub;
              break;
    case '*': fp = mul;
              break;
    default:
              return INT_MIN;
  }
  
  return fp(a,b);
  
}
