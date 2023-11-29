void getfileblk() {
    char buf[1024] = "\0";
    FILE* infofile = fopen("/home/cyh/hdfstest/filesblk", "r");
    /*if(infofile == NULL){
        printf("err open infofile\n");
    }*/
    printf("ok\n");
    off_t offe;
    char namebuf[20];
    vector<string> path_vec;
    while (fgets(buf, 1024, infofile) != NULL) {
        if (buf[0] == 'f' && buf[1] == 'i' && buf[2] == 'l' && buf[3] == 'e') {
            printf("%d\n", strlen(buf));
            printf("%s\n", buf);
            //namebuf = buf + 5;
            strcpy(namebuf,buf+5);
            namebuf[strlen(namebuf) - 1] = '\0';
            create_file_dir(namebuf, 1);
            //fwrite(buf,sizeof(char),strlen(buf) ,inforawhd);
            //fprintf(inforawhd,"\n");
            offe = 0;
        }

        if (buf[0] == 'b' && buf[1] == 'l' && buf[2] == 'o' && buf[3] == 'c' && buf[4] == 'k') {
            //fwrite(buf,sizeof(char),strlen(buf) ,inforawhd);
            printf("%s\n", buf);
            fgets(buf, 1024, infofile);
            path_vec.push_back(buf);
            buf[strlen(buf) - 1] = '\0';
            getoneblk(buf,namebuf);
            //continue;
        }
    }
    //free(buf);
    fclose(infofile);
}