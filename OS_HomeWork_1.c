#include <stdio.h>
#include <signal.h>
#include <sys/types.h>

int main()
{
    int pid=0;
    //int temp;
    scanf("%d", pid); // 특정 프로세스의 시작 pid 값 입력받음 아니면 자동으로 pid구할 수있는 방법 찾기

    while (1)// 마피아 찾기를 위한 특정 시그널 보내기
    {
        kill(pid, 10);
        //temp=getpid();
        // if(pid==temp){

        // }
        pid++;
        sleep(1);

        if(pid==(pid+200)){
            break;
        }
    }

    return 0;
}