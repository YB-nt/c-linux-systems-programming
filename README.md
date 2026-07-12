# c-linux-systems-programming
C 언어 및 Linux 시스템 프로그래밍 학습을 위한 문제풀이


# Phase 1 — 문법 + 메모리 기초 

모든 문제는 아래 형식을 따른다:

- **목표**: 이 문제로 확인하려는 개념
- **요구사항**: 정확히 구현해야 하는 것 (함수 시그니처 고정)
- **입력/출력 예시**: 실제 터미널에 찍히는 문자열 그대로
- **성공 기준**: 이 상태가 되면 통과
- **실패로 간주하는 경우**: 컴파일 경고, 크래시, 잘못된 출력, 메모리 문제 등 명시
- **의도적으로 실패해야 하는 부분**: 있다면 왜 실패해야 하는지, 어떤 종류의 실패인지(컴파일 에러 / 런타임 크래시 / 잘못된 값)

---

## Chapter 1 — 변수, 타입, 연산자, 제어문

### 문제 1-1. 타입 경계값 탐지기

**목표**: C의 타입 크기가 플랫폼 의존적이라는 것과, 정수 오버플로우가 "에러 없이 조용히" 발생한다는 것을 직접 확인한다.

**요구사항**:

```c
void print_type_info(void);   // 아래 3가지를 모두 출력
```

1. 아래 타입들의 `sizeof` 결과를 바이트 단위로 출력: `char`, `short`, `int`, `long`, `long long`, `unsigned int`, `float`, `double`
2. `<limits.h>`의 `INT_MAX`, `INT_MIN`, `UINT_MAX`, `CHAR_MAX`, `CHAR_MIN`을 출력
3. 아래 두 가지 오버플로우 상황을 **직접 재현하고 결과를 출력**:
    - `unsigned int x = 0; x = x - 1;` 실행 후 `x` 값 출력
    - `signed char c = 127; c = c + 1;` 실행 후 `c` 값 출력 (정수로 캐스팅해서 출력할 것)

**출력 예시** (실제 값은 플랫폼에 따라 다를 수 있음 — 아래는 x86-64 Linux/macOS 기준 예상값):

```
sizeof(char)      = 1 bytes
sizeof(short)     = 2 bytes
sizeof(int)       = 4 bytes
sizeof(long)      = 8 bytes
sizeof(long long) = 8 bytes
sizeof(unsigned int) = 4 bytes
sizeof(float)     = 4 bytes
sizeof(double)    = 8 bytes

INT_MAX  = 2147483647
INT_MIN  = -2147483648
UINT_MAX = 4294967295
CHAR_MAX = 127
CHAR_MIN = -128

[unsigned underflow test]
x = 0, after x = x - 1: x = 4294967295

[signed char overflow test]
c = 127, after c = c + 1: c = -128
```

**성공 기준**:

- 컴파일 시 `-Wall -Wextra` 경고 0개
- 위 8개 항목이 전부 출력됨 (정확한 숫자는 본인 플랫폼 값이면 됨 — 위 예시는 참고용)
- `unsigned int` 언더플로우 결과가 매우 큰 양수(4294967295 근처)로 나옴 — 이게 "정상"이다. 크래시가 나거나 음수가 나오면 실패
- `signed char` 오버플로우 결과가 음수(-128)로 나옴 — 이것도 "정상"이다

**실패로 간주하는 경우**:

- 컴파일 경고가 하나라도 뜨는 경우 (특히 `%d`에 `unsigned int` 넣어서 나는 format 경고 — `%u` 써야 함)
- 프로그램이 크래시하는 경우 (이 문제는 크래시 없이 끝까지 실행되어야 정상)
- `sizeof` 결과에 `%d`를 써서 경고가 나는 경우 — 반드시 `%zu` 사용

**의도적으로 실패해야 하는 부분**: 없음. 이 문제는 전부 정상 종료해야 하며, "오버플로우가 일어나도 프로그램은 안 죽고 계속 돈다"는 것 자체가 학습 포인트다.

---

### 문제 1-2. 진법 변환기 (비트 연산 전용)

**목표**: `printf`의 포맷 지정자에 의존하지 않고 비트 연산만으로 2진수 문자열을 만들 수 있는지 확인한다.

**요구사항**:

```c
void print_binary(unsigned int n);
```

- 함수 내부에서 `%x`, `%o`, `%b` 등 진법 관련 포맷 지정자 사용 금지 (일반 `%d`, `%u`, `%s`, `%c`는 허용)
- 비트 연산자(`&`, `|`, `>>`, `<<`)와 반복문만 사용해서 2진수 문자열을 만들고 출력
- **32비트 전부** 출력 (앞자리 0을 생략하지 않음)
- 함수는 값을 리턴하지 않고 `printf`로 직접 출력 (줄바꿈 포함 여부는 자유, 단 테스트 시 값만 비교)

**입력/출력 예시**:

```c
print_binary(5);
// 출력: 00000000000000000000000000000101

print_binary(0);
// 출력: 00000000000000000000000000000000

print_binary(4294967295u);   // UINT_MAX
// 출력: 11111111111111111111111111111111

print_binary(2147483648u);   // 2^31, 최상위 비트만 1
// 출력: 10000000000000000000000000000000
```

**성공 기준**:

- 위 4개 테스트 케이스(`5`, `0`, `4294967295`, `2147483648`) 모두 정확히 일치하는 32자리 문자열 출력
- 출력 문자열의 길이가 항상 정확히 32자 (더 짧거나 길면 실패)
- 컴파일 경고 0개

**실패로 간주하는 경우**:

- `%x`, `sprintf`의 진법 변환 기능 등을 사용한 경우 (문제 취지 위반 — 컴파일은 되지만 "풀이 실패"로 간주)
- 출력 자리수가 32자리가 아닌 경우 (예: 앞자리 0 생략하고 `101`만 출력하면 실패)
- `n=0`일 때 아무것도 출력 안 하거나 빈 문자열이 나오면 실패

**의도적으로 실패해야 하는 부분**: 없음.

---

### 문제 1-3. FizzBuzz 변형 — 비트마스크 버전

_(이미 대화에서 상세히 다룬 문제 — 아래는 통합 재정리)_

