#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h> // pid_t 정의를 위해 필요
#include <unistd.h> // kill 함수 정의를 위해 필요


int main(int argc, char *argv[]){

    int tmp;
    int tmp2=0;
    int i=0;
    int k;
    int mafia_pid[200]={0,}; // 출력할 마피아의 pid
    int mafia_num=0; // 출력할 마피아의 수

    //생성된 200개의 프로세스중 pid값이 가장 작은거 입력받기
    int pid;
    int sig=10;

    if (argc != 2) {
        fprintf(stderr, "Step: %s <Process Group ID>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid = atoi(argv[1]); // 명령줄 인자로부터 프로세스 ID를 얻음
    //scanf("%d", &pid);
    //FILE *fp=fopen("confession.txt", "w"); // 파일 열기(쓰기모드)

    //pid++ 해가면서 조건 만족할때까지 무한 반복
    while (1)
    {
        //pid=getpid();
        if (kill(pid, sig) == -1) { // 프로세스에 시그널 보내기
        perror("kill");
        exit(EXIT_FAILURE);
        }
        else{
            /*
            이 시그널에 반응을 보이는(시그널을 보내는데 성공하는?) 
            마피아 프로세스의 pid를 confession.txt에 추가하자??? 이걸 내가해야하는 건가?
            ->아님 반응 보인다는게 시그널 보내는데 성공x
            */
            //fprintf(fp,"%s\n", "mafia");
            //mafia_pid[i]=pid;
            //mafia_num++;
            printf("%d\n", pid); //테스트용
            pid++; // 다음 pid
            i++;
        }
        //SIGUSR1에 반응하는 마피아 프로세스를 찾은 후

        //생성된 200개 프로세스에 전부 시그널 보내면 반복문
        if(i>199){
            //fclose(fp);
            break;
        }
    }

    //출력
    // tmp2=(200-mafia_num);

    // printf("mafia = %d\n", mafia_num);
    // printf("citizen = %d\n", tmp2);
    // printf("=========   mafia list  ===========\n\n");

    // for(k=0; k<mafia_num; k++){
    //    printf("%d\n", mafia_pid[k]);
    // }
    
    return 0;
}