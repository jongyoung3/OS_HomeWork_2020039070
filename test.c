#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int pgid;
    int sig = SIGUSR1; // 보낼 시그널

    if (argc != 2) {
        fprintf(stderr, "Step: %s <Process Group ID>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pgid = atoi(argv[1]); // 명령줄 인자로부터 프로세스 그룹 ID를 얻음

    if (kill(-pgid, sig) == -1) { // 프로세스 그룹에 시그널 보내기
        perror("kill");
        exit(EXIT_FAILURE);
    }

    printf("Process Group %d SIGUSR1\n", pgid);
    return 0;
}
