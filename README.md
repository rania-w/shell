# shell - needs a cool name



Dženis Kajević & Rania Weiss

Task 1.5

Q1: What does the mmap() function do?
mmap() is used to map files or devices into virtual memory. This system call works by manipulating a page table. It takes six arguments, and its first argument is a pointer to the address space where it will map files, and then is followed by an argument that determines the length of the address space that it needs. The third argument controls what kind of access is permitted. The fourth argument takes flags, the fifth take the file descriptor which has to be mapped, and the last one takes offset. If successful, the mmap() system call returns 0. mmap() is an alternative to the classic open() and read() system calls, but still uses them. This system call is optimal for small tasks, since it avoids multiple switches from user and kernel mode. This method is also very efficient with reading and writing into databases. Also, the mmap() syscall is more likely to fail on a 32-bit system, as opposed to a 64-bit one. This system call is only available in Linux environments.

Q2: What happens during a context switch? Do we want the OS to perform many or few context
switches? Explain.
Context switching is a method of switching from one process to another. It is helpful in sharing the CPU resources across all processes. This ensures that one process does not hog all the CPU's resources, and also that the CPU stays constantly busy as to not waste time either. When the switch occurs, the state of the first process is saved so that when it is resumed it resumes its execution properly.
There is no rule for how many context switches should occur given any parametrs. On one hand, the context switches improve response time by assuring that no time is wasted for a single process to execute completely, and on the other hand context switching itself requires time as well. It is important to determine a proper length of a time slice so that context switches do not take more time than it would to run the processes without interrupts. If the time slice is large enough, fewer context switches take place, and therefore less time is needed for context switches. However, larger time slices to suggest that one process will be hogging the CPU. Therefore it is important to find balance when deciding the length of the time slices.

The biggest challenge for this project was not being as familiar as we were hoping we were with the C programming language. Many of the things we learned during our Programming II course was not quite enough to grasp the complexity and possibilities of the language.

SOURCES:
https://www.geeksforgeeks.org/making-linux-shell-c/
https://www.asciiart.eu/mythology/unicorns
https://fuchsia.googlesource.com/fuchsia/+/refs/heads/main/examples/cowsay/cowsay.c
https://aljensencprogramming.wordpress.com/2014/05/15/the-kill-function-in-c/
https://www.youtube.com/watch?v=8hVLcyBkSXY
https://linuxhint.com/using_mmap_function_linux/
