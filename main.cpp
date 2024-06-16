#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char** argv)
{
    int fd;
    fd = creat("./test.txt", S_IRUSR|S_IWUSR);
    if(fd == -1)
    {
        perror("create failed");
        exit(100);
    }
    printf("文件创建成功 fd = %d", fd);
    return 0;
}

