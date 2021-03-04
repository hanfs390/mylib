#include <stdio.h>
#include <time.h>

static void print_thread_by_pid(char *prefix, int pid)
{
    char cmd[64] = {0};
    time_t now;
    struct tm *timenow;
    time(&now);
    timenow = localtime(&now);
    sprintf(cmd, "echo %d:%d:%d >> 1.log", timenow->tm_hour,timenow->tm_min,timenow->tm_sec);
    printf("%s\n", cmd);
    system(cmd);
    sprintf(cmd, "echo %s >> 1.log", prefix);
    system(cmd);
    sprintf(cmd, "echo `ps -T -p %d` >> 1.log", pid);
    system(cmd);
}
void main()
{
    print_thread_by_pid("test", getpid());
}
