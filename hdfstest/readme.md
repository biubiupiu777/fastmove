# 功能

读取hdfs所有文件及目录，所有块的分布情况。分别存储在当前目录的filesname，filesblk。

# 运行

运行runtest程序,默认从根目录开始

```
source run.sh
./runtest
```

如果不需要读取整个根目录，可在后面添加路径。

例如读取file单个文件文件或目录

```
./runtest /file
```