**목표**: 여러 개의 독립적인 boolean 조건을 정수 하나로 압축(비트플래그)하고, `switch`로 분기하는 패턴을 익힌다. 이 패턴은 `open()`, `socket()` 등 실제 시스템 콜 옵션 처리 방식과 동일하다.

**요구사항**:

```c
int main(void);   // 별도 함수 분리 없이 main에 작성해도 무방
```

- 1부터 100까지 순회
- 3의 배수면 `fizz` 비트(값 1)를 켜고, 5의 배수면 `buzz` 비트(값 2)를 켬
- `if-else` 체인 없이 `switch(flag)`로 분기 (단, 비트를 계산하는 `if (i % 3 == 0) flag |= 1;` 같은 조건문은 허용 — 금지되는 건 출력 분기를 `switch`가 아니라 `if-else`로 하는 것)
- 각 `case`에는 반드시 `break` 포함

**출력 예시** (1~20까지만 표시):

```
1
2
Fizz
4
Buzz
Fizz
7
8
Fizz
Buzz
11
Fizz
13
14
FizzBuzz
16
17
Fizz
19
Buzz
```

**성공 기준**:

- 1~100 전체 출력이 표준 FizzBuzz(if-else로 짠 버전)와 **한 글자도 다르지 않게** 일치
- `switch`문에 최소 4개의 `case`(0, 1, 2, 3) 존재, 각 case에 `break` 존재
- 컴파일 경고 0개 (특히 `switch`에서 `case` 누락 경고 — `-Wswitch` 관련)

**실패로 간주하는 경우**:

- `break` 누락으로 fallthrough 발생 (실행은 되지만 출력이 표준 FizzBuzz와 다르게 나옴 — 이게 실패의 정확한 정의)
- `switch` 대신 `if-else`로 최종 출력 분기한 경우

**의도적으로 실패해야 하는 부분**: 없음.

---

## Chapter 2 — 포인터

### 문제 2-1. 포인터로 swap 구현

**목표**: 값 전달(pass by value)과 포인터 전달(pass by pointer)의 차이를 직접 실행 결과로 확인한다. **이 문제는 두 함수 중 하나가 "의도적으로 작동하지 않는 것"이 정답이다.**

**요구사항**:

```c 
void swap_wrong(int a, int b);      // 값 전달
void swap_right(int *a, int *b);    // 포인터 전달
```

- `swap_wrong`: 함수 내부에서 `a`, `b`를 서로 바꾸는 로직을 작성 (평범한 임시변수 방식)
- `swap_right`: 포인터가 가리키는 실제 값을 서로 바꾸는 로직 작성
- `main`에서 순서대로: `swap_wrong` 호출 전후 원본 변수 출력 → `swap_right` 호출 전후 원본 변수 출력

**입력/출력 예시**:

```c
int x = 1, y = 2;

printf("--- swap_wrong 호출 전: x=%d, y=%d\n", x, y);
swap_wrong(x, y);
printf("--- swap_wrong 호출 후: x=%d, y=%d\n", x, y);

printf("--- swap_right 호출 전: x=%d, y=%d\n", x, y);
swap_right(&x, &y);
printf("--- swap_right 호출 후: x=%d, y=%d\n", x, y);
```

**기대 출력**:

```
--- swap_wrong 호출 전: x=1, y=2
--- swap_wrong 호출 후: x=1, y=2     ← 바뀌지 않음. 이게 정답이다.
--- swap_right 호출 전: x=1, y=2
--- swap_right 호출 후: x=2, y=1     ← 바뀜. 이게 정답이다.
```

**성공 기준 (중요 — 이 문제의 핵심)**:

- `swap_wrong` 호출 후에도 `x`, `y` 원본값이 **바뀌지 않아야** 통과다. 만약 `swap_wrong`이 `x`, `y`를 바꿔버렸다면, 함수 시그니처를 잘못 만들었거나(포인터를 몰래 썼거나) 전역변수를 참조한 것 — 이 경우 **문제를 잘못 푼 것**이다.
- `swap_right` 호출 후에는 `x`, `y`가 **반드시 바뀌어야** 통과다.
- 컴파일 경고 0개, 크래시 없음

**"실패"의 두 가지 의미 — 반드시 구분할 것**:

1. **프로그램 크래시/컴파일 에러 = 버그.** 이 문제에서는 발생하면 안 됨.
2. **`swap_wrong`이 원본을 못 바꾸는 것 = 정상 동작.** 이건 버그가 아니라 "값 전달은 원본을 바꿀 수 없다"는 C의 정상적인 의미론(semantics)을 보여주는 것이다. 함수 이름이 `wrong`인 이유는 "이 함수가 오작동해서"가 아니라 "swap을 하려는 의도가 값 전달 방식으로는 실패한다"는 뜻이다.

**추가 요구사항**: `swap_wrong` 함수 내부 또는 바로 위에 주석으로 "왜 원본이 안 바뀌는지"를 스택 프레임 관점에서 1~2문장 설명 작성.

---

### 문제 2-2. 포인터 산술과 배열의 동치성 증명

**목표**: `arr[i]`와 `*(arr+i)`가 같은 결과를 낸다는 것, 그리고 배열과 포인터가 `sizeof` 앞에서는 다르게 취급된다는 것을 직접 확인한다.

**요구사항**:

```c
int main(void);
```

1. `int arr[5] = {10, 20, 30, 40, 50};` 선언
2. 모든 인덱스(0~4)에 대해 아래 두 값이 같은지 출력하며 확인:
    - `arr[i]` 값과 `*(arr + i)` 값
    - `&arr[i]` 주소와 `(arr + i)` 주소
3. 함수 작성:
    
    ```c
    int sum_via_pointer(int *arr, int len);  // *p++ 형태의 포인터 순회로 합계 계산
    ```
    
4. `sizeof(arr)`와, `int *p = arr;`로 선언한 `p`에 대해 `sizeof(p)`를 각각 출력하고 그 차이를 주석으로 설명

**출력 예시**:

