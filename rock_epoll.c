




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

}

int rock_epoll_del_connection(int ep, rock_connection_t *c)
{
}

int rock_epoll_add_event(int ep, rock_event_t *ev)
{
}

int rock_epoll_del_event(int ep, rock_event_t *ev)
{
}


int rock_epoll_process_events(int ep, int timer)
{

}
