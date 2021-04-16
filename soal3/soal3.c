#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main(int argc, char *argv[])
{

    pid_t ortuid, anakid;

    ortuid = fork();

    if (ortuid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if (ortuid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    anakid = setsid();
    if (anakid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/home/mikehotel/modul2/soal3/")) < 0)
    {
        exit(EXIT_FAILURE);
    }

    FILE *pFile;
    pFile = fopen("killer.sh", "w");

    if (strcmp(argv[1], "-x") == 0)
    {
        char inp[30] = {"pkill -9 -s "};
        char anakid[30];
        sprintf(anakid, " %d", anakid);
        strcat(inp, anakid);
        fprintf(pFile, inp);
    }

    if (strcmp(argv[1], "-z") == 0)
    {
        char inp[30] = {"kill -9 "};
        char gpid[30];
        sprintf(gpid, " %d", getpid());
        strcat(inp, gpid);
        fprintf(pFile, inp);
    }

    fclose(pFile);

    close(STDIN_FILENO);
    close(STDERR_FILENO);
    close(STDOUT_FILENO);

    while (1)
    {
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        char now[80];
        strftime(now, 80, "%Y-%m-%d_%H:%M:%S", tm);

        pid_t cucuid;
        cucuid = fork();

        if (cucuid == 0)
        {
            char *argv[] = {"mkdir", now, NULL};
            execv("/bin/mkdir", argv);
        }

        cucuid = fork();
        if (cucuid == 0)
        {

            for (int i = 0; i < 10; i++)
            {

                cucuid = fork();
                if (cucuid == 0)
                {

                    t = time(NULL);
                    tm = localtime(&t);

                    char new_now[80], location[160], link[80];
                    strftime(new_now, 80, "%Y-%m-%d_%H:%M:%S", tm);
                    sprintf(location, "%s/%s", now, new_now);
                    sprintf(link, "https://picsum.photos/%ld", (((int)tm->tm_sec % 1000) + 50));
                    char *argv[] = {"wget", "-O", location, link, "-o", "log", NULL};
                    execv("/usr/bin/wget", argv);
                }

                sleep(5);

                if (i == 9)
                {

                    char plain[100] = {"Download Success"};
                    char ch;
                    int J;
                    int key = 5;

                    for (J = 0; plain[J] != '\0'; ++J)
                    {
                        ch = plain[J];

                        if (ch >= 'a' && ch <= 'z')
                        {
                            ch = ch + key;

                            if (ch > 'z')
                            {
                                ch = ch - 'z' + 'a' - 1;
                            }

                            plain[J] = ch;
                        }
                        else if (ch >= 'A' && ch <= 'Z')
                        {
                            ch = ch + key;

                            if (ch > 'Z')
                            {
                                ch = ch - 'Z' + 'A' - 1;
                            }

                            plain[J] = ch;
                        }
                    }

                    FILE *pFile;
                    char path[100];
                    strcpy(path, now);
                    strcat(path, "/success.txt");
                    pFile = fopen(path, "a+");
                    fprintf(pFile, plain);
                    fclose(pFile);
                }
            }

            while (wait(NULL) > 0)
                ;
            cucuid = fork();
            if (cucuid == 0)
            {

                char nama_file[80];
                sprintf(nama_file, "%s.zip", now);
                char *argv[] = {"zip", "-r", nama_file, now, NULL};
                execv("/usr/bin/zip", argv);
            }

            while (wait(NULL) != cucuid)
                ;
            char *argv[] = {"rm", "-r", now, NULL};
            execv("/bin/rm", argv);
        }

        sleep(40);
    }
}

