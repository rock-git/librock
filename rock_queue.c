#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rock_queue.h"

/*
 * find the middle queue element if the queue has odd number of elements
 * or the first element of the queue's second part otherwise
 */

rock_queue_t *rock_queue_middle(rock_queue_t *queue)
{
    rock_queue_t  *middle, *next;

	middle = rock_queue_head(queue);
	if (middle == rock_queue_last(queue)) return middle;

	next = rock_queue_head(queue);

	for (;;)
	{
		middle = rock_queue_next(middle);
		next = rock_queue_next(next);
		if (next == rock_queue_last(queue)) return middle;

		next = rock_queue_next(next);
		if (next == rock_queue_last(queue)) return middle;
	}
}


/* the stable insertion sort */

void rock_queue_sort(rock_queue_t *queue, int (*cmp)(const rock_queue_t *, const rock_queue_t *))
{
    rock_queue_t  *q, *prev, *next;

    q = rock_queue_head(queue);
    if (q == rock_queue_last(queue)) return;

    for (q = rock_queue_next(q); q != rock_queue_sentinel(queue); q = next) 
	{
        prev = rock_queue_prev(q);
        next = rock_queue_next(q);

        rock_queue_remove(q);

        do {
            if (cmp(prev, q) <= 0) break;
            prev = rock_queue_prev(prev);

        } while (prev != rock_queue_sentinel(queue));

        rock_queue_insert_after(prev, q);
    }
}

#if 0 //debug

typedef struct rock_test rock_test_t;

struct rock_test
{
	int data;
	rock_queue_t q;
};


int main(void)
{
	int i;
	rock_queue_t h, *p;
	struct rock_test *tmp;

	rock_queue_init(&h);

	for (i = 0; i < 10; ++i)
	{
		tmp = (struct rock_test*)calloc(1, sizeof(struct rock_test));
		tmp->data = i;
		rock_queue_insert_head(&h, &tmp->q);
	}

	p = &h;
	while ((p = rock_queue_next(p)) != &h)
	{
		tmp = rock_queue_data(p, rock_test_t, q);
		printf("%d ", tmp->data);
	}

	printf("\n");
	return 0;
}

#endif
