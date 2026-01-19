#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    // 1. 부모 프로세스 PID 출력
    printf("hello world (pid:%d)\n", (int) getpid());

    // 2. 새로운 프로세스 생성
    int rc = fork();

    if (rc < 0) {
        // 3. fork 실패 시 종료
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // 4. 자식 프로세스 실행 경로
        printf("hello, I am child (pid:%d)\n", (int) getpid());
    } else {
        // 5. 부모 프로세스 실행 경로
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
               rc, wc, (int) getpid());
    }

    return 0;
}