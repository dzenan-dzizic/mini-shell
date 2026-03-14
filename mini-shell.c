#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <sys/sysinfo.h>
#include <sys/wait.h>
#include <stdarg.h>

#define True 1 
#define False 0
#define MAX_COMMAND_LENGTH 1024

#define RED   "\033[31m"
#define RESET "\033[0m"


struct stat st = {0};

// The function receives two arrays of chars as parameters for comparasion.
int string_compare(char str1[], char str2[]){

    // Reinvented my own function on purpose.

    int a; // This variable will later be initialized (assigned value to it).
    int counter = 0;
    int counter1 = 0;

    // Iterating throught the FIRST string until the NULL character which is the END of a string in C.
    while (str1[counter] != '\0'){
       counter++;
    }

    // Iterating throught the SECOND string until the END of it.
    while (str2[counter1] != '\0'){
       counter1++;
    }

    // If the first string is longer -> They can't be equal.
    if (counter > counter1)
    {
        a = 1; // This function will return 1 if FIRST string is LONGER.
    }

    // If the second string is longer -> They can't be equal.
    else if (counter < counter1)
    {
        a = -1; // This function will return -1 if SECOND string is LONGER.
    }

    else{
        
        // This loop will check and compare every character of the two strings one by one
        // If it finds a difference (strings are not equal), function will return 1.
        for (int i = 0; i < counter;i++){
        
            if (str1[i] == str2[i]){
              // None
            }
            else if(str1[i] != str2[i]){
                a = 1;
                return a;
            }
        }
        a = 0; // If no difference is found so far (string are identical), this function will return 0.
    }
    
    return a;
        
}

// Simple function to exit the program.
void close_program(){

    puts("Exiting shell...");    
    sleep(1);
    exit(0); // No errors while exiting the program.
}

void print_working_dir(){

    char cwd[1024];

    // Printing the current directory 
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    } 
        
    // Printing an error message if getcwd returns NULL value -> Fail.
    else {
        perror("getcwd() error");
    }

}

void list_dir(){
    
    DIR *dp; // Pointer to a DIR which is needed for using the opendir() function.
    struct dirent *ep;     
    dp = opendir ("./");
    
    if (dp != NULL){
        
        while ((ep = readdir (dp)) != NULL)
        puts (ep->d_name);
        (void) closedir (dp);
    }

    else{
        perror ("Couldn't open the directory");
    }
}

void clear_screen(){

    // Cleans the screen
    printf("\033[2J\033[H");
    fflush(stdout);
}

int string_length(char *str){

    // Reinvented my own function instead of strlen() for learning purposes.
    
    int counter = 0; // Number zero
    if (str == NULL) {
        return 0;  
    }
    
    // Looping throught the string until the NULL character (end of the string) and counting.
    while (str[counter] != '\0'){
        counter ++;
    }
    
    
    return counter;
}

void trim(char *string){
// This function will "trim" the empty spaces before a string.
 
        int i = 0, j = 0;
        
        while (string[i] == ' ') i++;
        while (string[i] == '\t') i++;    
            
        while (string[j++] = string[i++]);
     
        string[strcspn(string, "\n")] = 0;
}

void change_directory(char *command){
    

    /*  Pointer to a char, it points to fifth index inside command array, this is where user will put
    the destination directory, with trim function everything will be in place.
    */
    char *path = command + 5;
    trim(path);

        // Using chdir function to change current directory.
        if (chdir(path) == 0){
            printf("Changed directory to %s\n", path);
        }
                
        else{
            puts("Change directory failed.");
        } 

}

void create_file(char *filename){
    
    FILE *fptr; // Pointer to a FILE type which will be needed for creating files etc...
    fptr = fopen(filename, "w"); // Creating a file with fopen().
    
    // Error handling, fopen returns NULL if an error happens, and we stored the value inside fptr.
    if (fptr == NULL){
        perror("Error creating the file");    
    }
    
    fclose(fptr); // Close the file
}

void remove_file(char *filename){

    // Removing a file with remove() function.
    if (remove(filename) == 0) {
        puts("File deleted successfully.");
    } 

    // Error handling
    else {
        puts("Error: Unable to delete the file.");
    }
}

void split_empty_space(char *string, char *string1, char *string2){
    
    int i = 0;
    int j = 0;

    while (string[i] != ' ' && string[i] != '\0'){ 
        string1[i] = string[i];
        i++;
    }

    string1[i] = '\0';
   
    while (string[i] == ' ' && string[i] != '\0'){
        i++;
    }

    while (string[i] != '\0'){
        string2[j] = string[i];
        i++;
        j++;
    }
               
    string2[j] = '\0';

}

