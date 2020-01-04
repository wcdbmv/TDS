#ifndef __INFO_H__
#define __INFO_H__

#include <stdio.h>
#include "errcodes.h"

void usage(FILE *file);
void help(void);
void my_perror(int errcode);

#endif // __INFO_H__
