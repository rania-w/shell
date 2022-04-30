Midterminal - shell project\
\
Task 5\
\
Made by: Dženis Kajević & Rania Weiss\
\
List of files:\
.gitignore\
followingTutorial.c -> this file was used to test a lot of things, and we kept it so that you can get a glimpse of our thought process\
forkexamples\
forkexamples.c\
halp\
halp.c\
kitten\
kitten.c\
midterminal\
midterminal.c\
trash\
trash.c\
unisay\
unisay.c\
\
Instructions for compiling and running:\
everything is compiled\
compile the shell by calling: gcc -o midterminal midterminal.c -lreadline\
start the midterminal by calling ./midterminal (you will be properly guided from there)\
\
WARNING: midterminal will not be shut down with Ctrl+C\

Task 1.5\
\
Q1: What does the mmap() function do?\
mmap() is used to map files or devices into virtual memory. This system call works by manipulating a page table. It takes six arguments, and its first argument is a pointer to the address space where it will map files, and then is followed by an argument that determines the length of the address space that it needs. The third argument controls what kind of access is permitted. The fourth argument takes flags, the fifth take the file descriptor which has to be mapped, and the last one takes offset. If successful, the mmap() system call returns 0. mmap() is an alternative to the classic open() and read() system calls, but still uses them. This system call is optimal for small tasks, since it avoids multiple switches from user and kernel mode. This method is also very efficient with reading and writing into databases. Also, the mmap() syscall is more likely to fail on a 32-bit system, as opposed to a 64-bit one. This system call is only available in Linux environments.\
\
Q2: What happens during a context switch? Do we want the OS to perform many or few context
switches? Explain.\
Context switching is a method of switching from one process to another. It is helpful in sharing the CPU resources across all processes. This ensures that one process does not hog all the CPU's resources, and also that the CPU stays constantly busy as to not waste time either. When the switch occurs, the state of the first process is saved so that when it is resumed it resumes its execution properly.
There is no rule for how many context switches should occur given any parametrs. On one hand, the context switches improve response time by assuring that no time is wasted for a single process to execute completely, and on the other hand context switching itself requires time as well. It is important to determine a proper length of a time slice so that context switches do not take more time than it would to run the processes without interrupts. If the time slice is large enough, fewer context switches take place, and therefore less time is needed for context switches. However, larger time slices to suggest that one process will be hogging the CPU. Therefore it is important to find balance when deciding the length of the time slices.\
\
\
Challenges and struggles:\
The biggest challenge for this project was not being as familiar as we were hoping we were with the C programming language. Many of the things we learned during our Programming II course was not quite enough to grasp the complexity and possibilities of the language.
Not being familiar with Unix calls was troubling, piping was a bit complex as well.\
\
It was a lovely april day, snow had finally stopped falling, it seemed like spring might not be so far... And then we saw it. We saw it on LMS. We thought: "How difficult could this possibly be?" We were in for a treat.\
We first had to do a lot of research, because this was very new for us. Then we figured we need to start doing something. So we started with simple implementations like clear, cd, ls, rm, and an infinite loop for the terminal. The terminal was functioning and had color in it. The terminal was upgraded to show command history and provide autocompletion. We spent too much time picking ASCII art but we hope you think the unicorn is pretty. Then, poor Dženis watched 10h worth of materials (listed in sources) regarding Unix calls, pipes, etc. Rania was creating examples regarding system calls. Dženis implemented piping and redirecting during exams, and made Rania very worried for his general well-being. Then, we implented cat and then Dženis fixed some memory leaks (and Rania doesn't know why he looked for them but she's glad he did). Rania added help and then optimized it. Finally, we added an easter egg, have fun finding it ;)\
P.S. looking in the code is cheating for finding the easter egg.\
\
SOURCES:\
Shell analysis(1): https://www.geeksforgeeks.org/making-linux-shell-c/ \
Shell analysis(2): https://github.com/kalpishs/Unix-Shell-Implementation-in-C \
Shell analysis(3): https://github.com/TunsAdrian/Linux-Terminal \
Shell analysis(4): https://web.stonehill.edu/compsci/CS314/Assignments/Assignment2.pdf \
Shell analysis(5): https://inst.eecs.berkeley.edu/~cs162/su20/static/hw/hw2.pdf \
(l)readline: https://eli.thegreenplace.net/2016/basics-of-using-the-readline-library/ \
Unicorn ASCII: https://www.asciiart.eu/mythology/unicorns \
Cowsay analysis: https://fuchsia.googlesource.com/fuchsia/+/refs/heads/main/examples/cowsay/cowsay.c \
Kill(): https://aljensencprogramming.wordpress.com/2014/05/15/the-kill-function-in-c/ \
MMAP(1): https://www.youtube.com/watch?v=8hVLcyBkSXY \
MMAP(2): https://linuxhint.com/using_mmap_function_linux/ \
why to avoid gets(): https://blogcwi.wordpress.com/2015/04/27/gets-docx/ \
fputs() - puts() replacement: https://www.geeksforgeeks.org/fgets-gets-c-language/ \
using valgrind to optimize shell (memory leak problems): https://stackoverflow.com/questions/5134891/how-do-i-use-valgrind-to-find-memory-leaks \
valgrind analysis: https://web.stanford.edu/class/archive/cs/cs107/cs107.1222/resources/valgrind.html \
Unix Processes in C: https://youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY \
Pipes(1): https://medium.com/swlh/understanding-pipes-in-unix-with-a-sample-implementation-9fe110d36412 \
strcspn(1): https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input \
strcspn(2): https://www.tutorialspoint.com/c_standard_library/c_function_strcspn.htm \
open() and creat(): https://man7.org/linux/man-pages/man2/open.2.html \
analysis of multiple cat() implementations: https://gist.github.com/pete/665971 \
more cat: https://linuxize.com/post/linux-cat-command/ \
handling signals: https://stackoverflow.com/questions/53657516/creating-my-own-shell-handling-ctrl-z-and-then-sending-sigcont-closes-the-proce \
mode bit flags for files: https://stackoverflow.com/questions/18415904/what-does-mode-t-0644-mean \
etc...