```
[인덱스별 비교]
i=0: arr[0]=10, *(arr+0)=10, &arr[0]=0x7ffee3a4a9c0, (arr+0)=0x7ffee3a4a9c0
i=1: arr[1]=20, *(arr+1)=20, &arr[1]=0x7ffee3a4a9c4, (arr+1)=0x7ffee3a4a9c4
i=2: arr[2]=30, *(arr+2)=30, &arr[2]=0x7ffee3a4a9c8, (arr+2)=0x7ffee3a4a9c8
i=3: arr[3]=40, *(arr+3)=40, &arr[3]=0x7ffee3a4a9cc, (arr+3)=0x7ffee3a4a9cc
i=4: arr[4]=50, *(arr+4)=50, &arr[4]=0x7ffee3a4a9d0, (arr+4)=0x7ffee3a4a9d0

[합계 검증]
sum_via_pointer 결과: 150   (10+20+30+40+50과 반드시 일치해야 함)

[sizeof 비교]
sizeof(arr) = 20   (int 5개 * 4바이트 = 배열 전체 크기)
sizeof(p)   = 8    (포인터 자체의 크기, 64비트 시스템 기준)
```

**성공 기준**:

- 모든 인덱스에서 `arr[i] == *(arr+i)`, `&arr[i] == (arr+i)` — 값과 주소 둘 다 일치
- `sum_via_pointer(arr, 5)`가 정확히 150 반환
- `sizeof(arr)`은 20 (배열 전체 바이트 수), `sizeof(p)`는 8 (포인터 크기, 32비트 시스템이면 4) — **이 둘이 다르다는 것 자체가 정답**. 같은 값이 나오면 `p`를 잘못 선언했을 가능성이 높음 (예: `int p[5]`로 배열처럼 선언했다면 같아짐 — 이 경우 문제 재확인 필요)

**실패로 간주하는 경우**:

- 인덱스 비교에서 값이나 주소가 하나라도 불일치 (버그)
- `sum_via_pointer` 결과가 150이 아닌 경우
- `sizeof(arr)`과 `sizeof(p)`가 같게 나오는 경우 (포인터 선언을 잘못했을 가능성)

**의도적으로 실패해야 하는 부분**: 없음. 이 문제의 모든 비교는 "일치해야" 정답이다. (문제 2-1과 달리 여기선 실패하는 케이스가 없음 — 혼동 주의)

---

### 문제 2-3. 함수 포인터로 간단한 계산기

**목표**: 함수 포인터 배열 선언 문법을 손으로 직접 쓸 수 있는지 확인한다.

**요구사항**:

```c
int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);

int calculate(int a, int b, char op);   // op: '+', '-', '*'
```

- `calculate` 내부에서 함수 포인터 배열을 사용해서 `op`에 따라 `add`/`sub`/`mul` 중 하나를 호출
- 잘못된 연산자(`op`가 `+`, `-`, `*` 어느 것도 아닌 경우)가 들어오면 에러 처리: `calculate`는 이 경우 `int`로 특정 실패값(예: `INT_MIN`)을 리턴하고, `main`에서 그 값을 확인해 "잘못된 연산자" 메시지를 출력

**입력/출력 예시**:

```c
printf("3 + 4 = %d\n", calculate(3, 4, '+'));
printf("10 - 6 = %d\n", calculate(10, 6, '-'));
printf("5 * 6 = %d\n", calculate(5, 6, '*'));

int result = calculate(1, 2, '%');   // 지원하지 않는 연산자
if (result == INT_MIN) {
    printf("잘못된 연산자입니다.\n");
}
```

**기대 출력**:

```
3 + 4 = 7
10 - 6 = 4
5 * 6 = 30
잘못된 연산자입니다.
```

**성공 기준**:

- 정상 연산자(`+`, `-`, `*`) 세 가지 모두 정확한 계산 결과 출력
- 잘못된 연산자 입력 시 크래시 없이 에러 처리 경로로 진입 (프로그램이 죽으면 실패)
- 함수 포인터 배열 문법을 실제로 사용했을 것 (아래처럼 `if-else`로 함수를 고르면 문제 취지 위반):
    
    ```c
    int (*ops[3])(int, int) = {add, sub, mul};   // 이런 형태 사용
    ```
    

**실패로 간주하는 경우**:

- 함수 포인터 배열 없이 `if (op=='+') return add(a,b);` 식으로 분기만 한 경우 — 컴파일은 되지만 문제 취지(함수 포인터 배열 문법 연습) 위반으로 "풀이 실패"
- 잘못된 연산자 입력 시 크래시하거나 정의되지 않은 값을 리턴하는 경우

**의도적으로 실패해야 하는 부분**: `calculate(1, 2, '%')` 호출은 "정상적인 계산 실패"를 리턴해야 한다. 이건 프로그램 크래시가 아니라, 함수가 "나는 이 연산자를 모른다"는 것을 값으로 알려주는 정상적인 에러 처리 경로다.

---

### 문제 2-4. NULL 포인터 역참조 — 의도적 크래시 실습

**목표**: 세그폴트가 실제로 어떻게 발생하는지, gdb/lldb로 크래시 지점을 어떻게 찾는지 익힌다.

**요구사항**:

```c
int main(void) {
    int *p = NULL;
    *p = 10;     // 여기서 반드시 크래시가 발생해야 함
    return 0;    // 이 줄은 절대 실행되지 않음
}
```

**성공 기준 (이 문제는 "성공 = 프로그램이 죽는 것"이다)**:

- `gcc -g`로 컴파일 후 실행하면 **반드시 `Segmentation fault` 로 비정상 종료**해야 한다. 정상 종료(`return 0`까지 도달)하면 오히려 이상한 것이고, 이 경우 컴파일러가 최적화로 해당 코드를 제거했을 가능성이 있으니 `-O0` 옵션으로 재컴파일해서 확인.
- lldb(또는 gdb)로 크래시 지점을 정확히 찾아낼 것:
    
    ```bash
    gcc -g -O0 -o null_deref null_deref.clldb ./null_deref
    ```
    
    ```lldb
    (lldb) runProcess ... stopped* thread #1, stop reason = EXC_BAD_ACCESS (code=1, address=0x0)
    (lldb) bt
    ```
    
- `bt` 결과에서 `main` 함수, 그리고 크래시가 발생한 정확한 줄 번호(`*p = 10;` 있는 줄)가 보여야 통과

**실패로 간주하는 경우**:

