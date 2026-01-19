#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int rc = fork();

    if (rc < 0) {
        exit(1);
    } else if (rc == 0) {
        // 1. 자식 프로세스: 표준 출력(화면 출력)을 닫음
        // STDOUT_FILENO는 보통 1번 파일 디스크립터입니다.
        close(STDOUT_FILENO);

        // 2. 출력을 시도
        // 이미 출력 통로를 닫았으므로 화면에 아무것도 나오지 않아야 합니다.
        printf("자식: 이 메시지가 화면에 보일까요?\n");
        
        // 3. printf의 성공 여부를 확인하기 위해 에러 로그를 남김 (stderr는 살아있음)
        fprintf(stderr, "자식: printf를 실행했지만 화면에는 아무것도 나오지 않았을 것입니다.\n");
    } else {
        // 부모 프로세스
        wait(NULL);
        printf("부모: 자식 프로세스의 작업이 끝났습니다.\n");
    }

    return 0;
}