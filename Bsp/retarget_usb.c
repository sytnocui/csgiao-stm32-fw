#include <_ansi.h>
#include <_syslist.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/times.h>
#include "retarget_usb.h"
#include <stdint.h>
#include <usbd_cdc_if.h>

#if !defined(OS_USE_SEMIHOSTING)

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

int _read(int fd, char *ptr, int len)
{
    // USB虚拟串口的接收采用了中断方式，芯片接收到数据后中断回调函数会调用CDC_Receive_FS()函数接收数据，然后将数据放到接收缓存中。
    // USB接收数据的函数 CDC_Receive_FS() 是系统自行调用，用户无法调用
    // 所以直接禁止使用scanf() 所以 _read就不写了
    return -1;
}

int _write(int fd, char *ptr, int len)
{
    //改为USB CDC 发送
    USBD_StatusTypeDef hstatus;

    if (fd == STDOUT_FILENO || fd == STDERR_FILENO)
    {
//        hstatus = HAL_UART_Transmit(gHuart, (uint8_t *) ptr, len, 1);
        hstatus = CDC_Transmit_FS((uint8_t *) ptr, len);

        if (hstatus == USBD_OK)
            return len;
        else
            return EIO;
    }
    errno = EBADF;
    return -1;
}

int _close(int fd)
{
    if (fd >= STDIN_FILENO && fd <= STDERR_FILENO)
        return 0;

    errno = EBADF;
    return -1;
}

int _lseek(int fd, int ptr, int dir)
{
    (void) fd;
    (void) ptr;
    (void) dir;

    errno = EBADF;
    return -1;
}

int _isatty(int fd)
{
    if (fd >= STDIN_FILENO && fd <= STDERR_FILENO)
        return 1;

    errno = EBADF;
    return 0;
}


int _fstat(int fd, struct stat *st)
{
    if (fd >= STDIN_FILENO && fd <= STDERR_FILENO)
    {
        st->st_mode = S_IFCHR;
        return 0;
    }

    errno = EBADF;
    return 0;
}

#endif //#if !defined(OS_USE_SEMIHOSTING)