- 프로그램이 크래시 없이 정상 종료되는 경우 (이 문제에서는 "안 죽는 것"이 버그)
- `bt` 결과에 줄 번호 정보가 없는 경우 (→ `-g` 플래그 누락이 원인일 가능성이 높음, 컴파일 명령 재확인)

**의도적으로 실패해야 하는 부분**: 프로그램 실행 자체가 "런타임 크래시로 종료"되는 것이 이 문제의 유일한 정답이다. 이건 버그가 아니라 문제의 목표 그 자체다.

**제출물**: lldb `bt` 출력 결과를 텍스트로 캡처해서 어느 줄에서 죽었는지 표시.
![[스크린샷 2026-07-12 오전 3.20.15.png]]

---

## Chapter 3 — 스택 vs 힙, malloc/free

### 문제 3-1. 동적 배열 직접 구현

**목표**: `realloc` 기반 동적 배열(파이썬 list와 유사한 구조)을 구현하고, valgrind/ASan으로 메모리 안전성을 검증한다.

**요구사항**:

```c
typedef struct {
    int *data;
    size_t size;       // 현재 채워진 요소 개수
    size_t capacity;    // 현재 할당된 용량
} IntVector;

IntVector* vec_create(size_t initial_capacity);
void vec_push(IntVector *v, int value);
int vec_get(IntVector *v, size_t index);
void vec_free(IntVector *v);
```

- `initial_capacity`는 0이 들어올 수도 있음 — 이 경우도 크래시 없이 처리해야 함 (첫 `push` 시 최소 1 이상으로 할당)
- `vec_push` 호출 시 `size == capacity`이면 `capacity`를 2배로 늘리고 `realloc`
- `vec_get`은 범위를 벗어난 `index`가 들어오면(`index >= size`) 프로그램을 죽이지 않고 `stderr`로 에러 메시지 출력 후 `-1` 리턴 (또는 사전에 정의한 에러 표시값)

**동작 확인 예시**:

```c
IntVector *v = vec_create(2);
for (int i = 0; i < 10; i++) {
    vec_push(v, i * i);
}
for (size_t i = 0; i < v->size; i++) {
    printf("v[%zu] = %d\n", i, vec_get(v, i));
}
vec_free(v);
```

**기대 출력**:

```
v[0] = 0
v[1] = 1
v[2] = 4
v[3] = 9
v[4] = 16
v[5] = 25
v[6] = 36
v[7] = 49
v[8] = 64
v[9] = 81
```

**성공 기준**:

- 위 10개 값이 정확히 출력됨
- `vec_get(v, 100)`(범위 초과) 호출 시 크래시 없이 에러 메시지 출력하고 프로그램 계속 진행
- **메모리 안전성 검증 — 아래 명령 실행 결과가 반드시 "누수 없음"이어야 통과**:
    
    ```bash
    # macOSleaks --atExit -- ./vector_test# 또는 AddressSanitizergcc -g -fsanitize=address -o vector_test vector_test.c./vector_test
    ```
    
    - `leaks` 결과: `0 leaks for 0 total leaked bytes` 가 나와야 함
    - ASan 결과: 아무 에러 메시지 없이 정상 종료해야 함 (에러 메시지가 하나라도 뜨면 실패)
- 10000개 요소를 `push`했을 때도 위 메모리 검증 도구에서 누수 0이어야 함

**실패로 간주하는 경우**:

- `vec_free` 호출 후에도 메모리가 남아있다고 검증 도구가 보고하는 경우
- `vec_get`에 범위 초과 index를 넣었을 때 크래시하거나(세그폴트) 검증 도구가 "invalid read" 에러를 보고하는 경우
- `realloc` 실패(반환값 NULL) 처리를 안 해서, 극단적 상황에서 크래시 가능성이 있는 경우 (실제로 테스트에서 발생하지 않아도, 코드 리뷰 시 `realloc` 반환값 체크 여부를 확인함)

**의도적으로 실패해야 하는 부분**: 없음. 이 문제는 모든 경로에서 안전하게 동작해야 한다.

---

### 문제 3-2. 메모리 누수 사냥

**목표**: 누수가 있는 코드와 없는 코드를 직접 비교해서, 검증 도구가 무엇을 다르게 보고하는지 눈으로 확인한다. **이 문제는 두 개의 버전을 모두 작성해야 한다.**

**요구사항**:

```c
// 버전 A — 의도적으로 누수 있음
void leaky_function(void) {
    int *p = malloc(100 * sizeof(int));
    // 의도적으로 free 하지 않음
}

// 버전 B — 누수 수정본
void fixed_function(void) {
    int *p = malloc(100 * sizeof(int));
    free(p);
}
```

- `main`에서 각각 5번씩 호출하는 두 개의 실행 파일(또는 매크로/커맨드라인 인자로 버전 전환)을 만들 것

**검증 절차 및 기대 결과**:

```bash
# 버전 A (누수 있음) 검증
gcc -g -o leaky leaky.c
leaks --atExit -- ./leaky
```

**버전 A 기대 출력** (요약):

```
Process ... leaks for X total leaked bytes.
5 leaks for 2000 total leaked bytes   ← 100 * sizeof(int) * 5회 = 2000 bytes 근처
```

→ **이 결과가 나오면 정상이다.** 누수가 "없다"고 나오면 오히려 `leaky_function`을 잘못 작성한 것(실제로 free를 넣었거나 호출을 안 했거나).

```bash
# 버전 B (수정본) 검증
gcc -g -o fixed fixed.c
leaks --atExit -- ./fixed
```

**버전 B 기대 출력**:

```
0 leaks for 0 total leaked bytes
```

**성공 기준**:

- 버전 A: 검증 도구가 **정확히 5번의 누수, 총 2000바이트 근처**(플랫폼별 malloc 오버헤드로 약간 다를 수 있음)를 보고함
- 버전 B: 검증 도구가 **누수 0**을 보고함
- 두 버전 모두 크래시 없이 정상 종료

**실패로 간주하는 경우**:

- 버전 A에서 누수가 감지되지 않는 경우 (누수 유발 코드를 잘못 작성한 것)
- 버전 B에서 누수가 감지되는 경우 (free 로직에 버그가 있는 것)

