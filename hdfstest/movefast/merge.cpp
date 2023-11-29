#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include<cstring>

FILE *inforawhd=fopen("/home/chen/info","w+");
FILE *rawsd=fopen("/dev/sdb","w+");


int main() {
    if(rawsd==NULL||inforawhd==NULL){
        printf("err open\n");
    }
    
    fclose(inforawhd);
    fclose(rawsd);
}