/*
** strace.c for strace.c in /home/nicolas.trognot/rendu/Instrumentation/PSU_2016_strace/STRACESAVE/srcs
**
** Made by Nicolas TROGNOT
** Login   <nicolas.trognot@epitech.net>
**
** Started on  Sat Apr 15 20:33:44 2017 Nicolas TROGNOT
** Last update Sun Apr 16 17:43:19 2017 Nicolas TROGNOT
*/

#include <stdio.h>
#include <sys/user.h>
#include "strace.h"
#include "verbose.h"

static const t_syscall	g_syscalls[] =
  {
    {"read", 3, ULONG, {INT, STRING, ULONG, 0, 0, 0}},
    {"write", 3, ULONG, {INT, STRING, ULONG, 0, 0, 0}},
    {"open", 2, INT, {STRING, INT, 0, 0, 0, 0}},
    {"close", 1, INT, {INT, 0, 0, 0, 0, 0}},
    {"stat", 2, INT, {STRING, PTR, 0, 0, 0, 0}},
    {"fstat", 2, INT, {INT, PTR, 0, 0, 0, 0}},
    {"lstat", 2, INT, {STRING, PTR, 0, 0, 0, 0}},
    {"poll", 3, INT, {PTR, UINT, INT, 0, 0, 0}},
    {"lseek", 3, INT, {INT, INT, INT, 0, 0, 0}},
    {"mmap", 6, PTR, {PTR, ULONG, INT, INT, INT, INT}},
    {"mprotect", 3, INT, {PTR, ULONG, INT, 0, 0, 0}},
    {"munmap", 2, INT, {PTR, ULONG, 0, 0, 0, 0}},
    {"brk", 1, INT, {PTR, 0, 0, 0, 0, 0}},
    {"rt_sigaction", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"rt_sigprocmask", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"rt_sigreturn", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"ioctl", 3, INT, {INT, ULONG, VARGS, 0, 0, 0}},
    {"pread64", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"pwrite64", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"readv", 3, ULONG, {INT, PTR, INT, 0, 0, 0}},
    {"writev", 3, ULONG, {INT, PTR, INT, 0, 0, 0}},
    {"access", 2, INT, {STRING, INT, 0, 0, 0, 0}},
    {"pipe", 1, INT, {INT, 0, 0, 0, 0, 0}},
    {"select", 5, INT, {INT, PTR, PTR, PTR, PTR, 0}},
    {"sched_yield", 1, INT, {0, 0, 0, 0, 0, 0}},
    {"mremap", 0, PTR, {0, 0, 0, 0, 0, 0}},
    {"msync", 3, INT, {PTR, ULONG, INT, 0, 0, 0}},
    {"mincore", 3, INT, {PTR, ULONG, PTR, 0, 0, 0}},
    {"madvise", 3, INT, {PTR, ULONG, INT, 0, 0, 0}},
    {"shmget", 3, INT, {INT, ULONG, INT, 0, 0, 0}},
    {"shmat", 3, PTR, {INT, PTR, INT, 0, 0, 0}},
    {"shmctl", 3, INT, {INT, INT, PTR, 0, 0, 0}},
    {"dup", 1, INT, {INT, 0, 0, 0, 0, 0}},
    {"dup2", 2, INT, {INT, INT, 0, 0, 0, 0}},
    {"pause", 1, INT, {0, 0, 0, 0, 0, 0}},
    {"nanosleep", 2, INT, {PTR, PTR, 0, 0, 0, 0}},
    {"getitimer", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"alarm", 1, UINT, {UINT, 0, 0, 0, 0, 0}},
    {"setitimer", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"getpid", 1, INT, {0, 0, 0, 0, 0, 0}},
    {"sendfile", 4, ULONG, {INT, INT, PTR, ULONG, 0, 0}},
    {"socket", 3, INT, {INT, INT, INT, 0, 0, 0}},
    {"connect", 3, INT, {INT, PTR, UINT, 0, 0, 0}},
    {"accept", 3, INT, {INT, PTR, PTR, 0, 0, 0}},
    {"sendto", 6, ULONG, {INT, PTR, ULONG, INT, PTR, UINT}},
    {"recvfrom", 6, ULONG, {INT, PTR, ULONG, INT, PTR, PTR}},
    {"sendmsg", 3, ULONG, {INT, PTR, INT, 0, 0, 0}},
    {"recvmsg", 3, ULONG, {INT, PTR, INT, 0, 0, 0}},
    {"shutdown", 2, INT, {INT, INT, 0, 0, 0, 0}},
    {"bind", 3, INT, {INT, PTR, UINT, 0, 0, 0}},
    {"listen", 2, INT, {INT, INT, 0, 0, 0, 0}},
    {"getsockname", 3, INT, {INT, PTR, PTR, 0, 0, 0}},
    {"getpeername", 3, INT, {INT, PTR, PTR, 0, 0, 0}},
    {"socketpair", 4, INT, {INT, INT, INT, INT, 0, 0}},
    {"setsockopt", 5, INT, {INT, INT, INT, PTR, UINT, 0}},
    {"getsockopt", 5, INT, {INT, INT, INT, PTR, PTR, 0}},
    {"clone", 0, INT, {0, 0, 0, 0, 0, 0}},
    {"fork", 1, INT, {0, 0, 0, 0, 0, 0}},
    {"vfork", 1, INT, {0, 0, 0, 0, 0, 0}},
    {"execve", 3, INT, {PTR, PTR, PTR, 0, 0, 0}},
    {"exit", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"wait4", 4, INT, {INT, PTR, INT, PTR, 0, 0}},
    {"kill", 2, INT, {INT, INT, 0, 0, 0, 0}},
    {"uname", 1, INT, {PTR, 0, 0, 0, 0, 0}},
    {"semget", 3, INT, {INT, INT, INT, 0, 0, 0}},
    {"semop", 3, INT, {INT, PTR, ULONG, 0, 0, 0}},
    {"semctl", 4, INT, {INT, INT, INT, VARGS, 0, 0}},
    {"shmdt", 1, INT, {PTR, 0, 0, 0, 0, 0}},
    {"msgget", 2, INT, {INT, INT, 0, 0, 0, 0}},
    {"msgsnd", 4, INT, {INT, PTR, ULONG, INT, 0, 0}},
    {"msgrcv", 5, ULONG, {INT, PTR, ULONG, LONG, INT, 0}},
    {"msgctl", 3, INT, {INT, INT, PTR, 0, 0, 0}},
    {"fcntl", 0, INT, {0, 0, 0, 0, 0, 0}},
    {"flock", 2, INT, {INT, INT, 0, 0, 0, 0}},
    {"fsync", 1, INT, {INT, 0, 0, 0, 0, 0}},
    {"fdatasync", 1, INT, {INT, 0, 0, 0, 0, 0}},
    {"truncate", 2, INT, {STRING, INT, 0, 0, 0, 0}},
    {"ftruncate", 2, INT, {INT, INT, 0, 0, 0, 0}},
    {"getdents", 3, INT, {UINT, PTR, UINT, 0, 0, 0}},
    {"getcwd", 2, LONG, {PTR, ULONG, 0, 0, 0, 0}},
    {"chdir", 1, INT, {STRING, 0, 0, 0, 0, 0}},
    {"fchdir", 1, INT, {INT, 0, 0, 0, 0, 0}},
    {"rename", 2, INT, {STRING, STRING, 0, 0, 0, 0}},
    {"mkdir", 2, INT, {STRING, UINT, 0, 0, 0, 0}},
    {"rmdir", 1, INT, {STRING, 0, 0, 0, 0, 0}},
    {"creat", 2, INT, {STRING, UINT, 0, 0, 0, 0}},
    {"link", 2, INT, {STRING, STRING, 0, 0, 0, 0}},
    {"unlink", 1, INT, {STRING, 0, 0, 0, 0, 0}},
    {"symlink", 2, INT, {STRING, STRING, 0, 0, 0, 0}},
    {"readlink", 3, ULONG, {STRING, STRING, ULONG, 0, 0, 0}},
    {"chmod", 2, INT, {STRING, UINT, 0, 0, 0, 0}},
    {"fchmod", 2, INT, {INT, UINT, 0, 0, 0, 0}},
    {"chown", 3, INT, {STRING, INT, INT, 0, 0, 0}},
    {"fchown", 3, INT, {INT, INT, INT, 0, 0, 0}},
    {"lchown", 3, INT, {STRING, INT, INT, 0, 0, 0}},
    {"umask", 1, UINT, {UINT, 0, 0, 0, 0, 0}},
    {"gettimeofday", 2, INT, {PTR, PTR, 0, 0, 0, 0}},
    {"getrlimit", 2, INT, {INT, PTR, 0, 0, 0, 0}},
    {"getrusage", 2, INT, {INT, PTR, 0, 0, 0, 0}},
    {"sysinfo", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"times", 1, LONG, {PTR, 0, 0, 0, 0, 0}},
    {"ptrace", 4, LONG, {INT, INT, PTR, PTR, 0, 0}},
    {"getuid", 1, INT, {0, 0, 0, 0, 0, 0}},
    {"syslog", 3, INT, {INT, STRING, INT, 0, 0, 0}},
    {"getgid", 1, INT, {0, 0, 0, 0, 0, 0}},
    {"setuid", 1, INT, {INT, 0, 0, 0, 0, 0}},
    {"setgid", 1, INT, {INT, 0, 0, 0, 0, 0}},
    {"geteuid", 1, INT, {0, 0, 0, 0, 0, 0}},
    {"getegid", 1, INT, {0, 0, 0, 0, 0, 0}},
    {"setpgid", 2, INT, {INT, INT, 0, 0, 0, 0}},
    {"getppid", 1, INT, {0, 0, 0, 0, 0, 0}},
    {"getpgrp", 0, INT, {0, 0, 0, 0, 0, 0}},
    {"setsid", 1, INT, {0, 0, 0, 0, 0, 0}},
    {"setreuid", 2, INT, {INT, INT, 0, 0, 0, 0}},
    {"setregid", 2, INT, {INT, INT, 0, 0, 0, 0}},
    {"getgroups", 2, INT, {INT, INT, 0, 0, 0, 0}},
    {"setgroups", 2, INT, {ULONG, PTR, 0, 0, 0, 0}},
    {"setresuid", 3, INT, {INT, INT, INT, 0, 0, 0}},
    {"getresuid", 3, INT, {PTR, PTR, PTR, 0, 0, 0}},
    {"setresgid", 3, INT, {INT, INT, INT, 0, 0, 0}},
    {"getresgid", 3, INT, {PTR, PTR, PTR, 0, 0, 0}},
    {"getpgid", 1, INT, {INT, 0, 0, 0, 0, 0}},
    {"setfsuid", 1, INT, {INT, 0, 0, 0, 0, 0}},
    {"setfsgid", 1, INT, {INT, 0, 0, 0, 0, 0}},
    {"getsid", 1, INT, {INT, 0, 0, 0, 0, 0}},
    {"capget", 2, INT, {LONG, LONG, 0, 0, 0, 0}},
    {"capset", 2, INT, {LONG, LONG, 0, 0, 0, 0}},
    {"rt_sigpending", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"rt_sigtimedwait", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"rt_sigqueueinfo", 3, INT, {INT, INT, PTR, 0, 0, 0}},
    {"rt_sigsuspend", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"sigaltstack", 2, INT, {PTR, PTR, 0, 0, 0, 0}},
    {"utime", 2, INT, {STRING, PTR, 0, 0, 0, 0}},
    {"mknod", 3, INT, {STRING, UINT, UINT, 0, 0, 0}},
    {"uselib", 1, INT, {STRING, 0, 0, 0, 0, 0}},
    {"personality", 1, INT, {ULONG, 0, 0, 0, 0, 0}},
    {"ustat", 2, INT, {UINT, PTR, 0, 0, 0, 0}},
    {"statfs", 2, INT, {STRING, PTR, 0, 0, 0, 0}},
    {"fstatfs", 2, INT, {INT, PTR, 0, 0, 0, 0}},
    {"sysfs", 2, INT, {INT, STRING, 0, 0, 0, 0}},
    {"getpriority", 2, INT, {INT, INT, 0, 0, 0, 0}},
    {"setpriority", 3, INT, {INT, INT, INT, 0, 0, 0}},
    {"sched_setparam", 2, INT, {INT, PTR, 0, 0, 0, 0}},
    {"sched_getparam", 2, INT, {INT, PTR, 0, 0, 0, 0}},
    {"sched_setscheduler", 3, INT, {INT, INT, PTR, 0, 0, 0}},
    {"sched_getscheduler", 1, INT, {INT, 0, 0, 0, 0, 0}},
    {"sched_get_priority_max", 1, INT, {INT, 0, 0, 0, 0, 0}},
    {"sched_get_priority_min", 1, INT, {INT, 0, 0, 0, 0, 0}},
    {"sched_rr_get_interval", 2, INT, {INT, PTR, 0, 0, 0, 0}},
    {"mlock", 2, INT, {PTR, ULONG, 0, 0, 0, 0}},
    {"munlock", 2, INT, {PTR, ULONG, 0, 0, 0, 0}},
    {"mlockall", 1, INT, {INT, 0, 0, 0, 0, 0}},
    {"munlockall", 1, INT, {0, 0, 0, 0, 0, 0}},
    {"vhangup", 1, INT, {0, 0, 0, 0, 0, 0}},
    {"modify_ldt", 3, INT, {INT, PTR, ULONG, 0, 0, 0}},
    {"pivot_root", 2, INT, {STRING, STRING, 0, 0, 0, 0}},
    {"_sysctl", 1, INT, {PTR, 0, 0, 0, 0, 0}},
    {"prctl", 5, INT, {INT, ULONG, ULONG, ULONG, ULONG, 0}},
    {"arch_prctl", 2, INT, {INT, ULONG, 0, 0, 0, 0}},
    {"adjtimex", 1, INT, {PTR, 0, 0, 0, 0, 0}},
    {"setrlimit", 2, INT, {INT, PTR, 0, 0, 0, 0}},
    {"chroot", 1, INT, {STRING, 0, 0, 0, 0, 0}},
    {"sync", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"acct", 1, INT, {STRING, 0, 0, 0, 0, 0}},
    {"settimeofday", 2, INT, {PTR, PTR, 0, 0, 0, 0}},
    {"mount", 5, INT, {STRING, STRING, STRING, ULONG, PTR, 0}},
    {"umount2", 2, INT, {STRING, INT, 0, 0, 0, 0}},
    {"swapon", 2, INT, {STRING, INT, 0, 0, 0, 0}},
    {"swapoff", 1, INT, {STRING, 0, 0, 0, 0, 0}},
    {"reboot", 4, INT, {INT, INT, INT, PTR, 0, 0}},
    {"sethostname", 2, INT, {STRING, ULONG, 0, 0, 0, 0}},
    {"setdomainname", 2, INT, {STRING, ULONG, 0, 0, 0, 0}},
    {"iopl", 1, INT, {INT, 0, 0, 0, 0, 0}},
    {"ioperm", 3, INT, {ULONG, ULONG, INT, 0, 0, 0}},
    {"create_module", 2, PTR, {STRING, ULONG, 0, 0, 0, 0}},
    {"init_module", 3, INT, {PTR, ULONG, STRING, 0, 0, 0}},
    {"delete_module", 2, INT, {STRING, INT, 0, 0, 0, 0}},
    {"get_kernel_syms", 1, INT, {PTR, 0, 0, 0, 0, 0}},
    {"query_module", 5, INT, {STRING, INT, PTR, ULONG, PTR, 0}},
    {"quotactl", 4, INT, {INT, STRING, INT, PTR, 0, 0}},
    {"nfsservctl", 3, LONG, {INT, PTR, PTR, 0, 0, 0}},
    {"getpmsg", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"putpmsg", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"afs_syscall", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"tuxcall", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"security", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"gettid", 1, INT, {0, 0, 0, 0, 0, 0}},
    {"readahead", 3, ULONG, {INT, LONG, ULONG, 0, 0, 0}},
    {"setxattr", 5, INT, {STRING, STRING, PTR, ULONG, INT, 0}},
    {"lsetxattr", 5, INT, {STRING, STRING, PTR, ULONG, INT, 0}},
    {"fsetxattr", 5, INT, {INT, STRING, PTR, ULONG, INT, 0}},
    {"getxattr", 4, ULONG, {STRING, STRING, PTR, ULONG, 0, 0}},
    {"lgetxattr", 4, ULONG, {STRING, STRING, PTR, ULONG, 0, 0}},
    {"fgetxattr", 4, ULONG, {INT, STRING, PTR, ULONG, 0, 0}},
    {"listxattr", 3, ULONG, {STRING, STRING, ULONG, 0, 0, 0}},
    {"llistxattr", 3, ULONG, {STRING, STRING, ULONG, 0, 0, 0}},
    {"flistxattr", 3, ULONG, {INT, STRING, ULONG, 0, 0, 0}},
    {"removexattr", 2, INT, {STRING, STRING, 0, 0, 0, 0}},
    {"lremovexattr", 2, INT, {STRING, STRING, 0, 0, 0, 0}},
    {"fremovexattr", 2, INT, {INT, STRING, 0, 0, 0, 0}},
    {"tkill", 2, INT, {INT, INT, 0, 0, 0, 0}},
    {"time", 1, INT, {PTR, 0, 0, 0, 0, 0}},
    {"futex", 0, INT, {0, 0, 0, 0, 0, 0}},
    {"sched_setaffinity", 3, INT, {INT, ULONG, PTR, 0, 0, 0}},
    {"sched_getaffinity", 3, INT, {INT, ULONG, PTR, 0, 0, 0}},
    {"set_thread_area", 1, INT, {PTR, 0, 0, 0, 0, 0}},
    {"io_setup", 2, INT, {ULONG, PTR, 0, 0, 0, 0}},
    {"io_destroy", 1, INT, {ULONG, 0, 0, 0, 0, 0}},
    {"io_getevents", 5, INT, {ULONG, LONG, LONG, PTR, PTR, 0}},
    {"io_submit", 3, INT, {ULONG, LONG, PTR, 0, 0, 0}},
    {"io_cancel", 3, INT, {ULONG, PTR, PTR, 0, 0, 0}},
    {"get_thread_area", 1, INT, {PTR, 0, 0, 0, 0, 0}},
    {"lookup_dcookie", 3, INT, {ULONG, STRING, ULONG, 0, 0, 0}},
    {"epoll_create", 1, INT, {INT, 0, 0, 0, 0, 0}},
    {"epoll_ctl_old", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"epoll_wait_old", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"remap_file_pages", 5, INT, {PTR, ULONG, INT, ULONG, INT, 0}},
    {"getdents64", 3, INT, {UINT, PTR, UINT, 0, 0, 0}},
    {"set_tid_address", 1, LONG, {PTR, 0, 0, 0, 0, 0}},
    {"restart_syscall", 1, INT, {0, 0, 0, 0, 0, 0}},
    {"semtimedop", 4, INT, {INT, PTR, ULONG, PTR, 0, 0}},
    {"fadvise64", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"timer_create", 3, INT, {INT, PTR, PTR, 0, 0, 0}},
    {"timer_settime", 4, INT, {UINT, INT, PTR, PTR, 0, 0}},
    {"timer_gettime", 2, INT, {UINT, PTR, 0, 0, 0, 0}},
    {"timer_getoverrun", 1, INT, {UINT, 0, 0, 0, 0, 0}},
    {"timer_delete", 1, INT, {UINT, 0, 0, 0, 0, 0}},
    {"clock_settime", 2, INT, {INT, PTR, 0, 0, 0, 0}},
    {"clock_gettime", 2, INT, {INT, PTR, 0, 0, 0, 0}},
    {"clock_getres", 2, INT, {INT, PTR, 0, 0, 0, 0}},
    {"clock_nanosleep", 4, INT, {INT, INT, PTR, PTR, 0, 0}},
    {"exit_group", 1, VOID, {INT, 0, 0, 0, 0, 0}},
    {"epoll_wait", 4, INT, {INT, PTR, INT, INT, 0, 0}},
    {"epoll_ctl", 4, INT, {INT, INT, INT, PTR, 0, 0}},
    {"tgkill", 3, INT, {INT, INT, INT, 0, 0, 0}},
    {"utimes", 2, INT, {STRING, ULONG, 0, 0, 0, 0}},
    {"vserver", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"mbind", 6, LONG, {PTR, ULONG, INT, PTR, ULONG, ULONG}},
    {"set_mempolicy", 3, LONG, {INT, PTR, ULONG, 0, 0, 0}},
    {"get_mempolicy", 5, INT, {PTR, PTR, ULONG, ULONG, ULONG, 0}},
    {"mq_open", 2, UINT, {STRING, INT, 0, 0, 0, 0}},
    {"mq_unlink", 1, INT, {STRING, 0, 0, 0, 0, 0}},
    {"mq_timedsend", 5, INT, {UINT, STRING, ULONG, UINT, PTR, 0}},
    {"mq_timedreceive", 5, ULONG, {UINT, STRING, ULONG, PTR, PTR, 0}},
    {"mq_notify", 2, INT, {UINT, PTR, 0, 0, 0, 0}},
    {"mq_getsetattr", 3, INT, {UINT, PTR, PTR, 0, 0, 0}},
    {"kexec_load", 4, LONG, {ULONG, ULONG, PTR, ULONG, 0, 0}},
    {"waitid", 4, INT, {UINT, INT, PTR, INT, 0, 0}},
    {"add_key", 5, LONG, {STRING, STRING, PTR, ULONG, LONG, 0}},
    {"request_key", 4, LONG, {STRING, STRING, STRING, LONG, 0, 0}},
    {"keyctl", 2, LONG, {INT, VARGS, 0, 0, 0, 0}},
    {"ioprio_set", 3, INT, {INT, INT, INT, 0, 0, 0}},
    {"ioprio_get", 2, INT, {INT, INT, 0, 0, 0, 0}},
    {"inotify_init", 1, INT, {0, 0, 0, 0, 0, 0}},
    {"inotify_add_watch", 3, INT, {INT, STRING, UINT, 0, 0, 0}},
    {"inotify_rm_watch", 2, INT, {INT, INT, 0, 0, 0, 0}},
    {"migrate_pages", 4, LONG, {INT, ULONG, PTR, PTR, 0, 0}},
    {"openat", 3, INT, {INT, STRING, INT, 0, 0, 0}},
    {"mkdirat", 3, INT, {INT, STRING, UINT, 0, 0, 0}},
    {"mknodat", 4, INT, {INT, STRING, UINT, UINT, 0, 0}},
    {"fchownat", 5, INT, {INT, STRING, INT, INT, INT, 0}},
    {"futimesat", 3, INT, {INT, STRING, LONG, 0, 0, 0}},
    {"newfstatat", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"unlinkat", 3, INT, {INT, STRING, INT, 0, 0, 0}},
    {"renameat", 4, INT, {INT, STRING, INT, STRING, 0, 0}},
    {"linkat", 5, INT, {INT, STRING, INT, STRING, INT, 0}},
    {"symlinkat", 3, INT, {STRING, INT, STRING, 0, 0, 0}},
    {"readlinkat", 4, ULONG, {INT, STRING, STRING, ULONG, 0, 0}},
    {"fchmodat", 4, INT, {INT, STRING, UINT, INT, 0, 0}},
    {"faccessat", 4, INT, {INT, STRING, INT, INT, 0, 0}},
    {"pselect6", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"ppoll", 4, INT, {PTR, UINT, PTR, PTR, 0, 0}},
    {"unshare", 1, INT, {INT, 0, 0, 0, 0, 0}},
    {"set_robust_list", 2, LONG, {PTR, ULONG, 0, 0, 0, 0}},
    {"get_robust_list", 3, LONG, {INT, PTR, PTR, 0, 0, 0}},
    {"splice", 6, ULONG, {INT, PTR, INT, PTR, ULONG, UINT}},
    {"tee", 4, ULONG, {INT, INT, ULONG, UINT, 0, 0}},
    {"sync_file_range", 4, INT, {INT, LONG, LONG, UINT, 0, 0}},
    {"vmsplice", 4, ULONG, {INT, PTR, ULONG, UINT, 0, 0}},
    {"move_pages", 6, LONG, {INT, ULONG, PTR, PTR, PTR, INT}},
    {"utimensat", 4, INT, {INT, STRING, LONG, INT, 0, 0}},
    {"epoll_pwait", 5, INT, {INT, PTR, INT, INT, PTR, 0}},
    {"signalfd", 3, INT, {INT, PTR, INT, 0, 0, 0}},
    {"timerfd_create", 2, INT, {INT, INT, 0, 0, 0, 0}},
    {"eventfd", 2, INT, {UINT, INT, 0, 0, 0, 0}},
    {"fallocate", 4, INT, {INT, INT, INT, INT, 0, 0}},
    {"timerfd_settime", 4, INT, {INT, INT, PTR, PTR, 0, 0}},
    {"timerfd_gettime", 2, INT, {INT, PTR, 0, 0, 0, 0}},
    {"accept4", 4, INT, {INT, PTR, PTR, INT, 0, 0}},
    {"signalfd4", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"eventfd2", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"epoll_create1", 1, INT, {INT, 0, 0, 0, 0, 0}},
    {"dup3", 3, INT, {INT, INT, INT, 0, 0, 0}},
    {"pipe2", 2, INT, {INT, INT, 0, 0, 0, 0}},
    {"inotify_init1", 1, INT, {INT, 0, 0, 0, 0, 0}},
    {"preadv", 4, ULONG, {INT, PTR, INT, INT, 0, 0}},
    {"pwritev", 4, ULONG, {INT, PTR, INT, INT, 0, 0}},
    {"rt_tgsigqueueinfo", 4, INT, {INT, INT, INT, PTR, 0, 0}},
    {"perf_event_open", 5, INT, {PTR, INT, INT, INT, ULONG, 0}},
    {"recvmmsg", 5, INT, {INT, PTR, UINT, UINT, PTR, 0}},
    {"fanotify_init", 2, INT, {UINT, UINT, 0, 0, 0, 0}},
    {"fanotify_mark", 5, INT, {INT, UINT, ULONG, INT, STRING, 0}},
    {"prlimit64", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"name_to_handle_at", 5, INT, {INT, STRING, PTR, PTR, INT, 0}},
    {"open_by_handle_at", 3, INT, {INT, PTR, INT, 0, 0, 0}},
    {"clock_adjtime", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"syncfs", 1, INT, {INT, 0, 0, 0, 0, 0}},
    {"sendmmsg", 4, INT, {INT, PTR, UINT, UINT, 0, 0}},
    {"setns", 2, INT, {INT, INT, 0, 0, 0, 0}},
    {"getcpu", 3, INT, {PTR, PTR, PTR, 0, 0, 0}},
    {"process_vm_readv", 6, ULONG, {INT, PTR, ULONG, PTR, ULONG, ULONG}},
    {"process_vm_writev", 6, ULONG, {INT, PTR, ULONG, PTR, ULONG, ULONG}},
    {"kcmp", 5, INT, {INT, INT, INT, ULONG, ULONG, 0}},
    {"finit_module", 3, INT, {INT, STRING, INT, 0, 0, 0}},
    {"sched_setattr", 3, INT, {INT, PTR, UINT, 0, 0, 0}},
    {"sched_getattr", 4, INT, {INT, PTR, UINT, UINT, 0, 0}},
    {"renameat2", 5, INT, {INT, STRING, INT, STRING, UINT, 0}},
    {"seccomp", 3, INT, {UINT, UINT, PTR, 0, 0, 0}},
    {"getrandom", 3, INT, {PTR, ULONG, UINT, 0, 0, 0}},
    {"memfd_create", 2, INT, {STRING, UINT, 0, 0, 0, 0}},
    {"kexec_file_load", 5, LONG, {INT, INT, ULONG, STRING, ULONG, 0}},
    {"bpf", 3, INT, {INT, PTR, UINT, 0, 0, 0}},
    {"execveat", 5, INT, {INT, STRING, PTR, PTR, INT, 0}},
    {"userfaultfd", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"membarrier", 2, INT, {INT, INT, 0, 0, 0, 0}},
    {"mlock2", 3, INT, {PTR, ULONG, INT, 0, 0, 0}},
    {"copy_file_range", 6, ULONG, {INT, PTR, INT, PTR, ULONG, UINT}},
    {"preadv2", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"pwritev2", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"pkey_mprotect", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"pkey_alloc", 1, VOID, {0, 0, 0, 0, 0, 0}},
    {"pkey_free", 1, VOID, {0, 0, 0, 0, 0, 0}}
  };