**의도적으로 실패해야 하는 부분**: 버전 A는 "검증 도구가 누수를 잡아내는 것"이 성공이다. 즉 이 경우 "메모리 관리는 실패했지만, 그 실패를 도구로 정확히 탐지했다"는 게 문제의 목표다.

---

### 문제 3-3. Double free / Dangling pointer 직접 만들기

**목표**: 이미 해제된 메모리를 다시 해제하거나 접근했을 때 어떤 일이 일어나는지 직접 확인한다.

**요구사항 — 3개의 독립된 짧은 프로그램 작성**:

**(A) Double free**

```c
int *p = malloc(sizeof(int));
*p = 42;
free(p);
free(p);   // 의도적으로 두 번 해제
```

**(B) Double free 수정본**

```c
int *p = malloc(sizeof(int));
*p = 42;
free(p);
p = NULL;
free(p);   // free(NULL)은 안전하게 아무 일도 안 함 — C 표준 보장 사항
```

**(C) Dangling pointer 읽기**

```c
int *p = malloc(sizeof(int));
*p = 42;
free(p);
printf("free 이후 값: %d\n", *p);   // 이미 해제된 메모리 읽기
```

**각 프로그램의 기대 동작**:

|프로그램|기대 동작|이게 정상인 이유|
|---|---|---|
|(A) Double free|실행 시 `malloc(): double free detected` 등의 메시지와 함께 **비정상 종료(abort)**|glibc/macOS 할당자가 double free를 감지하고 강제 종료시키는 것이 설계된 동작|
|(B) 수정본|크래시 없이 **정상 종료**|`free(NULL)`은 C 표준에서 아무 동작도 하지 않도록 규정됨 (안전)|
|(C) Dangling read|크래시할 수도, 안 할 수도, 42가 그대로 나올 수도, 쓰레기값이 나올 수도 있음 — **결과가 매번 다를 수 있다는 것 자체가 정답**|Undefined Behavior이기 때문에 "이런 값이 나와야 한다"는 보장이 아예 없음|

**성공 기준**:

- (A): 프로그램이 크래시(abort)하는 것을 직접 실행해서 확인. 크래시 메시지를 캡처해서 제출
- (B): 프로그램이 크래시 없이 끝까지 실행되는 것을 확인
- (C): 최소 3번 이상 반복 실행해서, 매번 같은 값이 나오는지 다른 값이 나오는지 관찰하고 기록 (어떤 결과가 나오든 "정답"이지만, 관찰하고 왜 이런 게 가능한지 서술하는 것이 요구사항)

**실패로 간주하는 경우**:

- (A)에서 크래시가 안 나는 경우 — 이 경우 애초에 `free(p)`를 두 번 안 부른 것일 수 있으니 코드 재확인
- (B)에서 크래시가 나는 경우 — `p = NULL` 대입을 빠뜨렸을 가능성

**의도적으로 실패해야 하는 부분**: (A)는 프로그램이 죽는 것이 정답. (C)는 "정해진 정답 값이 없다"는 것 자체가 학습 목표 — Undefined Behavior를 코드로 직접 겪어보는 것.

**제출물**: "왜 `free` 후 포인터를 `NULL`로 초기화하는 습관이 필요한가"를 (A)와 (B)의 실행 결과 차이에 근거해서 한 문단으로 서술.

---

## Chapter 4 — 문자열

### 문제 4-1. strlen, strcpy, strcat, strcmp 직접 구현

**목표**: 표준 라이브러리 문자열 함수를 포인터 연산만으로 재구현할 수 있는지 확인한다.

**요구사항**:

```c
size_t my_strlen(const char *s);
char*  my_strcpy(char *dest, const char *src);
char*  my_strcat(char *dest, const char *src);
int    my_strcmp(const char *s1, const char *s2);
```

- `<string.h>`의 `strlen`, `strcpy`, `strcat`, `strcmp`를 함수 내부에서 호출 금지
- 포인터 연산(`*p++` 등)과 반복문만 사용

**정확성 요구사항 (표준 함수와 동일해야 함)**:

|함수|입력|기대 출력|
|---|---|---|
|`my_strlen`|`"hello"`|`5`|
|`my_strlen`|`""`|`0`|
|`my_strcpy`|`dest`, `"world"`|`dest`에 `"world"` 복사, 리턴값은 `dest` 자체|
|`my_strcat`|`dest="foo"`, `src="bar"`|`dest`가 `"foobar"`가 됨|
|`my_strcmp`|`"abc"`, `"abc"`|`0`|
|`my_strcmp`|`"abc"`, `"abd"`|음수 (표준처럼 정확히 -1일 필요는 없음, 부호만 일치하면 됨)|
|`my_strcmp`|`"abd"`, `"abc"`|양수|

**검증 방법 — 표준 함수와 자동 비교**:

```c
#include <string.h>
#include <assert.h>

assert(my_strlen("hello") == strlen("hello"));

char buf1[20], buf2[20];
strcpy(buf1, "world");
my_strcpy(buf2, "world");
assert(strcmp(buf1, buf2) == 0);   // 검증 목적으로만 표준 strcmp 사용 (구현 내부에서 쓰면 안 됨)

assert((my_strcmp("abc","abc") == 0) == (strcmp("abc","abc") == 0));
assert((my_strcmp("abc","abd") < 0) == (strcmp("abc","abd") < 0));
```

**성공 기준**:

- 위 `assert` 문들이 전부 통과 (하나라도 실패하면 프로그램이 `assertion failed`로 죽음 — 이 경우는 버그로 간주하고 수정)
- 컴파일 경고 0개, `<string.h>` 함수를 구현 내부에서 사용하지 않았을 것 (테스트/검증 코드에서 비교용으로 쓰는 것은 허용)

**실패로 간주하는 경우**:

- `assert` 실패로 프로그램이 죽는 경우
- 구현 함수 내부에서 `strlen` 등 표준 함수를 호출한 경우 (컴파일은 되지만 문제 취지 위반)

**의도적으로 실패해야 하는 부분**: 없음.

---

### 문제 4-2. strcpy vs strncpy 버퍼 오버플로우 실험

**목표**: `strcpy`가 왜 안전하지 않은지, `strncpy`도 완벽한 해결책이 아니라는 것을 직접 겪어본다. **이 문제는 첫 번째 버전이 위험한 동작(정의되지 않은 동작)을 보이는 것을 관찰하는 것이 목표다.**

