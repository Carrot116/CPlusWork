//
// Created by Carrot on 16/5/30.
//

#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/utsname.h>

void GetUserInfo(){
    printf("\n------GetUserInfo------\n");
    uid_t uid;
    gid_t gid;

    struct passwd * pw;
    uid = getuid();
    gid = getgid();

    printf("User is %s\n", getlogin());
    printf("User IDs: uid=%d, gid=%d\n", uid, gid);

    pw = getpwuid(uid);
    printf("UID passwd entry:\n name=d%s, pwd=%s, uid=%d, gid=%d, home=%s, shell=%s\n",
           pw->pw_name,pw->pw_passwd, pw->pw_uid, pw->pw_gid, pw->pw_gecos, pw->pw_shell);

    pw = getpwnam("root");
    printf("UID passwd entry:\n name=%s, pwd=%s, uid=%d, gid=%d, home=%s, shell=%s\n",
           pw->pw_name,pw->pw_passwd, pw->pw_uid, pw->pw_gid, pw->pw_gecos, pw->pw_shell);
}

void GetHostInfo(){
    printf("\n------GetHostInfo------\n");
    char computer[256];
    struct utsname uts;

    if (gethostname(computer,255) != 0 || uname(&uts) < 0){
        fprintf(stderr, "Could not get host information\n");
        return;
    }

    printf("Computer host name is %s\n", computer);
    printf("System is %s on %s hardware\n", uts.sysname, uts.machine);
    printf("Node name is %s\n", uts.nodename);
    printf("Version is %s, %s\n", uts.release, uts.version);
    printf("HostID:%ld\n", gethostid());
}

/*
 * 菜单测试
 */
char* menu[]={
        (char*)("a - add new record"),
        (char*)("d - delete record"),
        (char*)("q - quit"),
        NULL,
};

int getchoice(char* greet, char*choices[]){
    int chosen = 0;
    int selected;
    char** option;
    do{
        printf("Choice: %s\n", greet);
        option = choices;
        while (*option){
            printf("%s\n",*option);
            option++;
        };

        do {
            selected = getchar();
        }while(selected == '\n');
        option = choices;
        while (*option){
            if (selected == (*option)[0]){
                chosen = 1;
                break;
            }
            option++;
        }
        if (!chosen){
            printf("Incorrect choice, select angin\n");
        }
    }while (!chosen);
    return selected;
}

void testMenu(){
    int choice = 0;

    if (!isatty(fileno(stdout))){
        fprintf(stderr, "You are not terminal!\n");
        return;
    }

    do{
        choice = getchoice((char*)("Please select an action"), menu);
        printf("You have chosen: %c\n", choice);
    }while (choice != 'q');
}

int getchoice_file(char* greet, char* choices[], FILE*in, FILE* out){
    int chosen = 0;
    int selected;
    char** option;
    do{
        fprintf(out,"Choice: %s\n", greet);
        option = choices;
        while (*option){
            fprintf(out,"%s\n",*option);
            option++;
        };

        do {
            selected = fgetc(in);
        }while(selected == '\n');
        option = choices;
        while (*option){
            if (selected == (*option)[0]){
                chosen = 1;
                break;
            }
            option++;
        }
        if (!chosen){
            fprintf(out,"Incorrect choice, select angin\n");
        }
    }while (!chosen);
    return selected;
}

void testMenu2(){
    int choice = 0;
    FILE* input;
    FILE* output;

    if (!isatty(fileno(stdout))){
        fprintf(stderr, "You are not a terminal, OK.\n");
    }

    input = fopen("/dev/tty", "r");
    output  = fopen("/dev/tty", "w");
    if (!input || !output){
        fprintf(stderr, "Unable to open /dev/tty\n");
        return;
    }
    do{
        choice = getchoice_file((char*)("Please select an action"), menu, input, output);
        printf("You have chosen: %c\n", choice);
    }while (choice != 'q');
}
