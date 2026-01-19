#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("현재 PID 번호 (pid:%d)\n ", (int) getpid());
    int x = 0;
    printf("포크 전 x의 값: %d\n", x); 
    int rc = fork();
    if (rc < 0) { // fork 실패; 종료
        fprintf(stderr, "fork 실패\n ");
        exit(1);
    } else if (rc == 0) { // 자식 (새 프로세스)
        x = 1;
        printf("자식 프로세스 (pid:%d)에서의 x 값: %d\n ", (int) getpid(), x);
    } else { // 부모 프로세스는 이 경로에 따라 실행한다. (main)
        int wc = wait(NULL);
        printf("부모 프로세스 (pid:%d)에서의 x 값: %d\n ", (int) getpid(), x);
    }
    return 0;
}