**요구사항 — 3단계로 진행**:

**(A) 위험한 버전 — 그대로 실행해서 관찰만 할 것**

```c
char dest[5];
char *src = "Hello, World!";   // 13글자 + null = 14바이트, dest는 5바이트뿐
strcpy(dest, src);              // 버퍼 오버플로우 발생
printf("%s\n", dest);
```

**(A)의 기대 동작**: **정해진 기대 출력이 없다.** 아래 중 무엇이든 나올 수 있다:

- 크래시(Segmentation fault 또는 `stack smashing detected`)
- 이상한 문자가 섞인 출력
- 아무 문제 없어 보이는 정상 출력 (가장 위험한 경우 — 문제가 있는데 겉으로는 안 보임)

이 세 가지 중 어떤 결과가 나오든 그 자체가 "정답"이다. 중요한 건 **AddressSanitizer로 실행해서 실제로 무슨 일이 일어나는지 명시적으로 확인하는 것**:

```bash
gcc -g -fsanitize=address -o overflow_test overflow_test.c
./overflow_test
```

**기대 ASan 출력**:

```
==ERROR: AddressSanitizer: stack-buffer-overflow
WRITE of size 14 at 0x... thread T0
    #0 in main overflow_test.c:5
```

- ASan이 반드시 `stack-buffer-overflow` 에러를 보고해야 이 단계가 "성공"이다. 만약 ASan 없이 실행했을 때 우연히 정상 출력처럼 보였더라도, ASan 결과가 에러를 보고하면 실제로는 버그가 있었던 것이다.

**(B) strncpy로 수정 — 여전히 문제가 남아있는 버전**

```c
char dest[5];
char *src = "Hello, World!";
strncpy(dest, src, sizeof(dest) - 1);
printf("%s\n", dest);   // 이 출력도 문제가 있을 수 있음
```

**(B)의 기대 동작**: ASan에서는 buffer overflow 에러가 사라짐 (크기 제한을 지켰으므로). 하지만 `dest`에 **null terminator가 보장되지 않아서** `printf("%s", dest)`가 `dest` 뒤의 스택 메모리까지 읽어서 **쓰레기 문자가 이어붙어 출력될 수 있다.** 이 현상이 재현되면 성공.

**(C) 완전한 수정본**

```c
char dest[5];
char *src = "Hello, World!";
strncpy(dest, src, sizeof(dest) - 1);
dest[sizeof(dest) - 1] = '\0';   // 수동으로 null terminator 보장
printf("%s\n", dest);
```

**(C)의 기대 출력**:

```
Hell
```

(`dest`가 5바이트라 4글자 + null만 들어감)

**성공 기준**:

- (A): ASan이 `stack-buffer-overflow`를 명확히 보고함
- (B): ASan에서 buffer overflow 에러는 사라졌지만, 일반 실행(`./a.out`, ASan 없이) 시 출력 끝에 이상한 문자가 붙는 것을 최소 1회 이상 관찰 (매번 재현되지 않을 수 있음 — 스택에 남아있는 값에 따라 다르므로, 재현 안 되면 "재현 안 됨"도 관찰 결과로 기록)
- (C): 정확히 `Hell` 출력, ASan 에러 없음

**실패로 간주하는 경우**:

- (A)에서 ASan을 안 쓰고 그냥 "정상 출력됐다"고 결론내리는 경우 — 반드시 ASan으로 검증해야 함
- (C)에서 여전히 이상한 문자가 출력되거나 ASan 에러가 나는 경우 (null terminator 처리 실수)

**의도적으로 실패해야 하는 부분**: (A) 전체가 "정의되지 않은 동작을 직접 재현하는 것"이 목표이며, 정확한 출력값을 맞추는 문제가 아니다. (B)도 마찬가지로 "여전히 위험하다"를 보여주는 것이 목표다.

---

### 문제 4-3. 문자열 토크나이저 (strtok 없이)

**목표**: 동적 메모리 할당으로 가변 개수의 문자열 배열을 만들고 정확히 해제하는 연습.

**요구사항**:

```c
char** split_string(const char *str, char delimiter, int *count);
void free_split(char **tokens, int count);
```

- `str`을 `delimiter` 문자 기준으로 분리
- 연속된 구분자는 하나로 취급 (예: `"a,,b"`를 `,`로 분리하면 `["a", "", "b"]`가 아니라 `["a", "b"]`가 되도록 — 단, 이 규칙을 다르게(빈 문자열 포함) 구현해도 괜찮으나, 어느 쪽으로 구현했는지 주석에 명시할 것)
- `count`에는 분리된 단어의 개수를 저장 (포인터로 전달받아 함수 내부에서 값 채움)
- `<string.h>`의 `strtok` 사용 금지

**입력/출력 예시**:

```c
int count;
char **words = split_string("hello world from C", ' ', &count);

printf("count = %d\n", count);
for (int i = 0; i < count; i++) {
    printf("words[%d] = \"%s\"\n", i, words[i]);
}

free_split(words, count);
```

**기대 출력**:

```
count = 4
words[0] = "hello"
words[1] = "world"
words[2] = "from"
words[3] = "C"
```

**추가 테스트 케이스**:

```c
split_string("", ' ', &count);       // count == 0 이어야 함, words는 NULL이거나 빈 배열
split_string("single", ' ', &count); // count == 1, words[0] == "single"
```

**성공 기준**:

- `"hello world from C"` 입력 시 위 4개 단어가 정확히 분리됨
- 빈 문자열 입력 시 크래시 없이 `count == 0`
- 단어가 하나뿐인 입력도 정상 처리
- **메모리 검증**: `leaks --atExit` 또는 ASan으로 확인했을 때 **누수 0**. `split_string`으로 할당한 모든 메모리(`char**` 배열 자체 + 각 `char*` 문자열)를 `free_split`이 전부 해제해야 함

**실패로 간주하는 경우**:

- 단어 개수가 틀리게 세어지는 경우
- `free_split` 이후에도 메모리 검증 도구가 누수를 보고하는 경우 (흔한 실수: `words` 배열 자체는 해제했는데 각 `words[i]` 문자열은 해제 안 한 경우, 또는 그 반대)
- 빈 문자열이나 구분자가 하나도 없는 입력에서 크래시

