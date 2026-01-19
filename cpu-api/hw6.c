#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int rc = fork();

    if (rc < 0) {
        exit(1);
    } else if (rc == 0) {
        // 1. 자식 프로세스
        printf("자식: 나도 자식을 기다려볼까?\n");
        int res = waitpid(-1, NULL, 0); 
        printf("자식: waitpid 결과값은 %d 입니다.\n", res);
    } else {
        // 2. 부모 프로세스: wait 대신 waitpid 사용
        int status;
        int wc = waitpid(rc, &status, 0); 
        
        printf("부모: 종료된 자식 PID는 %d, waitpid 반환값(wc)은 %d 입니다.\n", rc, wc);
    }
    return 0;
}