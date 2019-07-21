#include"../all.h"
int main(){
	return 0;
}

#if 0
软连接就是Windows里的快捷方式
硬链接就是cp -p 加 同步更新
一个文件被删除了的本质是它的i节点的链接计数减小到0了
删除源文件后硬链接还在，因为删掉的只是文件名和i节点的映射，并把i节点的链接计数减小了1，page92
/home/shensheng/link_symlink: cat test.txt
      July 2019
Su Mo Tu We Th Fr Sa
    1  2  3  4  5  6
 7  8  9 10 11 12 13
14 15 16 17 18 19 20
21 22 23 24 25 26 27
28 29 30 31

/home/shensheng/link_symlink: ln -s test.txt soft.txt
/home/shensheng/link_symlink: ls
soft.txt  test.txt
/home/shensheng/link_symlink: cat soft.txt
      July 2019
Su Mo Tu We Th Fr Sa
    1  2  3  4  5  6
 7  8  9 10 11 12 13
14 15 16 17 18 19 20
21 22 23 24 25 26 27
28 29 30 31

/home/shensheng/link_symlink: ln test.txt hard.txt
/home/shensheng/link_symlink: ls
hard.txt  soft.txt  test.txt
/home/shensheng/link_symlink: ls -l
total 8
-rw-r--r--    2 root     root          135 Jul 21 14:27 hard.txt
lrwxrwxrwx    1 root     root            8 Jul 21 14:27 soft.txt -> test.txt
-rw-r--r--    2 root     root          135 Jul 21 14:27 test.txt
/home/shensheng/link_symlink: unlink soft.txt
/home/shensheng/link_symlink: ls
hard.txt  test.txt
/home/shensheng/link_symlink: unlink hard.txt
/home/shensheng/link_symlink: ls
test.txt
/home/shensheng/link_symlink: unlink test.txt
/home/shensheng/link_symlink: ls
/home/shensheng/link_symlink:

#endif