**의도적으로 실패해야 하는 부분**: 없음.

---

## Chapter 5 — 구조체

### 문제 5-1. 연결 리스트 구현

**목표**: 포인터를 이용해 노드 기반 자료구조를 조작하는 기본기를 익힌다.

**요구사항**:

```c
typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* list_push_front(Node *head, int value);   // 새 head 리턴
Node* list_push_back(Node *head, int value);    // head는 안 바뀌지만 일관성 위해 리턴
void  list_print(Node *head);
Node* list_remove(Node *head, int value);       // 삭제 후 새 head 리턴 (head 자체가 삭제될 수도 있음)
void  list_free(Node *head);
```

- `list_remove`는 리스트에 없는 값이 들어와도 크래시 없이 원래 리스트를 그대로 리턴
- `list_remove`는 같은 값이 여러 개 있으면 **첫 번째로 찾은 하나만** 삭제 (전부 삭제하는 걸로 구현했다면 주석에 명시)

**동작 확인 시나리오**:

```c
Node *head = NULL;
head = list_push_back(head, 1);
head = list_push_back(head, 2);
head = list_push_back(head, 3);
list_print(head);              // 1 -> 2 -> 3 -> NULL

head = list_push_front(head, 0);
list_print(head);              // 0 -> 1 -> 2 -> 3 -> NULL

head = list_remove(head, 2);   // 중간 삭제
list_print(head);              // 0 -> 1 -> 3 -> NULL

head = list_remove(head, 0);   // 첫 번째(head) 삭제
list_print(head);              // 1 -> 3 -> NULL

head = list_remove(head, 3);   // 마지막 삭제
list_print(head);              // 1 -> NULL

head = list_remove(head, 999); // 존재하지 않는 값 — 크래시 없이 리스트 그대로
list_print(head);              // 1 -> NULL

list_free(head);
```

**기대 출력** (형식은 자유, 순서와 값만 일치하면 됨):

```
1 -> 2 -> 3 -> NULL
0 -> 1 -> 2 -> 3 -> NULL
0 -> 1 -> 3 -> NULL
1 -> 3 -> NULL
1 -> NULL
1 -> NULL
```

**성공 기준**:

- 위 시나리오 그대로 실행했을 때 각 단계의 출력이 정확히 일치
- 존재하지 않는 값 삭제 시도(`list_remove(head, 999)`) 시 크래시 없음
- **메모리 검증**: 삽입/삭제를 100회 반복하는 별도 테스트 작성 후 `leaks`/ASan으로 확인했을 때 누수 0
- `list_free` 호출 후 프로그램이 그 포인터를 다시 사용하지 않음 (해제 후 `head` 변수를 `NULL`로 별도 설정하는 습관 권장)

**실패로 간주하는 경우**:

- head, 중간, 끝 삭제 중 하나라도 리스트가 깨지는 경우 (예: 중간 노드 삭제 후 `next` 포인터 연결이 끊겨서 그 이후 노드들이 통째로 사라지는 메모리 누수)
- 존재하지 않는 값 삭제 시 크래시
- 100회 삽입/삭제 반복 테스트에서 메모리 누수 발생

**의도적으로 실패해야 하는 부분**: 없음.

---

### 문제 5-2. 구조체 포인터 vs 구조체 값 전달 비교

**목표**: 구조체도 배열과 마찬가지로 값 전달 시 통째로 복사된다는 것, 그리고 구조체 멤버 순서에 따라 패딩으로 인해 크기가 달라질 수 있다는 것을 확인한다.

**요구사항**:

```c
typedef struct {
    char name[32];
    int  age;
} Person;

void modify_by_value(Person p);     // 내부에서 p.age를 변경 시도
void modify_by_pointer(Person *p);  // 내부에서 p->age를 변경 시도
```

**동작 확인 시나리오**:

```c
Person person = {"Alice", 30};

printf("modify_by_value 호출 전: age=%d\n", person.age);
modify_by_value(person);
printf("modify_by_value 호출 후: age=%d\n", person.age);

printf("modify_by_pointer 호출 전: age=%d\n", person.age);
modify_by_pointer(&person);
printf("modify_by_pointer 호출 후: age=%d\n", person.age);
```

**기대 출력**:

```
modify_by_value 호출 전: age=30
modify_by_value 호출 후: age=30      ← 안 바뀜. 정답임 (문제 2-1과 동일한 원리)
modify_by_pointer 호출 전: age=30
modify_by_pointer 호출 후: age=99    ← 바뀜 (modify_by_pointer 내부에서 99로 설정한다고 가정)
```

**패딩 비교 요구사항**:

```c
typedef struct {
    char name[32];
    int  age;
} PersonV1;

typedef struct {
    int  age;
    char name[32];
} PersonV2;

printf("sizeof(PersonV1) = %zu\n", sizeof(PersonV1));
printf("sizeof(PersonV2) = %zu\n", sizeof(PersonV2));
```

**기대 출력** (일반적인 x86-64 환경 기준, 컴파일러/플랫폼에 따라 다를 수 있음):

```
sizeof(PersonV1) = 36
sizeof(PersonV2) = 36
```

이 경우는 `char[32]`가 4의 배수라 우연히 같을 수 있다. **중요한 것은 값이 같냐 다르냐가 아니라, 왜 그런 값이 나오는지 `pahole` 또는 직접 계산으로 설명하는 것**이다. 필드 순서를 바꿔서 패딩 차이가 실제로 나는 예시(`char`와 `int`를 번갈아 여러 개 배치)도 추가로 하나 더 만들어서 비교할 것:

```c
typedef struct {
    char a;
    int  b;
    char c;
    int  d;
} Mixed1;   // 패딩 많이 낌

typedef struct {
    int  b;
    int  d;
    char a;
    char c;
} Mixed2;   // 패딩 적게 낌

printf("sizeof(Mixed1) = %zu\n", sizeof(Mixed1));   // 16 예상 (4바이트 정렬 때문에)
printf("sizeof(Mixed2) = %zu\n", sizeof(Mixed2));   // 10 또는 12 예상 (컴파일러 정렬 규칙에 따라)
```

**성공 기준**:

