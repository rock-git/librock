#ifndef _ROCK_QUEUE_H
#define _ROCK_QUEUE_H


#define offsetof(type, data) ((unsigned int)&((type *)0)->data)

typedef struct rock_queue_s  rock_queue_t;

struct rock_queue_s
{
    rock_queue_t  *prev;
    rock_queue_t  *next;
};

#define rock_queue_init(q)                \
    (q)->prev = q;                      \
    (q)->next = q


#define rock_queue_empty(h)                \
    (h == (h)->prev)


#define rock_queue_insert_head(h, x)        \
    (x)->next = (h)->next;                \
    (x)->next->prev = x;                  \
    (x)->prev = h;                       \
    (h)->next = x


#define rock_queue_insert_after   rock_queue_insert_head


#define rock_queue_insert_tail(h, x)        \
    (x)->prev = (h)->prev;                \
    (x)->prev->next = x;                  \
    (x)->next = h;                        \
    (h)->prev = x


#define rock_queue_head(h)                   \
    (h)->next


#define rock_queue_last(h)                   \
    (h)->prev


#define rock_queue_sentinel(h)                \
    (h)


#define rock_queue_next(q)                    \
    (q)->next


#define rock_queue_prev(q)                    \
    (q)->prev



#define rock_queue_remove(x)                    \
    (x)->next->prev = (x)->prev;               \
    (x)->prev->next = (x)->next


#define rock_queue_split(h, q, n)                \
    (n)->prev = (h)->prev;                     \
    (n)->prev->next = n;                       \
    (n)->next = q;                            \
    (h)->prev = (q)->prev;                     \
    (h)->prev->next = h;                       \
    (q)->prev = n;


#define rock_queue_add(h, n)                     \
    (h)->prev->next = (n)->next;                 \
    (n)->next->prev = (h)->prev;                 \
    (h)->prev = (n)->prev;                      \
    (h)->prev->next = h;


#define rock_queue_data(q, type, link)            \
	(type *) ((unsigned char *)q - offsetof(type, link))


rock_queue_t *rock_queue_middle(rock_queue_t *queue);
void rock_queue_sort(rock_queue_t *queue, int (*cmp)(const rock_queue_t *, const rock_queue_t *)); 




#endif