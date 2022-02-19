#include <stdio.h>
#include <dirent.h>
#include <string.h>

int sentinal = 1;
const char stand_comm[7][10] = {"help", "create", "insert", "rename", "del", "exit", "dir"};


int isCommand(char pre[], char com[]){
    int i;
    int cmp1 = strcmp(pre, ">>");
    if(cmp1 == 0){
        for(i = 0; i < 7; i++){
            int cmp2 = strcmp(com, stand_comm[i]);
            if(cmp2 == 0) return i;
        }
        return 7;
    }
    return -1;

}

void main(){

    char comm[2][30];

    printf("Program is started. Enter command: \n");
    while(sentinal > 0){
        int i;
        for(i = 0; i < 2; i++){
            scanf("%s", comm[i]);
        }

        int idxCom = isCommand(comm[0], comm[1]);
        if(idxCom >= 0){
            switch(idxCom){
                case 0:{
                    printf("Defined commands:\n\t>> help\n\t>> create filename.txt\n\t>> insert filename.txt sample data\n");
                    printf("\t>> rename newname filename.txt\n\t>> del filename.txt\n\t>> dir\n");
                    break;
                }
                case 1: {
                    char file[30];
                    scanf("%s", file);
                    FILE *fp;

                    fp = fopen(file, "w");
                    if(fp == NULL){
                        printf("\n%s file is no t able opened.\n", file);
                        exit(1);
                    }

                    fprintf(fp, "%s", NULL);
                    fclose(fp);

                    printf("\n%s file is created successfully.\n", file);
                    break;
                }
                case 2:{
                    char file[30], data[100];
                    scanf("%s", file);
                    gets(data);
                    FILE *fp;

                    fp = fopen(file, "w");
                    if(fp == NULL){
                        printf("\n%s file is no t able opened.\n", file);
                        exit(1);
                    }
                    fprintf(fp, "%s", data);
                    fclose(fp);

                    printf("\nData is written in the file successfully.\n");
                    break;
                }
                case 3:{
                    char file[30], newname[100];
                    scanf("%s", newname);
                    scanf("%s", file);
                    int res  = rename(file, newname);
                    if(res == 0){
                        printf("\nThe file is renamed successfully.\n");
                    }else{
                        printf("\nThe file could not be renamed.\n");
                    }
                    break;
                }
                case 4:{
                    char file[30];
                    scanf("%s", file);
                    if(remove(file) == 0){
                        printf("\nThe files is deleted successfully.\n");
                    }else{
                        printf("\nThe file is not deleted.\n");
                    }
                    break;
                }
                case 5:{
                    sentinal = 0;
                    break;
                }
                case 6:{
                    DIR *d;
                    struct dirent *dir;
                    d = opendir(".");
                    if (d) {
                        while ((dir = readdir(d)) != NULL) {
                          printf("%s\n", dir->d_name);
                        }
                        closedir(d);
                    }
                    break;
                }
                default:{
                    printf("\nError: Command is not defined.\n");
                    break;
                }
            }
        }else{
            printf("\nError: Given command is wrong or no prefix command.\n");
            break;
        }
    }

}
