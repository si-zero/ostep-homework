#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    // 1. fork() 호출 전 파일을 오픈 (파일 디스크립터 생성)
    // O_TRUNC를 사용하여 실행할 때마다 파일 내용을 새로 씁니다.
    int fd = open("test.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    
    if (fd < 0) {
        perror("open failed");
        exit(1);
    }

    // 2. 프로세스 복제
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // 3. 자식 프로세스: 파일 디스크립터 접근 및 쓰기 테스트
        const char *child_msg = "I am child, writing to the file...\n";
        printf("자식 프로세스(PID:%d): 파일 디스크립터 %d에 쓰는 중\n", (int)getpid(), fd);
        write(fd, child_msg, strlen(child_msg));
    } else {
        // 4. 부모 프로세스: 자식이 쓸 때까지 기다리지 않고 동시에 쓰기 시도
        // (동시성 테스트를 위해 wait을 쓰기 이후로 배치)
        const char *parent_msg = "I am parent, writing to the same file...\n";
        printf("부모 프로세스(PID:%d): 파일 디스크립터 %d에 쓰는 중\n", (int)getpid(), fd);
        write(fd, parent_msg, strlen(parent_msg));
        
        // 자식 프로세스 종료 대기
        wait(NULL);
        
        // 5. 작업 완료 후 파일 닫기
        close(fd);
        printf("테스트 완료. 'cat test.txt' 명령어로 결과를 확인하세요.\n");
    }

    return 0;
}