void uptime(){

    // Function displays current time and date and uptime in minutes.
    struct sysinfo info;
    sysinfo(&info);

    sysinfo(&info);
    info.uptime = info.uptime / 60;

    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
       
    printf ( "Current local time and date: %s", asctime (timeinfo) );
    printf("up: %ld minutes \n", info.uptime);


}

char *append_char_array(char *string, char *string2){

    int i = 0;
    int j = 0;


    while (string[i] != '\0'){
        
        
        
        if (string[i] == '\n'){
            string[i] = '\0';
        }
         
        if (string[i] == '\t'){
            string[i] = '\0';
        }
      
        i++;  
    }
    
    while (string2[j] != '\0'){
        
        if (string2[j] == '\n'){
            string2[j] = '\0';
        }
        
        if (string2[j] == '\t'){
            string2[j] = '\0';
        }
        
        string[i] = string2[j];
        j++;
        i++;
    }

    string[i] = '\0';
    return string;
}

void rename_file(char *old_file_name, char *new_file_name){

    // Renaming the file.
    if (rename(old_file_name, new_file_name) == 0) {
        puts("File renamed successfully.");
        
    } 

    else {
        puts("Error: Unable to rename the file. File either does not exist or is not specified as an argument.");
    }
}

void make_directory(char *dir_name){
   
    if (stat(dir_name, &st) == -1) {
        mkdir(dir_name, 0700);
    }

}

void split_pipe(char *command, char *left, char *right){

    int i = 0;
    int j = 0;

    while(command[i] != '|' && command[i] != '\0'){
        left[i] = command[i];
        i++;
    }

    left[i] = '\0';

    if(command[i] == '|'){
        i++;
    }

    while(command[i] == ' ')
        i++;

    while(command[i] != '\0'){
        right[j++] = command[i++];
    }

    right[j] = '\0';
}

void launch_process(char *command){

    pid_t pid;
    int n = 0;
    int boolean = False;
    

    while (command[n] != '\0'){
        if (command[n] == '|'){
            boolean = True;
        }
        n++;
    }


    if (boolean == True){

    char left[256];
    char right[256];

    split_pipe(command, left, right);

    trim(left);
    trim(right);

    int fd[2];
    if(pipe(fd) == -1){
    perror("pipe");
    return;
}

    pid_t pid1 = fork();

    if(pid1 == 0){
        // FIRST COMMAND

        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);

        char *args1[50];
        int i = 0;
        char *token = strtok(left, " ");

        while(token != NULL){
            args1[i++] = token;
            token = strtok(NULL," ");
        }

        args1[i] = NULL;

        execvp(args1[0], args1);
        perror("Error.");
    }

    pid_t pid2 = fork();

    if(pid2 == 0){
        // SECOND COMMAND

        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        close(fd[0]);

        char *args2[50];
        int i = 0;
        char *token = strtok(right, " ");

        while(token != NULL){
            args2[i++] = token;
            token = strtok(NULL," ");
        }

        args2[i] = NULL;

        execvp(args2[0], args2);
        exit(1);
    }

    close(fd[0]);
    close(fd[1]);

    waitpid(pid1,NULL,0);
    waitpid(pid2,NULL,0);
}
    

    else if (boolean != True){
        boolean = False;
    }
    
    

    if (boolean == False){
    
    int i = 0;
    char *args[256];
    char *token = strtok(command, " ");
                
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
            
    args[i] = NULL;

    
    pid = fork();

    if (pid < 0){
        perror("fork \n");
        
    }

    else if (pid == 0){ 
        
        execvp(args[0], args);
        exit(127);              
    }
                
    else{

        int status;
        waitpid(pid, &status, 0); 
    }
    }
        
}

