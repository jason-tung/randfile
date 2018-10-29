#import <stdlib.h>
#import <stdio.h>
#import <fcntl.h>
#import <errno.h>
#include <string.h>
#include <zconf.h>

int rand(){
    int desc = open("/dev/random", O_RDONLY);
    if (desc < 0){
        printf("error_open: %s\n", strerror(errno));
        return -1;
    }
    int *men = malloc(sizeof(int));
    int foo = read(desc, men, sizeof(int));
    if (foo < sizeof(int)){
        printf("error_read: %s\n", strerror(errno));
        return -1;
    }
    close(foo);
    return* men;
}

int main(){
    printf("generating random nums...\n");
    int *i_holder = malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++){
        i_holder[i] = rand();
        printf("holder[%d] = %d\n", i, i_holder[i]);
    }
    printf("done!\n\n");


    printf("opening file...\n");
    int i_desc = open("men", O_WRONLY | O_CREAT, 0777);
    if (i_desc < 0){
        printf("error_open: %s\n", strerror(errno));
        return -1;
    }
    printf("done!\n\n");


    printf("writing into file...\n");
    int foo = write(i_desc, i_holder, 10 * sizeof(int));
    if (foo < 0){
        printf("write_error: %s\n", strerror(errno));
        return -1;
    }
    printf("done!\n\n");


    printf("closing file...\n");
    int bar = close(i_desc);
    if (bar < 0){
        printf("close_error: %s\n", strerror(errno));
        return -1;
    }
    printf("done!\n\n");



    //OPENING THE FILE BACK UP


    printf("opening file...\n");
    int o_desc = open("men", O_RDONLY);
    if (o_desc < 0){
        printf("error_open: %s\n", strerror(errno));
        return -1;
    }
    printf("done!\n\n");


    printf("reading from file...\n");
    int *o_holder = malloc(10 * sizeof(int));
    int o_foo = read(o_desc, o_holder, 10 * sizeof(int));
    if (o_foo < 0){
        printf("read_error: %s\n", strerror(errno));
        return -1;
    }
    printf("done!\n\n");


    printf("closing file...\n");
    int o_bar = close(o_desc);
    if (o_bar < 0){
        printf("close_error: %s\n", strerror(errno));
        return -1;
    }
    printf("done!\n\n");

    printf("reading from new array...\n");
    for (int i = 0; i < 10; i++){
        printf("holder[%d] = %d\n", i, o_holder[i]);
    }
    printf("checking if every int in each array matches...\n");
    int check = 1;
    for (int i = 0; i < 10; i++){
        int curr = i_holder[i] == o_holder[i];
        check &= curr;
        printf("i_holder[%d] == o_holder[%d]: %s\n", i, i, curr != 0 ? "true" : "false");
    }
    printf("all match: %s \n", check != 0 ? "true" : "false");
    printf("done!\n\n");
}