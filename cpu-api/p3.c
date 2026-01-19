#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    // 1. 초기 PID 출력
    printf("hello world (pid:%d)\n", (int) getpid());

    // 2. 프로세스 복제
    int rc = fork();

    if (rc < 0) { 
        // 3. fork 실패 시 처리
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { 
        // 4. 자식 프로세스: "wc" 프로그램 실행 준비
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        char *myargs[3];
        myargs[0] = strdup("wc");      // 실행할 프로그램 이름 (word count)
        myargs[1] = strdup("p3.c");    // 인자로 전달할 파일명
        myargs[2] = NULL;              // 배열의 끝을 표시
        
        // 5. 현재 프로세스 이미지를 "wc"로 교체 (성공 시 여기서 코드가 전환됨)
        execvp(myargs[0], myargs); 
        
        // 6. execvp가 성공하면 이 코드는 메모리에서 사라지므로 실행되지 않음
        printf("this shouldn't print out");
    } else { 
        // 7. 부모 프로세스: 자식이 종료될 때까지 대기
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
               rc, wc, (int) getpid());
    }

    return 0;
}