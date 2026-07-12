/*
문제 2-1. 포인터로 swap 구현 (값 vs 주소 체감)

**요구사항:**

- 두 버전 모두 구현하고 `main`에서 둘 다 호출
- 각 호출 전후로 원본 변수 값을 출력해서 차이를 직접 확인
- 왜 `swap_wrong`이 실패하는지 스택 프레임 관점에서 주석 작성

*/

#include <stdio.h>

void swap_wrong(int a, int b);   // 값 전달 — 실패해야 함
void swap_right(int *a, int *b); // 포인터 전달 — 성공해야 함

int main() {
    int a = 10, b = 20;

    int *ptr_a, *ptr_b;
    ptr_a = &a;
    ptr_b = &b;

    printf("=== swap_wrong 호출 전 ===\n");
    printf("a: %d, b: %d\n\n", a, b);

    swap_wrong(a, b);

    printf("=== swap_wrong 호출 후 (원본 확인) ===\n");
    printf("a: %d, b: %d\n\n", a, b);   // 값 그대로 → 실패 확인

    printf("=== swap_right 호출 전 ===\n");
    printf("a: %d, b: %d\n\n", a, b);

    swap_right(ptr_a, ptr_b);

    printf("=== swap_right 호출 후 (원본 확인) ===\n");
    printf("a: %d, b: %d\n\n", a, b);   // 값이 바뀜 → 성공 확인

    return 0;
}

void swap_wrong(int a, int b) {
    // a, b는 main의 a, b와 이름만 같을 뿐 완전히 별개의 지역 변수.
    // 함수 호출 시 값이 "복사"되어 이 함수만의 새로운 스택 프레임에 저장됨.
    // 즉 main 스택 프레임의 a(0x1000), b(0x1004)와
    //    swap_wrong 스택 프레임의 a(0x2000), b(0x2004)는 서로 다른 메모리.
    // 아래에서 a, b를 아무리 바꿔도 0x2000, 0x2004만 바뀔 뿐,
    // 함수가 리턴하며 이 스택 프레임 자체가 소멸되므로 원본(main의 a, b)은 영향 없음.
    int temp = a;
    a = b;
    b = temp;

    printf("swap_wrong 내부\n");
    printf("a: %d (주소: %p)\n", a, (void*)&a);
    printf("b: %d (주소: %p)\n\n", b, (void*)&b);
}

void swap_right(int *a, int *b) {
    // a, b는 여전히 "포인터 변수의 복사본"이라 swap_wrong과 마찬가지로
    // 이 함수만의 새 스택 프레임에 저장됨 (주소 자체는 다름).
    // 하지만 그 안에 담긴 "내용물"은 main의 a, b가 있는 실제 주소값.
    // *a, *b로 그 주소를 역참조하면 main 스택 프레임의 메모리를 직접 수정하게 됨.
    // 따라서 함수가 끝나도 원본(main의 a, b)에 변경이 그대로 남음.
    int temp = *a;
    *a = *b;
    *b = temp;

    printf("swap_right 내부\n");
    printf("a가 가리키는 값: %d, ptr_a 자체 값(주소): %p\n", *a, (void*)a);
    printf("b가 가리키는 값: %d, ptr_b 자체 값(주소): %p\n\n", *b, (void*)b);
}
