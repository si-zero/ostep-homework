#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int rc = fork();

    if (rc < 0) {
        exit(1);
    } else if (rc == 0) {
        // 1. 자식 프로세스가 wait() 호출 시도
        printf("자식: 나도 자식을 기다려볼까?\n");
        int res = wait(NULL); 
        printf("자식: wait() 결과값은 %d 입니다. (기다릴 자식이 없어서 -1 반환)\n", res);
    } else {
        // 2. 부모 프로세스가 wait() 호출
        int status;
        int wc = wait(&status); 
        printf("부모: 종료된 자식 PID는 %d, wait 반환값(wc)은 %d 입니다.\n", rc, wc);
    }
    return 0;
}