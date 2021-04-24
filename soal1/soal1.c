#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int main()
{

    time_t t = time(NULL);
    while (t != 1617960119)
    {

        t = time(NULL);
    }

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

    if ((chdir("/home/mikehotel/modul_2/soalShift2/")) < 0)
    {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    ortuid = fork();
    if (ortuid == 0)
    {
        char *argv[] = {"mkdir", "Musyik", "Pyoto", "Fylm", NULL};
        execv("/bin/mkdir", argv);
    }
    while (wait(NULL) != ortuid)
        ;

    ortuid = fork();
    if (ortuid == 0)
    {
        char *argv[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-O", "Pyoto_for_Stevany.zip", "-o", "log", NULL};
        execv("/usr/bin/wget", argv);
    }
    while (wait(NULL) != ortuid)
        ;

    ortuid = fork();
    if (ortuid == 0)
    {
        char *argv[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", "-O", "Fylm_for_Stevany.zip", "-o", "log", NULL};
        execv("/usr/bin/wget", argv);
    }
    while (wait(NULL) != ortuid)
        ;

    ortuid = fork();
    if (ortuid == 0)
    {
        char *argv[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O", "Musyik_for_Stevany.zip", "-o", "log", NULL};
        execv("/usr/bin/wget", argv);
    }
    while (wait(NULL) != ortuid)
        ;

    ortuid = fork();
    if (ortuid == 0)
    {
        sleep(20);
        char *argv[] = {"unzip", "Musyik_for_Stevany.zip", NULL};
        execv("/usr/bin/unzip", argv);
    }
    while (wait(NULL) != ortuid)
        ;

    ortuid = fork();
    if (ortuid == 0)
    {
        sleep(20);
        char *argv[] = {"unzip", "Pyoto_for_Stevany.zip", NULL};
        execv("/usr/bin/unzip", argv);
    }
    while (wait(NULL) != ortuid)
        ;

    ortuid = fork();
    if (ortuid == 0)
    {
        sleep(20);
        char *argv[] = {"unzip", "Fylm_for_Stevany.zip", NULL};
        execv("/usr/bin/unzip", argv);
    }
    while (wait(NULL) != ortuid)
        ;

    ortuid = fork();
    if (ortuid == 0)
    {
        sleep(20);
        char *argv[] = {"find", "/home/mikehotel/modul_2/soalShift2/FOTO", "-type", "f", "!", "-iname", "\*.jpg", "-delete", NULL};
        execv("/usr/bin/find", argv);
    }
    while (wait(NULL) != ortuid)
        ;

    while (t != 1617981719)
    {

        t = time(NULL);
    }

    while (1)
    {

        pid_t cucuid;
        cucuid = fork();
        int status = 5;

        while (status == 5)
        {
            if (cucuid == 0)
            {
                sleep(15);
                char *argv[] = {"rm", "-r", "/home/mikehotel/modul_2/soalShift2/Fylm", "/home/mikehotel/modul_2/soalShift2/Pyoto", "/home/mikehotel/modul_2/soalShift2/Musyik", NULL};
                execv("/usr/bin/rm", argv);
            }
            status++;
        }

        //2
        while (wait(NULL) > 0)
            ;

        cucuid = fork();

        while (status == 6)
        {
            if (cucuid == 0)
            {
                sleep(40);
                char *argv[] = {"mv", "/home/mikehotel/modul_2/soalShift2/FILM", "/home/mikehotel/modul_2/soalShift2/Fylm", NULL};
                execv("/usr/bin/mv", argv);
            }
            status++;
        }

        //3
        while (wait(NULL) > 0)
            ;

        cucuid = fork();

        while (status == 7)
        {
            if (cucuid == 0)
            {
                sleep(40);
                char *argv[] = {"mv", "/home/mikehotel/modul_2/soalShift2/MUSIK", "/home/mikehotel/modul_2/soalShift2/Musyik", NULL};
                execv("/usr/bin/mv", argv);
            }
            status++;
        }

        while (wait(NULL) > 0)
            ;

        cucuid = fork();

        while (status == 8)
        {
            if (cucuid == 0)
            {
                sleep(30);
                char *argv[] = {"mv", "/home/mikehotel/modul_2/soalShift2/FOTO", "/home/mikehotel/modul_2/soalShift2/Pyoto", NULL};
                execv("/usr/bin/mv", argv);
            }
            status++;
        }

        while (wait(NULL) != cucuid)
            ;

        while (status == 9)
        {
            sleep(80);
            char *argv[] = {"zip", "-rm", "Lopyu_Stevany", "Pyoto", "Musyik", "Fylm", NULL};
            execv("/bin/zip", argv);
        }
        status++;

        while (wait(NULL) > 0)
            ;

        sleep(10);
    }
    exit(EXIT_SUCCESS);
}
