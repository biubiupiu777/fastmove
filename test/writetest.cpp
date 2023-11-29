#include<iostream>
#include<string.h>
using namespace std;
#define BLOCK_SIZE (long)(128*1024*1024)
FILE *disk= fopen("/nvme_hdfs/1.txt","r+");
/*long write2disk(string path_vec,int blk_id) {
    char buf[1024];
    int len;
    long end_off;
    char *path= const_cast<char *>(path_vec.c_str());
    path[strlen(path) - 1] = '\0';
    //printf("%s",path);
    FILE *fp= fopen(path,"r");
    fseek(disk,blk_id*BLOCK_SIZE,SEEK_SET);
    if(fp==NULL)
    printf("ok\n");
    while(len=fread(buf,sizeof(char),1024,fp)){
        //printf("%d\n",len);
        fwrite(buf,sizeof(char),len,disk);
    }
    end_off=ftell(disk);
    fclose(fp);
    return end_off%BLOCK_SIZE;
}*/
int getinfo(){
    char buf[4096];
    FILE *infofp=fopen("/home/cyh/test/writeinfo","r");
    //fread(buf,1,strlen(msg)+1,stream);
    fread(buf, 1,sizeof(buf), infofp);
    int i=2560*1024;
    printf("%s",buf);
    while(i--){
        //printf("%d\n",i);
        fwrite(buf,1,sizeof(buf),disk);    
    }
}
int main(){
    getinfo();
}