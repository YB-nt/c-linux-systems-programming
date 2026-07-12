/*
 * 요구사항
#define으로 플래그 상수 정의 (매직넘버 1, 2 대신 이름 붙이기)
가능한 모든 조합(8가지)에 대한 case 작성
main에서 여러 조합으로 직접 호출해서 테스트

HINT
이 문제가 실제로 open(path, O_WRONLY | O_CREAT | O_TRUNC) 같은 코드를 읽을 때 바로 도움이 되는 패턴이야. #define으로 이름 붙이는 이유는 나중에 1, 2, 4라는 숫자만 봐서는 무슨 뜻인지 알기 어렵기 때문.
*/
#include<stdio.h>

#define STYLE_NONE      0
#define STYLE_BOLD      1   // 0001
#define STYLE_ITALIC    2   // 0010
#define STYLE_UNDERLINE 4   // 0100

void print_style(int style) {
    switch (style) {
        case STYLE_NONE:                                  printf("일반 텍스트\n"); break;
        case STYLE_BOLD:                                  printf("**볼드**\n"); break;
        case STYLE_ITALIC:                                printf("_이탤릭_\n"); break;
        case STYLE_BOLD | STYLE_ITALIC:                   printf("***볼드+이탤릭***\n"); break;
        case STYLE_BOLD | STYLE_UNDERLINE:                printf("**<u>볼드+밑줄</u>**\n"); break;
        case STYLE_ITALIC | STYLE_UNDERLINE:              printf("_<u>이탤릭+밑줄</u>_\n"); break;
        case STYLE_UNDERLINE:                             printf("<u>밑줄</u>\n"); break;
        case STYLE_BOLD | STYLE_ITALIC | STYLE_UNDERLINE: printf("***<u>이탤릭+밑줄</u>***\n"); break;

    }
}

int main() {
    print_style(STYLE_BOLD);
    print_style(STYLE_BOLD | STYLE_ITALIC);
    print_style(STYLE_BOLD | STYLE_ITALIC | STYLE_UNDERLINE);
    print_style(STYLE_ITALIC | STYLE_UNDERLINE);

    return 0;
}
