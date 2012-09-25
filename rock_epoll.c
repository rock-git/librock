

#define ROCK_EVENT_READ     0
#define ROCK_EVENT_WRITE    1


#define ROCK_EVENT_OPEN     0
#define ROCK_EVENT_CLOSE    1


int rock_epoll_init(int size)
{
	int ep;

	if ((ep = epoll_create(size)) <= 0)
	{
		printf("epoll_create error: %d\n", ep);
		return -1;
	}

	return ep;
}


int rock_epoll_add_connection(int ep, rock_connection_t *c)
{
	struct epoll_event event;
	
	event.data->ptr = (void *)(c | c->read->instance);
	event.events = EPOLLIN | EPOLLOUT | EPOLLET;
	
	if (epoll_ctl(ep, EPOLL_CTL_ADD, c->fd, &event) == -1)
	{
		printf("epoll_ctl error: %d\n", errno);
		return -1;
	}
	
	c->read->active = 1;
	c->write->active = 1;
	
	return 0;
}

int rock_epoll_del_connection(int ep, int flags, rock_connection_t *c)
{
	struct epoll_event event;
	
	if (flags & ROCK_EVENT_CLOSE)
	{
		c->read->active = 0;
		c->write->active = 0;
		return 0;
	}
	
	event.data->ptr = NULL;
	event.events = 0;
	
	if (epoll_ctl(ep, EPOLL_CTL_DEL, c->fd, &event) == -1)
	{
		printf("epoll_ctl error: %d\n", errno);
		return -1;
	}
	
	c->read->active = 0;
	c->write->active = 0;
	
	return 0;
}

int rock_epoll_add_event(int ep, int eventtype, rock_event_t *ev)
{
	int op;
	rock_event_t *e;
	rock_connection_t *c;
	struct epoll_event event;
	
	c = ev->data;
	
	if (ROCK_EVENT_READ == eventtype) e = c->read;
	else e = c->write;
	
    if (e->active) op = EPOLL_CTL_MOD;
    else op = EPOLL_CTL_ADD;
    
	event.data->ptr = (void *)(c | ev->instance)
	event.events = EPOLLIN | EPOLLOUT | EPOLLET;
	
	if (epoll_ctl(ep, op, c->fd, &event) == -1)
	{
		printf("epoll_ctl error: %d\n", errno);
		return -1;
	}
	
	return 0;
}

int rock_epoll_del_event(int ep, int eventtype, int flags, rock_event_t *ev)
{
	int                  op;
	rock_event_t         *e;
	rock_connection_t    *c;
	struct epoll_event   ee;


	if (flags & ROCK_EVENT_CLOSE) 
	{
		ev->active = 0;
		return 0;
	}

	c = ev->data;

	if (ROCK_EVENT_READ == eventtype)  e = c->write;
	else e = c->read;

	if (e->active) 
	{
		op = EPOLL_CTL_MOD;
		ee.events = EPOLLIN | EPOLLOUT;
		ee.data.ptr = (void *) ((uintptr_t) c | ev->instance);
	} 
	else 
	{
		op = EPOLL_CTL_DEL;
		ee.events = 0;
		ee.data.ptr = NULL;
	}

	if (epoll_ctl(ep, op, c->fd, &ee) == -1)
	{
		printf("epoll_ctl error: %d\n", errno);
		return -1;
	}

	ev->active = 0;

	return 0;
}


int rock_epoll_process_events(int ep, int timer)
{

}
