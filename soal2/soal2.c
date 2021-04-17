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

    pid_t pid, sid; // Variabel untuk menyimpan PID

    pid = fork(); // Menyimpan PID dari Child Process

    /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }

    /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/home/lambang/Downloads/sisop/soal3/")) < 0)
    {
        exit(EXIT_FAILURE);
    }

    FILE *pFile;
    pFile = fopen("killer.sh", "w");

    if (strcmp(argv[1], "-x") == 0)
    {
        char inp[30] = {"pkill -9 -s "};
        char sid[30];
        sprintf(sid, " %d", sid);
        strcat(inp, sid);
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

    pid = fork();
    if (pid == 0)
    {
        char *argv[] = {"chmod", "+x", "killer.sh", NULL};
        execv("/bin/chmod", argv);
    }
    while (wait(NULL) != pid)
        ;

    close(STDIN_FILENO);
    close(STDERR_FILENO);
    close(STDOUT_FILENO);

    while (1)
    {
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        char now[80];
        strftime(now, 80, "%Y-%m-%d_%H:%M:%S", tm);

        pid_t child_id;
        child_id = fork();

        if (child_id == 0)
        {
            char *argv[] = {"mkdir", now, NULL};
            execv("/bin/mkdir", argv);
        }

        child_id = fork();
        if (child_id == 0)
        {

            for (int i = 0; i < 10; i++)
            {

                child_id = fork();
                if (child_id == 0)
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
                    char temp_char;
                    int index;
                    int key = 5;

                    for (index = 0; plain[index] != '\0'; ++index)
                    {
                        temp_char = plain[index];

                        if (temp_char >= 'a' && temp_char <= 'z')
                        {
                            temp_char = temp_char + key;

                            if (temp_char > 'z')
                            {
                                temp_char = temp_char - 'z' + 'a' - 1;
                            }

                            plain[index] = temp_char;
                        }
                        else if (temp_char >= 'A' && temp_char <= 'Z')
                        {
                            temp_char = temp_char + key;

                            if (temp_char > 'Z')
                            {
                                temp_char = temp_char - 'Z' + 'A' - 1;
                            }

                            plain[index] = ch;
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
            child_id = fork();
            if (child_id == 0)
            {

                char nama_file[80];
                sprintf(nama_file, "%s.zip", now);
                char *argv[] = {"zip", "-r", nama_file, now, NULL};
                execv("/usr/bin/zip", argv);
            }

            while (wait(NULL) != child_id)
                ;
            char *argv[] = {"rm", "-r", now, NULL};
            execv("/bin/rm", argv);
        }

        sleep(40);
    }
}