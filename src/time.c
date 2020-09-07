/*
 * tio - a simple TTY terminal I/O application
 *
 * Copyright (c) 2014-2017  Martin Lund
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "tio/error.h"
#include "tio/print.h"

static char time_string[24];

char * current_time(void)
{
    time_t t;
    struct tm *tmp;

    struct timeval tv;
    gettimeofday(&tv,NULL);

    t = tv.tv_sec;
    tmp = localtime(&t);
    if (tmp == NULL)
    {
        error_printf("Retrieving local time failed");
        exit(EXIT_FAILURE);
    }

    strftime(time_string, sizeof(time_string), "%H:%M:%S", tmp);
    snprintf(time_string + strlen(time_string), sizeof(time_string), ".%03ld", tv.tv_usec / 1000);

    return time_string;
}

void delay(long ms)
{
    struct timespec ts;

    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;

    nanosleep(&ts, NULL);
}
