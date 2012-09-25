#ifndef _ROCK_EVENT_H
#define _ROCK_EVENT_H

typedef struct rock_event_s rock_event_t;

struct rock_event_s
{
    void            *data;

    unsigned         type:1;

    unsigned         accept:1;
    unsigned         instance:1;

    unsigned         eof:1;
    unsigned         error:1;
    unsigned         timedout:1;
    unsigned         timer_set:1;

    unsigned         delayed:1;

    unsigned         deferred_accept:1;

    unsigned         index;

    unsigned         closed:1;

    rock_event_t     *next;
    rock_event_t    **prev;
};




#endif