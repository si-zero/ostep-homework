#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // 1. 동기화를 위한 임시 파일 생성
    // 부모는 이 파일이 존재할 때까지 기다릴 것입니다.
    const char *sync_file = "sync.tmp";

    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // 2. 자식 프로세스 실행
        printf("hello\n");

        // 출력을 마친 후 파일을 생성하여 부모에게 신호를 보냄
        int fd = open(sync_file, O_CREAT | O_WRONLY, S_IRWXU);
        close(fd);
    } else {
        // 3. 부모 프로세스 실행 (wait() 사용 금지)
        // 파일이 생성될 때까지 무한 루프를 돌며 기다림 (Busy Waiting)
        while (access(sync_file, F_OK) != 0) {
            // 파일이 아직 없으면 아무것도 하지 않고 대기
        }

        printf("goodbye\n");

        // 4. 사용한 임시 파일 삭제
        unlink(sync_file);
    }

    return 0;
}