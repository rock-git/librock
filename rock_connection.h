#ifndef _ROCK_CONNECTION_H
#define _ROCK_CONNECTION_H

typedef struct rock_listen_s rock_listen_t;

struct rock_listen_s
{
	int fd;

	struct sockaddr_in self_addr;
	socklen_t            socklen;    /* size of sockaddr */

	rock_connection_t connection;

	int                 backlog;
	int                 nonblocking;

	unsigned             nonblocking:1;
	unsigned             shared:1;    /* shared between threads or processes */
};

typedef struct rock_connection_s rock_connection_t;

struct rock_connection_s
{
	int fd;

	struct sockaddr_in peer_addr;
	struct sockaddr_in self_addr;
	socklen_t           socklen;    /* size of sockaddr */

	rock_listen_t *listening;

	rock_event_t *read;
	unsigned r_ev_nums;
	rock_event_t *write;
	unsigned w_ev_nums;

	char *buf;

	unsigned            buffered:8;

	unsigned            log_error:3;

	unsigned            single_connection:1;
	unsigned            unexpected_eof:1;
	unsigned            timedout:1;
	unsigned            error:1;
	unsigned            destroyed:1;

	unsigned            idle:1;
	unsigned            reusable:1;
	unsigned            close:1;

	unsigned            sendfile:1;
	unsigned            sndlowat:1;
	unsigned            tcp_nodelay:2;   /* ngx_connection_tcp_nodelay_e */
	unsigned            tcp_nopush:2;    /* ngx_connection_tcp_nopush_e */
};


#endif