#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define __USE_XOPEN
#include <time.h>

long long diff_tm(struct tm *a, struct tm *b)
{
    return a->tm_sec - b->tm_sec
        +60LL*(a->tm_min - b->tm_min)
        +3600LL*(a->tm_hour - b->tm_hour)
        +86400LL*(a->tm_yday - b->tm_yday)
        +(a->tm_year-70)*31536000LL
        -(a->tm_year-69)/4*86400LL
        +(a->tm_year-1)/100*86400LL
        -(a->tm_year+299)/400*86400LL
        -(b->tm_year-70)*31536000LL
        +(b->tm_year-69)/4*86400LL
        -(b->tm_year-1)/100*86400LL
        +(b->tm_year+299)/400*86400LL;
}


int main()
{
    time_t utc, local;
    char buf[100];
    const char datetime[]="2013 11 30 23 30 26 UTC"; /* hard coded date and time in UTC */

    struct tm *tp=malloc(sizeof(struct tm));
    if(tp==NULL)
    	exit(-1);

    struct tm *localt=malloc(sizeof(struct tm));
    if(localt==NULL)
    	exit(-1);

    memset(tp, 0, sizeof(struct tm));
    memset(localt, 0, sizeof(struct tm));

    printf("UTC date and time to be converted in local time: %s\n", datetime);

    /* put values of datetime into time structure *tp */
    strptime(datetime, "%Y %m %d %H %M %S %z", tp);

    /* get seconds since EPOCH for this time */
    utc=mktime(tp);
    printf("UTC date and time in seconds since EPOCH: %ld\n", utc);

    /* lets convert this UTC date and time to local date and time */

    struct tm e0={ .tm_year = 70, .tm_mday = 1 }, e1;
    /* get time_t EPOCH value for e0 (Jan. 1, 1970) */
    time_t pseudo=mktime(&e0);

    /* get gmtime for this value */
    e1=*gmtime(&pseudo);

    /* calculate local time in seconds since EPOCH */
    e0.tm_sec += utc - diff_tm(&e1, &e0);

    /* assign to local, this can all can be coded shorter but I attempted to increase clarity */
    local=e0.tm_sec;
    printf("local date and time in seconds since EPOCH: %ld\n", local);

    /* convert seconds since EPOCH for local time into localt time structure */
    localt=localtime(&local);

    /* get nicely formatted human readable time */
    strftime(buf, sizeof buf, "%Y-%m-%d %H:%M:%S %Z", localt);

    printf("local date and time: %s\n", buf);
}
