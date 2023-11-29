#include "hdfs.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <sys/stat.h>
#include <cmath>
#include <fcntl.h>
std::vector<std::string> get_blk_pol(std::string getcmd)
{
    FILE *fp;
    fp = popen(getcmd.c_str(), "r");
    char string1[4096];
    int nread = fread(string1, 1, 4096, fp);
    std::string sysoutinfo = string1;
    pclose(fp);
    std::istringstream ss(sysoutinfo);
    std::vector<std::string> words;
    std::string word;
    while (ss >> word)
    {
        if (word[0] == 'B' && word[1] == 'P' && word[2] == '-')
            words.push_back(word);
    }
    return words;
}

int main(int argc, char **argv)
{
    int n;
    std::vector<std::string> dirs;
    std::vector<std::string> files;
    FILE *fp;
    fp = fopen("filesname", "w");
    fclose(fp);
    fp = fopen("filesblk", "w");
    fclose(fp);
    int filesname = open("./filesname", O_RDWR | O_CREAT);
    int filesblk = open("./filesblk", O_RDWR | O_CREAT);
    if (filesname == -1)
    {
        std::cout << "cannot open" << std::endl;
    }
    if (filesname == -1)
    {
        std::cout << "cannot open" << std::endl;
    }
    hdfsFS fs = hdfsConnect("default", 0);

    std::string path = "/";
    if (argc == 2)
    {
        path = argv[1];
    }

    int open(const char *pathname, int flags);
    dirs.push_back(path);

    while (dirs.size() != 0)
    {
        std::string tpath = *(dirs.end() - 1);
        dirs.pop_back();
        hdfsFileInfo *infos = hdfsListDirectory(fs, tpath.c_str(), &n);
        for (int i = 0; i < n; i++)
        {
            hdfsFileInfo *theinfo = infos + i;
            if (theinfo->mKind == kObjectKindFile)
            {
                files.push_back(theinfo->mName);
            }
            else
            {
                dirs.push_back(theinfo->mName);
            }
        }
        hdfsFreeFileInfo(infos, n);
    }

    for (int i = 0; i < files.size(); i++)
    {
        std::cout << files[i] << std::endl;
        write(filesname, files[i].c_str(), files[i].size());
        write(filesname, "\n", 1);
    }

    for (int i = 0; i < files.size(); i++)
    {
        hdfsFileInfo *fileinfo = hdfsGetPathInfo(fs, files[i].c_str());
        std::cout << files[i] << std::endl;
        int blknum = ceil((double)fileinfo->mSize / (double)fileinfo->mBlockSize);
        int cpnum = fileinfo->mReplication;
        char ***hosts = hdfsGetHosts(fs, files[i].c_str(), 0, fileinfo->mSize);
        write(filesblk, files[i].c_str(), files[i].size());
        write(filesblk, "\n", 1);
        std::string filename = files[i].c_str();
        std::string getcmd = "hdfs fsck " + filename + " -files -blocks -locations";
        char *blkstring;
        FILE *fp;
        fp = popen(getcmd.c_str(), "r");
        char string1[1024];
        std::vector<std::string> words;
                   
        /*int nread = fread(string1, 1, 20960, fp);
        std::string sysoutinfo = string1;*/
        while (!feof(fp))
        {
            fgets(string1, sizeof(string1), fp);
            std::string sysoutinfo = string1;    
            std::istringstream ss(sysoutinfo);
            std::string word;
            while (ss >> word)
            {
                if (word[0] == 'B' && word[1] == 'P' && word[2] == '-')
                    words.push_back(word);
            }
        }
        pclose(fp);
        for (int j = 0; j < blknum; j++)
        {
            if (fileinfo->mSize == 0)
                break;
            std::cout << "block" << j << std::endl;
            // std::cout << words[j] << std::endl;
            std::string outblk = "block";
            char num[15];
            sprintf(num, "%d\0", j);
            write(filesblk, outblk.c_str(), outblk.size());
            write(filesblk, num, strlen(num));
            write(filesblk, "\n", 1);
            write(filesblk, words[j].c_str(), words[j].size());
            write(filesblk, "\n", 1);
            for (int k = 0; k < cpnum; k++)
            {
                if (hosts[j][k] == NULL)
                    break;
                std::cout << hosts[j][k] << std::endl;
                char a[50];
                sprintf(a, "%s\n\0", hosts[j][k]);
                write(filesblk, a, strlen(a));
            }
        }
        hdfsFreeHosts(hosts);
    }
    close(filesname);
    close(filesblk);
    hdfsDisconnect(fs);
}