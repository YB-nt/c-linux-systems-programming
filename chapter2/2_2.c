/*
**요구사항:**

- `arr[i]`와 `*(arr + i)`가 같은 값을 출력하는 것을 모든 인덱스에서 검증 - 값은 동일
- `&arr[i]`와 `arr + i`가 같은 주소인지 출력해서 확인 - 주소는 다르다
- 포인터를 하나 선언해서 `arr`를 순회하며 `*p++` 형태로 합계 계산하는 함수 작성

**통과 기준:** `sizeof(arr)`와 `sizeof(p)` (p는 `int*`)의 차이를 설명할 수 있어야 함 — 이게 포인터 vs 배열 함정의 핵심

 */


#include<stdio.h>

int sum_arr(int *arr,int len){

  int value = 0;
  
  printf("[인덱스별 비교]\n");
  for (int i =0;i<len;i++){ 
    printf("i=%d arr[%d]=%d, *(arr+%d)=%d, &arr[%d]=%p, (arr+%d)=%p\n"
             ,i
             ,i,arr[i]  
             ,i,*(arr+i)  
             ,i,&arr[i]
             ,i,(void*)&*(arr+i)
           );

    value += arr[i];
  }
  return value;
}



int main(){
  int arr[5] = {10, 20, 30, 40, 50};
  int *p=arr;
  int len = 5;
  int value = sum_arr(p,len);

  printf("\n[합계 검증]\n");
  printf("sum_via_pointer 결과: %d\n",value);
   

  printf("\n[sizeof 비교]\n");
  printf("sizeof(arr)=%d\n",(int)sizeof(arr));
  printf("sizeof(p)=%d\n",(int)sizeof(p));


  return 0;
}