static const t_verbose	g_verbose[] =
  {
    {INT, &v_int},
    {UINT, &v_uint},
    {LONG, &v_long},
    {ULONG, &v_ulong},
    {STRING, &v_string},
    {VARGS, &v_vargs},
    {VOID, &v_void},
    {PTR, &v_ptr},
    {BASIC, &v_basic}
  };

static void	print_end(int nb,
			  int *mode,
			  const int offset,
			  struct user_regs_struct *regs)
{
  while (++nb < 40)
    dprintf(2, " ");
  dprintf(2, " = ");
  if (g_syscalls[offset].ret_type == VOID)
    dprintf(2, "?");
  else if (mode[0] == 1)
    g_verbose[g_syscalls[offset].ret_type - 1].display(regs->rax, mode[1]);
  else
    dprintf(2, "0x%llx", regs->rax);
  dprintf(2, "\n");
}

static void	basic_arg_display(int *i,
				  int *nb,
				  int *ov,
				  const long long unsigned int v)
{
  if (g_syscalls[ov[0]].nb_args >= *i &&
      ov[1] - 1 >= 0)
    {
      *nb = *nb + g_verbose[ov[1] - 1].display(v, ov[2]);
      *i = *i + 1;
      if (g_syscalls[ov[0]].nb_args >= *i)
	*nb = *nb + dprintf(2, ", ");
    }
}

