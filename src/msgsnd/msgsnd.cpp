#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>

#define MSGKEY  1000

struct msgbuf_s
{
    long mtype;
    char mtext[128];
};

int main()
{
    int msgid = msgget(MSGKEY, IPC_CREAT|IPC_EXCL|0666);
    if(-1 == msgid)
    {
        perror("msgget");
        return(1);
    }

    struct msgbuf_s m;
    int ret;

    while(1)    
    {
        memset(&m, 0, sizeof(struct msgbuf_s));
        scanf("%s", m.mtext);
        m.mtype = 1;

        ret = msgsnd(msgid, &m, sizeof(m.mtext), 0);
        if(-1 == ret)
        {
            perror("msgsnd");
        }

        if(!strcmp(m.mtext, "bye"))
        {
            break;
        }
    }

    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
