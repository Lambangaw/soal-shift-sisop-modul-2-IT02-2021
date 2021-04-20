#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <wait.h>
#include <dirent.h>
#include <errno.h>

int main()
{

    pid_t child_id;
    if ((chdir("/home/mikehotel/modul2/soal2/petshop/")) < 0)
    {
        exit(EXIT_FAILURE);
    }

    child_id = fork();
    if (child_id == 0)
    {
        char *argv[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1g5rehatLEkqvuuK_eooHJXB57EfdnxVD&export=download", "-O", "pets.zip", NULL};
        execv("/bin/wget", argv);
    }
    while (wait(NULL) != child_id)
        ;

    child_id = fork();
    if (child_id == 0)
    {
        sleep(10);
        char *argv[] = {"unzip", "pets.zip", NULL};
        execv("/bin/unzip", argv);
    }
    while (wait(NULL) != child_id)
        ;

    child_id = fork();
    if (child_id == 0)
    {
        sleep(20);
        char *argv[] = {"rm", "pets.zip", NULL};
        execv("/bin/rm", argv);
    }
    while (wait(NULL) != child_id)
        ;

    child_id = fork();
    if (child_id == 0)
    {
        sleep(20);
        char *argv[] = {"rm", "-r", "musics", "apex_cheats", "unimportant_files", NULL};
        execv("/bin/rm", argv);
    }
    while (wait(NULL) != child_id)
        ;

    DIR *petdir;
    struct dirent *helperdir;
    char pet[1024];
    memset(pet, 0, sizeof pet);
    petdir = opendir("/home/mikehotel/modul2/soal2/petshop/");

    if (petdir != NULL)
    {
        while ((helperdir = readdir(petdir)))
        {
            if (strcmp(helperdir->d_name, ".") == 0 || strcmp(helperdir->d_name, "..") == 0)
            {
                continue;
            }
            sprintf(pet + strlen(pet), "%s\n", helperdir->d_name);
        }
        (void)closedir(petdir);
    }

    char *petname = strtok(pet, "\n");
    char **name = malloc(60 * sizeof(char *));
    char **nametmp = malloc(60 * sizeof(char *));
    int index = 0;

    while (petname != NULL)
    {
        if (strstr(petname, "_") != NULL)
        {
            name[index] = petname;
            nametmp[index] = petname;
            index++;
            name[index] = petname;
            nametmp[index] = petname;
            index++;
        }
        else
        {
            name[index] = petname;
            nametmp[index] = petname;
            index++;
        }

        petname = strtok(NULL, "\n");
    }

    char foldering[index][128], owner[index][128], age[index][128], temp[128];

    for (int i = 0; i < index; i++)
    {
        if (strstr(name[i], "_") == NULL)
        {
            sprintf(temp, "%s", nametmp[i]);
            char *petname2 = strtok(temp, ";");
            while (petname2 != NULL)
            {
                sprintf(foldering[i], "%s", petname2);
                petname2 = strtok(NULL, ";");
                sprintf(owner[i], "%s", petname2);
                petname2 = strtok(NULL, ";");
                ;
                strncpy(age[i], petname2, strlen(petname2) - 4);

                petname2 = NULL;
            }
        }
        else
        {
            sprintf(temp, "%s", nametmp[i]);
            char *petname2 = strtok(temp, ";");
            while (petname2 != NULL)
            {
                sprintf(foldering[i], "%s", petname2);
                petname2 = strtok(NULL, ";");
                sprintf(owner[i], "%s", petname2);
                petname2 = strtok(NULL, "_");
                sprintf(age[i], petname2);
                i = i + 1;
                petname2 = strtok(NULL, ";");
                sprintf(foldering[i], "%s", petname2);
                petname2 = strtok(NULL, ";");
                sprintf(owner[i], "%s", petname2);
                petname2 = strtok(NULL, ";");
                strncpy(age[i], petname2, strlen(petname2) - 4);
                petname2 = NULL;
            }
        }
    }

    for (int j = index - 1; j >= 0; j--)
    {
        char loc[128], path[128], txtpath[128];
        FILE *pFile;
        char abs[128] = "/home/mikehotel/modul2/soal2/petshop/";
        sprintf(loc, "/home/mikehotel/modul2/soal2/petshop/%s", foldering[j]);
        DIR *dir = opendir(loc);
        if (dir)
        {
            closedir(dir);
        }
        else if (ENOENT == errno)
        {
            child_id = fork();
            if (child_id == 0)
            {
                char *argv[] = {"mkdir", loc, NULL};
                execv("/bin/mkdir", argv);
            }
            while (wait(NULL) != child_id)
                ;
        }
        if (strstr(name[j], "_") == NULL)
        {
            child_id = fork();
            if (child_id == 0)
            {
                sprintf(path, "%s/%s.jpg", loc, owner[j]);
                char *argv[] = {"mv", name[j], path, NULL};
                execv("/bin/mv", argv);
            }
            while (wait(NULL) != child_id)
                ;
        }
        else
        {
            child_id = fork();
            if (child_id == 0)
            {
                sprintf(path, "%s/%s.jpg", loc, owner[j]);
                char *argv[] = {"cp", name[j], path, NULL};
                execv("/bin/cp", argv);
            }
            while (wait(NULL) != child_id)
                ;
            sprintf(txtpath, "%s/keterangan.txt", foldering[j]);
            pFile = fopen(txtpath, "a+");
            char *txt = ""
                        "nama: %s\n"
                        "umur: %s\n\n";
            fprintf(pFile, txt, owner[j], age[j]);
            fclose(pFile);
            j = j - 1;
            child_id = fork();
            if (child_id == 0)
            {
                sprintf(path, "%s/%s.jpg", foldering[j], owner[j]);
                char *argv[] = {"mv", name[j], path, NULL};
                execv("/bin/mv", argv);
            }
            while (wait(NULL) != child_id)
                ;
        }

        sprintf(txtpath, "%s/keterangan.txt", foldering[j]);
        pFile = fopen(txtpath, "a+");
        char *txt = ""
                    "nama: %s\n"
                    "umur: %s\n\n";
        fprintf(pFile, txt, owner[j], age[j]);
        fclose(pFile);
    }

    return 0;
}
