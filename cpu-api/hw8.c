#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int p[2];
    // 1. 파이프 생성 [cite: 411]
    if (pipe(p) < 0) exit(1);

    // 2. 첫 번째 자식: 여러 줄의 데이터를 보냄
    if (fork() == 0) {
        dup2(p[1], STDOUT_FILENO); // 표준 출력을 파이프 쓰기 쪽으로 연결
        close(p[0]);
        close(p[1]);
        
        // 정렬 테스트를 위해 순서가 섞인 과일 이름을 보냅니다.
        printf("Banana\nApple\nCherry\n");
        fflush(stdout);
        exit(0);
    }

    // 3. 두 번째 자식: 데이터를 받아 정렬(sort)하여 출력
    if (fork() == 0) {
        dup2(p[0], STDIN_FILENO); // 표준 입력을 파이프 읽기 쪽으로 연결
        close(p[1]);
        close(p[0]);
        
        // 윈도우와 리눅스 공용 명령어인 'sort'를 사용합니다.
        // 첫 번째 자식이 보낸 과일 이름들이 가나다순으로 정렬되어 화면에 나옵니다.
        execlp("sort", "sort", NULL);
    }

    // 4. 부모 프로세스 마무리
    close(p[0]);
    close(p[1]);
    wait(NULL);
    wait(NULL);

    return 0;
}