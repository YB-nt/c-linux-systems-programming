### 문제 A. 3단계 등급 판정기 (비트 2개, 새로운 조합)

학생 성적을 출석/과제 제출 여부로 등급 매기기.
1~50번 학생에 대해 (학생 번호를 임의 조건으로 활용):
- 번호가 4의 배수면 "출석 우수"
- 번호가 6의 배수면 "과제 우수"
- 둘 다 해당하면 "모범생"
- 둘 다 아니면 "보통"

비트 플래그: attend = 1, homework = 2
switch로 분기
힌트: 문제 1-3과 구조가 완전히 동일해. 배수 조건과 출력 문자열만 바뀐 것. 이 문제부터 먼저 풀어보면 원본 문제 복습이 될 거야.

### 문제 B. 3개 조건으로 확장 (비트 3개 — 새로운 자릿값 등장)

조건이 2개가 아니라 3개가 되면 어떻게 될지 확장.
1~100까지 출력하되:
- 3의 배수면 "A"
- 5의 배수면 "B"
- 7의 배수면 "C"
- 여러 개 해당하면 순서대로 이어붙여 출력 (예: "AB", "ABC")
- 아무것도 해당 안 되면 숫자 그대로 출력

비트 플래그: flag_a = 1, flag_b = 2, flag_c = 4
switch로 분기 (case가 몇 개나 필요할지 직접 계산해보기)
힌트: 조건이 3개면 가능한 조합이 몇 가지일까? (flag_a, flag_b, flag_c 각각 켜짐/꺼짐 → 2×2×2 = 8가지) case 8개를 전부 써야 해. 여기서 4 = 2^2가 왜 필요한지 (기존 1, 2와 겹치지 않는 새 비트 자리) 직접 체감하게 될 거야.

### 문제 C. 비트마스크로 옵션 조합 표현하기 (실무 패턴 미리보기)

간단한 "텍스트 스타일 옵션" 시뮬레이터. open() 시스템콜에서 O_RDONLY | O_CREAT 쓰는 방식과 똑같은 구조를 미리 연습.

``` c
#define STYLE_BOLD      1   // 0001
#define STYLE_ITALIC    2   // 0010
#define STYLE_UNDERLINE 4   // 0100

void print_style(int style) {
    switch (style) {
        case 0:                       printf("일반 텍스트\n"); break;
        case STYLE_BOLD:               printf("**볼드**\n"); break;
        case STYLE_ITALIC:             printf("_이탤릭_\n"); break;
        case STYLE_BOLD | STYLE_ITALIC: printf("***볼드+이탤릭***\n"); break;
        // 나머지 조합 case들 직접 채우기
    }
}

int main() {
    print_style(STYLE_BOLD);
    print_style(STYLE_BOLD | STYLE_ITALIC);
    print_style(STYLE_BOLD | STYLE_ITALIC | STYLE_UNDERLINE);
    // ...
    return 0;
}

```

**요구사항:**

#define으로 플래그 상수 정의 (매직넘버 1, 2 대신 이름 붙이기)
가능한 모든 조합(8가지)에 대한 case 작성
main에서 여러 조합으로 직접 호출해서 테스트

힌트: 이 문제가 실제로 open(path, O_WRONLY | O_CREAT | O_TRUNC) 같은 코드를 읽을 때 바로 도움이 되는 패턴이야. #define으로 이름 붙이는 이유는 나중에 1, 2, 4라는 숫자만 봐서는 무슨 뜻인지 알기 어렵기 때문.
