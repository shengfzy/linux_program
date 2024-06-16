#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>

#define MSGKEY 1000

struct msgbuf_s
{
    long mtype;
    char mtext[128];
};

int main()
{
    int msgid = msgget(MSGKEY, 0);

    if(-1 == msgid)
    {
        perror("msgget");
        exit(1);
    }

    struct msgbuf_s m;
    int ret;

    while(1)
    {
        memset(&m, 0, sizeof(struct msgbuf_s));
        ret = msgrcv(msgid, &m, sizeof(m.mtext), 1, 0);

        if(-1 == ret)
        {
            perror("msgrcv");
            exit(1);
        }

        if(!strcmp(m.mtext, "bye"))
        {
            break;
        }

        printf("%s\n", m.mtext);
    }

    return 0;
}
