#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("hello world (pid:%d)\n ", (int) getpid());
    int rc = fork();
    if (rc < 0) { // fork 실패; 종료
        fprintf(stderr, "fork failed\n ");
        exit(1);
    } else if (rc == 0) { // 자식 (새 프로세스)
        printf("hello, I am child (pid:%d)\n ", (int) getpid());
    } else { // 부모 프로세스는 이 경로에 따라 실행한다. (main)
        printf("hello, I am parent of %d (pid:%d)\n ",
               rc, (int) getpid());
    }
    return 0;
}