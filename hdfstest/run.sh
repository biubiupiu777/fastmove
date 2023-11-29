#!/bin/bash
export LD_LIBRARY_PATH=$JAVA_HOME/jre/lib/amd64/server:$LD_LIBRARY_PATH
export CLASSPATH=$($HADOOP_HOME/bin/hadoop classpath --glob):$CLASSPATH
export LD_LIBRARY_PATH=$HADOOP_HOME/lib/native:$LD_LIBRARY_PATH
