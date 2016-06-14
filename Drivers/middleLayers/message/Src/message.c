#include "xprintf.h"
#include <stdio.h>
#include <stdarg.h>
#include "message.h"

static
void _xprintf(char *fmt, ...);

static
char buff[2048];

void MW_printf(const char* fmt, ...){
  va_list arp;
  va_start(arp, fmt);
  xvprintf(fmt, arp);
  va_end(arp);
}

void _msg(const char* type,
          const char* file,
          const char* func,
          int line,
          const char* fmt,
          ...){
  _xprintf("%-10s %-10s %-3d %-6s ", file, func, line, type);

  {
    va_list arp;
    va_start(arp, fmt);
    xvprintf(fmt, arp);
    va_end(arp);
  }

  _xprintf("\n");
}

void MW_flush(void){
  if( outptr != 0 ){
    *outptr = 0;                /* Terminate output string with a \0 */
#warning todo
    /*todo message out*/
  }
  outptr = buff;
}

static
void _xprintf(char *fmt, ...){
  va_list arp;
  va_start(arp, fmt);
  xvprintf(fmt, arp);
  va_end(arp);
}

