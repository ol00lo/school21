#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MAX_SIZE 256

int print_file(char* filename, int* is_file_open);
int add_string_into_file(char* filename, char* str);
int encrypt_dir(char* dirname, int shift);

int main() {
    int cmp = 0;

    printf("press 1 to print file\n");
    printf("press 2 to write string into open file\n");
    printf("press 3 to encryption of all .c and clearing all .h\n");
    printf("press -1 to finish\n");

    char filename[MAX_SIZE];
    int is_file_open = 0;
    while (cmp != -1) {
        if (scanf("%d", &cmp) != 1) {
            printf("n/a");
            continue;
        }
        if (cmp == 1) {
            scanf("%s", filename);
            if (print_file(filename, &is_file_open)) printf("n/a");
        } else if (cmp == 2) {
            char str[MAX_SIZE];
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            if (strlen(str) > 0 && str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = '\0';

            if (fgets(str, sizeof(str), stdin) == NULL) {
                printf("n/a");
            } else if (!is_file_open) {
                printf("n/a");
            } else if (add_string_into_file(filename, str) || print_file(filename, &is_file_open))
                printf("n/a");
        } else if(cmp == 3){
            char path[MAX_SIZE];
            int shift;
            if(scanf("%s", path)!= 1 || scanf("%d", &shift)!=1) {
                printf("n/a");
                continue;
            }
            if (encrypt_dir(path, shift))  printf("n/a");
        } 
        else if (cmp == -1)
            break;
        else
            continue;
        printf("\n");
    }
    return 0;
}

int print_file(char* filename, int* is_file_open) {
    *is_file_open = 0;
    FILE* f = fopen(filename, "r");
    if (f == NULL) return 1;
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    *is_file_open = 1;
    if (size == 0) {
        fclose(f);
        return 1;
    }
    fseek(f, 0, SEEK_SET);
    char* curr = malloc(size + 1);
    if (curr == NULL) {
        fclose(f);
        return 1;
    }
    fread(curr, 1, size, f);
    curr[size] = '\0';
    printf("%s", curr);
    free(curr);
    fclose(f);
    return 0;
}

int add_string_into_file(char* filename, char* str) {
    FILE* f = fopen(filename, "a");
    if (f == NULL) return 1;
    fprintf(f, "%s", str);
    fclose(f);
    return 0;
}

int encrypt_file(char* filename, int shift){
    FILE * file = fopen(filename, "r+");
    if(file==NULL) return 1;
    int ch;
    while((ch=getc(file))!=EOF){
        if(ch>='A'&&ch<='Z'){   
            ch = 'A' +(ch-'A'+shift+26)%26;
        }else if(ch>='a'&&ch<='z'){
            ch = 'a' +(ch-'a'+shift+26)%26;
        }
        fseek(file, -1, SEEK_CUR);
        fputc(ch, file);
        fseek(file, 0, SEEK_CUR);
    }
    fclose(file);
    return 0;
}

int encrypt_dir(char* dirname, int shift) {
    DIR *dir = opendir(dirname);
    if(dir == NULL) return 1;
    struct dirent *entry;
    
    while((entry = readdir(dir)) != NULL){
        if(entry->d_name[0] == '.') continue;

        char filepath[MAX_SIZE];
        strcpy(filepath, dirname);
        strcat(filepath, "/");
        strcat(filepath, entry->d_name);
        int len = strlen(entry->d_name);
        if(len>2 && strcmp(&entry->d_name[len-2], ".h") == 0){
            FILE *file = fopen(filepath, "w");
            if(file!= NULL) fclose(file);
        }
        else if(len>2  && strcmp(&entry->d_name[len-2], ".c") == 0){
            if(encrypt_file(filepath, shift)) printf("n/a");
        }
    }
    closedir(dir);
    return 0;
}