void		string_args_display(int offset,
				    struct user_regs_struct  *regs,
				    int pid)
{
  int		nb;
  int		i;
  int		v[3];

  v[0] = offset;
  v[2] = pid;
  nb = dprintf(2, "%s(", g_syscalls[offset].name);
  i = 1;
  v[1] = g_syscalls[offset].args_type[i - 1];
  basic_arg_display(&i, &nb, v, regs->rdi);
  v[1] = g_syscalls[offset].args_type[i - 1];
  basic_arg_display(&i, &nb, v, regs->rsi);
  v[1] = g_syscalls[offset].args_type[i - 1];
  basic_arg_display(&i, &nb, v, regs->rdx);
  v[1] = g_syscalls[offset].args_type[i - 1];
  basic_arg_display(&i, &nb, v, regs->r10);
  v[1] = g_syscalls[offset].args_type[i - 1];
  basic_arg_display(&i, &nb, v, regs->r8);
  v[1] = g_syscalls[offset].args_type[i - 1];
  basic_arg_display(&i, &nb, v, regs->r9);
  nb += dprintf(2, ")");
  v[0] = 1;
  v[1] = pid;
  print_end(nb, v, offset, regs);
}

void		basic_args_display(int offset,
				   struct user_regs_struct *regs,
				   int pid)
{
  int		nb;
  int		i;
  int		v[3];

  v[0] = offset;
  v[1] = BASIC;
  v[2] = pid;
  nb = dprintf(2, "%s(", g_syscalls[offset].name);
  i = 1;
  basic_arg_display(&i, &nb, v, regs->rdi);
  basic_arg_display(&i, &nb, v, regs->rsi);
  basic_arg_display(&i, &nb, v, regs->rdx);
  basic_arg_display(&i, &nb, v, regs->r10);
  basic_arg_display(&i, &nb, v, regs->r8);
  basic_arg_display(&i, &nb, v, regs->r9);
  nb += dprintf(2, ")");
  v[0] = 0;
  print_end(nb, v, offset, regs);
}
