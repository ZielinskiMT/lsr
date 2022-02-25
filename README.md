# lsr
Program to collect summary data about directory under given path, its subdirectories and files.

This program is a programing excersise that utilizes thread pool. 
User can specify number of threads to use and observe simple benchmark data printed out after program execution.

Usage:

./lsr [-t \<max nr of threads to use\>] \<path to a directory\>

Sample result:
```
vm@ubuntu:~/projects/lsr/build$ ./lsr -t 2 /usr/share/
Scanning...

+---------------------------------------+
/usr/share/
+---------------------------------------+
 subdirs: 6677
 regular files: 81945
 other files: 8867
 lines: 24768500
 empty lines: 935770
 non empty lines: 23832915
+---------------------------------------+

Benchmark:
   std::thread::hardware_concurrency() = 4
   threads used = 2
   Execution time: 6933.47ms
```
