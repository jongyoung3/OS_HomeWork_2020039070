#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <dirent.h>

#define MAX_LINE_LENGTH 1024

int result_pid[MAX_LINE_LENGTH];

// 특정 pgid를 가진 모든 프로세스의 PID를 출력하는 함수
void find_processes_by_pgid(pid_t target_pgid) {
    DIR *dir;
    struct dirent *entry;
    char path[256];
    FILE *fp;
    pid_t pid, pgid;

    // /proc 디렉토리 열기
    dir = opendir("/proc");
    if (dir == NULL) {
        perror("opendir failed");
        return;
    }

    // /proc 디렉토리 내의 모든 항목을 순회
    while ((entry = readdir(dir)) != NULL) {
        int i=0;

        // 디렉토리 이름이 숫자로만 구성되어 있는지 확인 (프로세스 ID)
        if (entry->d_type == DT_DIR && strspn(entry->d_name, "0123456789") == strlen(entry->d_name)) {
            pid = atoi(entry->d_name); // PID로 변환

            // 해당 프로세스의 stat 파일 경로 구성
            snprintf(path, sizeof(path), "/proc/%d/stat", pid);

            // stat 파일 열기
            fp = fopen(path, "r");
            if (fp == NULL) {
                continue;
            }

            // stat 파일에서 pgid 읽기
            if (fscanf(fp, "%*d %*s %*c %d", &pgid) == 1) {
                if (pgid == target_pgid) {
                    result_pid[i]=pid;
                    // 일치하는 pgid를 가진 프로세스의 PID 출력
                    //printf("PID: %d\n", pid);
                }
            }

            fclose(fp);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    int pgid;
    int sig = SIGUSR1; // 보낼 시그널
    char line[MAX_LINE_LENGTH];
    int line_number = 0;
    int found_count = 0;
    int result[50]={0,};
    FILE *fp=fopen("confession.txt", "r"); // 파일 열기(읽기모드)
    int pid, tmp_pid;

    if (argc != 2) {
        exit(EXIT_FAILURE);
    }

    pgid = atoi(argv[1]); // 명령줄 인자로부터 프로세스 그룹 ID를 얻음
    pid=pgid;

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
            result[found_count]=(line_number+pid-1);
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