- `modify_by_value` 호출 후 원본 `age`가 바뀌지 않음 (안 바뀌는 게 정답)
- `modify_by_pointer` 호출 후 원본 `age`가 바뀜
- `Mixed1`과 `Mixed2`의 `sizeof` 값이 서로 다르게 나옴 (필드 순서만 바꿨는데 크기가 달라지는 것을 직접 확인하는 게 이 문제의 핵심)
- 왜 그런 크기가 나오는지 필드별 오프셋을 손으로 계산해서 주석으로 설명 (컴파일러의 정렬 규칙: 각 타입은 자신의 크기만큼 정렬됨 — `int`는 4바이트 경계에 위치해야 함)

**실패로 간주하는 경우**:

- `modify_by_value` 호출 후 원본이 바뀌어버리는 경우 (포인터를 몰래 썼거나 잘못 구현한 것)
- `modify_by_pointer` 호출 후 원본이 안 바뀌는 경우 (버그)
- `Mixed1`과 `Mixed2`의 크기가 같게 나왔는데 그 이유를 설명 못 하는 경우 (컴파일러별로 정렬 규칙이 다를 수 있으니, 같게 나왔다면 그 이유도 패딩 규칙으로 설명이 가능해야 함 — "그냥 같았다"는 답은 불충분)

**의도적으로 실패해야 하는 부분**: `modify_by_value`가 원본을 못 바꾸는 것은 버그가 아니라 정답이다 (문제 2-1과 동일한 원리 — 구조체도 배열처럼 크게 복사되지만, 그 복사본을 바꾸는 것이지 원본이 아니다).

---

### 문제 5-3. 종합 — 학생 관리 시스템

**목표**: Chapter 2~5에서 만든 함수들을 재사용해서 하나의 프로그램으로 통합한다.

**요구사항**:

```c
typedef struct {
    char name[32];
    int  score;
} Student;

typedef struct {
    Student *students;
    size_t   count;
    size_t   capacity;
} StudentDB;

StudentDB* db_create(void);
void       db_add(StudentDB *db, const char *name, int score);
Student*   db_find(StudentDB *db, const char *name);   // 못 찾으면 NULL 리턴
void       db_print_all(StudentDB *db);
void       db_free(StudentDB *db);
```

- `db_add`는 문제 3-1의 동적 배열 확장 로직(용량 초과 시 2배 `realloc`) 재사용
- `db_find`는 문제 4-1에서 만든 `my_strcmp` 재사용 (이름 비교)
- 콘솔 메뉴 입력 처리 (`fgets` 권장, `scanf`로 문자열 읽을 때 버퍼 오버플로우 위험 있으니 주의)

**메뉴 동작 예시**:

```
1. Add student
2. Find student
3. Print all
4. Quit
> 1
Enter name: Alice
Enter score: 90
Added.

> 1
Enter name: Bob
Enter score: 85
Added.

> 3
Alice: 90
Bob: 85

> 2
Enter name to find: Bob
Found: Bob, score=85

> 2
Enter name to find: Charlie
Not found.

> 4
Bye.
```

**성공 기준**:

- 위 시나리오 그대로 입력했을 때 정확히 일치하는 출력
- 학생을 capacity 초과할 만큼(예: 초기 capacity 2로 설정 후 10명 이상) 추가해도 크래시 없이 정상 동작 (내부적으로 `realloc` 확장이 일어나는 것)
- 존재하지 않는 이름 검색 시 `NULL` 리턴, 크래시 없이 "Not found" 메시지 출력
- **메모리 검증**: `db_free` 이후 `leaks`/ASan으로 확인했을 때 누수 0

**실패로 간주하는 경우**:

- capacity 확장 로직 버그로 일정 개수 이상 추가 시 크래시 또는 데이터 손상(이전에 추가한 학생 정보가 깨짐)
- `db_find`에서 존재하지 않는 이름 검색 시 크래시
- 이름에 32바이트(널 문자 포함이므로 실제로는 31자) 넘는 문자열이 입력됐을 때 버퍼 오버플로우 (입력 길이 제한 처리 여부 확인 — `fgets`에 버퍼 크기를 정확히 지정했는지)
- `db_free` 후 메모리 누수 발생 (흔한 실수: `db->students` 배열은 해제했는데 `db` 구조체 자체를 담은 포인터는 해제 안 함, 또는 그 반대)

**의도적으로 실패해야 하는 부분**: 없음. 이름 길이 초과 입력에 대해서는 "잘라서 저장" 또는 "에러 메시지 출력 후 재입력 요구" 중 하나를 선택해서 구현하고, 어느 쪽으로 처리했는지 주석에 명시할 것 (둘 다 유효한 설계 선택이지만, 크래시만 아니면 됨).

---

## 전체 진행 시 공통 규칙

1. **모든 코드는 `gcc -Wall -Wextra -std=c17 -g` 로 컴파일해서 경고 0개**가 기본 전제. 경고가 있는 상태로 "일단 실행되니까 통과"로 간주하지 않는다.
2. **"성공"과 "실패"를 구분하는 방법이 문제마다 다르다는 것에 유의**:
    - 대부분의 문제: 크래시 없음 + 정확한 출력값 = 성공
    - 문제 2-1: `swap_wrong`이 실패하는 것(원본 안 바뀜) = 성공, 크래시나 컴파일 에러만 진짜 실패
    - 문제 2-4: 프로그램이 크래시하는 것 = 성공, 정상 종료되면 오히려 재확인 필요
    - 문제 3-2: 버전 A에서 누수가 검출되는 것 = 성공, 버전 B에서 안 검출되는 것 = 성공
    - 문제 3-3: (A) 크래시 = 성공, (C)는 결과가 매번 달라질 수 있는 것 자체가 성공 (정해진 정답값 없음)
    - 문제 4-2: (A)에서 ASan이 에러를 보고하는 것 = 성공
    - 문제 5-2: `modify_by_value`가 실패하는 것(원본 안 바뀜) = 성공
3. 리뷰 요청 시 아래 3가지를 함께 제출하면 리뷰 속도가 빨라짐:
    - 소스 코드
    - 실제 실행 출력 (터미널 캡처 또는 복사)
    - 사용한 검증 도구 결과 (leaks / ASan / lldb bt 등, 해당 문제에서 요구하는 경우)



