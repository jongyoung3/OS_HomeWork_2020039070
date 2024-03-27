#include <stdio.h>
#include <signal.h>

#define SIGUSR1 10

int main(){

    int tmp;
    int tmp2=0;
    int i=0;
    int k;
    int mafia_pid[200]={0,}; // 출력할 마피아의 pid
    int mafia_num=0; // 출력할 마피아의 수

    //생성된 200개의 프로세스중 pid값이 가장 작은거 입력받기
    int pid=0;
    scanf("%d", &pid);

    //pid++ 해가면서 조건 만족할때까지 무한 반복
    while (1)
    {
        tmp=kill(pid, SIGUSR1); // 해당 프로세스에 SIGUSR1 전송, 도대체 왜 kill함수 암시적 선언 오류가 남?

        if(tmp==0){ // 시그널을 보내는데 성공할 경우
            /* SIGUSR1에 반응하는 마피아 프로세스를 찾은 후
            mafia_pid[i]=pid;
            mafia_num++;*/
            pid++; // 다음 pid
        }
        else{
            continue;
        }

        //생성된 200개 프로세스에 전부 시그널 보내면 반복문
        if(pid==(pid+200)){
            break;
        }
    }

    //출력
    tmp2=(200-mafia_num);

    printf("mafia = %d\n", mafia_num);
    printf("citizen = %d\n", tmp2);
    printf("=========   mafia list  ===========\n\n");

    for(k=0; k<mafia_num; k++){
       printf("%d\n", mafia_pid[k]);
    }
    
    return 0;
}