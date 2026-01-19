#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int rc = fork();

    if (rc < 0) {
        exit(1);
    } else if (rc == 0) {
        // --- 1. execl: 인자를 리스트(List)로 나열, 전체 경로 필요 ---
        // execl("/bin/ls", "ls", "-l", NULL); 

        // --- 2. execlp: 리스트 사용 + PATH 환경변수에서 파일 검색 ---
        // execlp("ls", "ls", "-l", NULL); 

        // --- 3. execle: 리스트 사용 + 새로운 환경변수(Env) 전달 ---
        // char *envp[] = {"PATH=/bin", NULL};
        // execle("/bin/ls", "ls", "-l", NULL, envp); 

        // --- 4. execv: 인자를 배열(Vector)로 전달, 전체 경로 필요 ---
        // char *args[] = {"ls", "-l", NULL};
        // execv("/bin/ls", args); 

        // --- 5. execvp: 배열 사용 + PATH 환경변수에서 파일 검색 ---
        char *args_p[] = {"ls", "-l", NULL};
        execvp("ls", args_p); // [cite: 154, 167]

        // --- 6. execve: 배열 사용 + 새로운 환경변수(Env) 전달 ---
        // char *args_e[] = {"ls", "-l", NULL};
        // char *envp_e[] = {"PATH=/bin", NULL};
        // execve("/bin/ls", args_e, envp_e); 

        // exec 성공 시 아래는 실행되지 않음
        perror("exec failed");
        exit(1);
    } else {
        wait(NULL);
    }
    return 0;
}