void copy_function(char *filename, char *src_file_name, char *dest_file_name, char *dest_file){

            struct stat sb;
            char symbol[2] = "/";
            FILE *fptr1, *fptr2;
            int c;
            
            
            trim(filename);
           
            split_empty_space(filename, src_file_name, dest_file_name);

            strcpy(dest_file, dest_file_name); 
           
            fptr1 = fopen(src_file_name, "rb");
            
            if (fptr1 == NULL)
            {
                printf("Cannot open file %s\n", src_file_name);
                return;
                
            }

            if (stat(dest_file, &sb) == 0) {
                if (S_ISDIR(sb.st_mode)){
                  //  printf("is dir.");
                 
                    append_char_array(dest_file, symbol);
                    append_char_array(dest_file, src_file_name);
                 
                }
            }

            fptr2 = fopen(dest_file, "wb");

            
           
            if (fptr2 == NULL)
            {
                printf("Cannot open file %s\n", dest_file);
                
            }

            while ((c = fgetc(fptr1)) != EOF){
                fputc(c, fptr2);
            }

           
          //  memset(dest_file, '\0', sizeof(dest_file));
            
            fclose(fptr1);
            fclose(fptr2);
}

void remove_directory(char *directory){

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

            if (remove(filepath) != 0) {
                perror(filepath);
            }
                    
            }
            }
               
            if (rmdir(directory) != 0) {
                
                perror(directory);
                return;
            }

            if(d)   closedir(d);
}


void control_flow(char *command){


        if (string_compare(command, "exit") == 0){ 
            close_program();     
        }

        else if (string_compare(command, "pwd") == 0){
            print_working_dir();  
        }

        else if(string_compare(command, "list") == 0){
            list_dir();
        }

        else if(string_compare(command, "clean") == 0){
            clear_screen();
        }

        else if(strncmp(command, "chdir", 5) == 0){
            change_directory(command);   
        }

        else if(strncmp(command, "create", 6) == 0){

            char *filename = command + 6;
            trim(filename);
            create_file(filename);
        }
      
        else if(strncmp(command, "remove", 6) == 0){
            
            char *filename = command + 6;
            trim(filename);
            remove_file(filename);
            
        }

        else if(strncmp(command, "rename", 6) == 0){
            
            char *filename = command + 6;
            trim(filename);
            char old_file_name[50];
            char new_file_name[50];
            split_empty_space(filename, old_file_name, new_file_name);
            rename_file(old_file_name, new_file_name);
            
        }
        
        else if(strncmp(command, "copy", 4) == 0){
 
            char src_file_name[50];
            char dest_file[50];
            char dest_file_name[50];
            char *filename = command + 4;
            copy_function(filename, src_file_name, dest_file_name, dest_file); 
            puts("Contents copied successfully.");
            
        }

        else if(strncmp(command, "move", 4) == 0){

            char src_file_name[50];
            char dest_file[50];
            char dest_file_name[50];
            char *filename = command + 4;
            copy_function(filename, src_file_name, dest_file_name, dest_file); 
            puts("Contents moved successfully.");
            remove(src_file_name);
            
        }

        else if(strncmp(command, "makedir", 7) == 0){

            char *dir_name = command + 7;
            trim(dir_name);
            make_directory(dir_name);
            
        }

        else if(strncmp(command, "rnmdir", 6) == 0){
            
            char *dir_name = command + 6;
            trim(dir_name);
            
            char old_dir_name[50];
            char new_dir_name[50];
            split_empty_space(dir_name, old_dir_name, new_dir_name);
          
            
            if (rename(old_dir_name, new_dir_name) == 0){
                puts("Renamed directory succesfuly.");
            }
            
            else{
                puts("Error! Rename directory failed.");
            }
            
        }
        
        else if(string_compare(command, "time") == 0){
            
            uptime();
        }
    
        else if(strncmp(command, "rmdir", 5) == 0){
            
            // Only removes directories that are empty or ONLY have files inside them. 
            // Will not work if a directory has a sub directory inside it.
            
            char *directory = command + 5;
            trim(directory);          
            remove_directory(directory);
        
            }

        
        else if(command[0] != '\0'){

            launch_process(command);
            
        }

}



int main(){

    char command[MAX_COMMAND_LENGTH];
    int n = MAX_COMMAND_LENGTH;
    
    
    while (True) {

    printf(RED "mini-shell>" RESET);

    if (!fgets(command, MAX_COMMAND_LENGTH, stdin)) break;

    if(command[0] == '\n') continue;
    
    if (strchr(command, '\n') != NULL) {
        trim(command);
        control_flow(command);
        continue;
    }

     
    char *full_cmd = malloc(MAX_COMMAND_LENGTH * 2);

    strcpy(full_cmd, command);

    fgets(full_cmd + strlen(full_cmd), MAX_COMMAND_LENGTH, stdin);

    trim(full_cmd);
    control_flow(full_cmd);

    free(full_cmd);

    }
        
        return 0;    
    }

    
