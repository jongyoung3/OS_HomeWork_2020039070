#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[]) {
    int pgid;
    int sig = SIGUSR1; // 보낼 시그널
    char line[MAX_LINE_LENGTH];
    int line_number = 0;
    int found_count = 0;
    int result[50]={0,};
    FILE *fp=fopen("confession.txt", "r"); // 파일 열기(읽기모드)

    if (argc != 2) {
        exit(EXIT_FAILURE);
    }

    pgid = atoi(argv[1]); // 명령줄 인자로부터 프로세스 그룹 ID를 얻음

    if (kill(-pgid, sig) == -1) { // 프로세스 그룹에 시그널 보내기
        perror("kill");
        exit(EXIT_FAILURE);
    }

    sleep(5);//메모장에 표시될때 까지 잠시 대기
    
    // 표준 입력으로부터 한 줄씩 읽기
    while (fgets(line, MAX_LINE_LENGTH, fp)) {
        line_number++; // 줄 번호 증가

        // 현재 줄에 "!!!" 문자열이 포함되어 있는지 확인
        if (strstr(line, "!!!")) {
            result[found_count]=(line_number+pgid-1);
            found_count++;
        }
    }

    if (found_count == 0) {
        printf("\"!!!\" not found.\n");
    }
    
    //결과 출력
    printf("mafia = %d\n", found_count);
    printf("citizen = %d\n", (200-found_count));
    printf("=========   mafia list  ===========\n\n");

    for(int i=0;i<found_count;i++){
        printf("%d\n",result[i]);
    }

    fclose(fp);
    return 0;
}
