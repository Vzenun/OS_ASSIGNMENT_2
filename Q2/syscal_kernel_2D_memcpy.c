#include <sys/syscall.h>
#include <linux/kernel.h>
#include <errno.h>

SYSCALL_DEFINE4(kernel_2D_memcopy, float **, src, float**, dest, int, k1, int, k2)
{
    float buffer[4][4]; 
    if (__copy_from_user(buffer, src, sizeof(float)* (16)))
       return -EFAULT;
    if (__copy_to_user(dest, buffer, sizeof(float)*(16)))
       return -EFAULT;
    return 0;
}