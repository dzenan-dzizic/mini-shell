// mini-shell
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <stddef.h>
#include <string.h>
#include <sys/wait.h>

#define RED   "\033[31m"
#define RESET "\033[0m"


#define NUMBER 50 

struct stat st = {0};

void trim(char *cmd) {
  
    int i = 0, j = 0;

    while (cmd[i] == ' ') i++; 

    while (cmd[j++] = cmd[i++]);

}

char* concat(const char *s1, const char *s2)
{
    
    char *result = malloc(strlen(s1) + 1 + strlen(s2) + 1); 
    
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void clear_screen() {
    printf("\033[2J\033[H");
    fflush(stdout);
}


int main(){


    char command[100]; 
    
    FILE *file_pointer;

    FILE *file_pointer3; 
    FILE *file_pointer4;

    while(1){

       
     
        printf(RED "mini-shell>" RESET);
        
        fgets(command, NUMBER, stdin);
        command[strcspn(command, "\n")] = 0; 

        trim(command);
      
        if ("%d", strcmp(command, "pwd") == 0){
            
            char cwd[50];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("Current working directory: %s\n", cwd);
            } 
            else {
                
                perror("getcwd() error \n");
                
                return 1;
            }
        }
        
        else if("%d", strcmp(command, "list") == 0){
            
            DIR *d;    
            struct dirent *dir;
            d = opendir(".");
            if (d) {
                while ((dir = readdir(d)) != NULL) {
                    printf("%s\n", dir->d_name);
                }
                closedir(d);
                }
            }
            
        else if(strncmp(command, "chdir", 5) == 0){
            
                        
        char *path = command + 5;
        trim(path);

            if (chdir(path) == 0)
        {

            printf("Changed directory to %s\n", path);
        }

        else{

            printf("Change directory failed. \n");
        }


        }

        else if(strncmp(command, "create", 6) == 0){
            
            
            char *file_name = command + 6;
            trim(file_name);
            
            file_pointer = fopen(file_name, "w");
            fclose(file_pointer); 

        }
    
        else if(strncmp(command, "remove", 6) == 0){
        
            char *file = command + 6;
            trim(file);

            if (remove(file) == 0) {
                printf("File deleted successfully.\n");
            } 
            
            else {
        printf("Error: Unable to delete the file.\n");
            }
        
    }
    
        else if(strncmp(command, "makedir", 7) == 0){

            char *directory = command + 7;
            trim(directory);

            if (stat(directory, &st) == -1) {
                mkdir(directory, 0700);
            }

        }

        else if (strncmp(command, "rmdir", 5) == 0) {

            char *directory = command + 5;
            trim(directory);

            DIR *d;
            struct dirent *dir;
            d = opendir(directory);

        if (d) {
            while ((dir = readdir(d)) != NULL) {


                if (strcmp(dir->d_name, ".") == 0 || 
                    strcmp(dir->d_name, "..") == 0)
                    continue;

                char filepath[4096];
                snprintf(filepath, sizeof(filepath), "%s/%s", directory, dir->d_name);

                remove(filepath);
            }


            closedir(d);
            rmdir(directory);
        }
    }

        else if (strncmp(command, "rename", 6) == 0){

            char new_file_name[50];
            char *file_name = command + 6;
            trim(file_name);
            
            printf("Enter new name for your file: ");
            scanf("%s", new_file_name);
            
            
            int value;

           
            value = rename(file_name, new_file_name);

            
            if (!value) {
                printf("%s", "File name changed successfully \n");
            }
            else {
                perror("Error \n");
            }
        }

        else if(strcmp(command, "exit") == 0){
            
            
            printf("Exiting shell... \n");
            
            usleep(1500000);//temporary pause program
            exit(0);

        }

        else if(strcmp(command, "clear") == 0){
            
            clear_screen();
            continue;
        }

        else if(strcmp(command, "uptime") == 0){


            struct sysinfo info;
            sysinfo(&info);
            
            sysinfo(&info);
            info.uptime = info.uptime / 60;

            time_t rawtime;
            struct tm * timeinfo;

            time ( &rawtime );
            timeinfo = localtime ( &rawtime );
            printf(" \n");
            printf ( "Current local time and date: %s", asctime (timeinfo) );
            printf("up: %ld minutes \n", info.uptime);


        }
              
        else if(strncmp(command, "copy", 4) == 0){



            char *file_name_src = strtok(command + 4, " ");
            char *file_dest = strtok(NULL, " ");
         
            int c;

            file_dest = concat(file_dest, "/");
            char* s = concat(file_dest, file_name_src);


            file_pointer3 = fopen(file_name_src, "r");

                if (file_pointer3 == NULL)
                {
                    printf("Cannot open file %s\n", file_name_src);
                    continue;
                }


            file_pointer4 = fopen(s, "w");

                if (file_pointer4 == NULL)
                {
                    printf("Cannot open file %s\n", s);
                    continue;
                }

                while ((c = fgetc(file_pointer3)) != EOF)
    {
        fputc(c, file_pointer4);
    }

    printf("Contents copied to %s\n", s);

    fclose(file_pointer3);
    fclose(file_pointer4);

    free(s);
    free(file_dest);        
        }    

        else if(strncmp(command, "move", 4) == 0){



            char *file_name_src = strtok(command + 4, " ");
            char *file_dest = strtok(NULL, " ");
         
            int c;

            file_dest = concat(file_dest, "/");
            char* s = concat(file_dest, file_name_src);


            file_pointer3 = fopen(file_name_src, "r");

                if (file_pointer3 == NULL)
                {
                    printf("Cannot open file %s\n", file_name_src);
                    continue;
                }


            file_pointer4 = fopen(s, "w");

                if (file_pointer4 == NULL)
                {
                    printf("Cannot open file %s\n", s);
                    continue;
                }

                while ((c = fgetc(file_pointer3)) != EOF)
    {
        fputc(c, file_pointer4);
    }

    printf("Contents moved to %s\n", s);

    fclose(file_pointer3);
    fclose(file_pointer4);
    remove(file_name_src);


    
    free(s);
    free(file_dest);  

      
        }

        else if (strncmp(command, "rnmdir", 6) == 0){
            char new_dir_name[50];
            char *dir_name = command + 6;
            trim(dir_name);
            
            printf("Enter new name for your directory: ");
            fgets(new_dir_name, NUMBER, stdin);
            trim(new_dir_name);
            new_dir_name[strcspn(new_dir_name, "\n")] = 0;
            
            
            
            int value;

             
           
            value = rename(dir_name, new_dir_name);

            
            if (!value) {
                printf("%s", "Directory name changed successfully \n");
            }
            else {
                perror("Error \n");
            }
        }
        
        else if (command[0] != '\0'){

            int i = 0;
            char *args[100];
            char *token = strtok(command, " ");
                while (token != NULL) {
                    args[i++] = token;
                    token = strtok(NULL, " ");
    }
            args[i] = NULL;
            pid_t pid;

            pid = fork();

            if (pid < 0){
                
                perror("fork \n");
                continue;   
            }
            if (pid == 0){

        execvp(args[0], args);

        printf("The call to execlp() was not successful.\n");
        printf("Command not found\n");
        exit(1);
    }  
      
    else{

        int status;
        waitpid(pid, &status, 0);
    }

    }
    
}
      
    return 0;
    
}


