#ifndef TIMER_H
# define TIMER_H

# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct timeval t_val;

typedef struct	s_timer
{
	t_val		start;
	t_val		end;
	pthread_t	thread;
	pthread_t	check;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	int 		time;
	void		(*callback)(void *);
	void		*callback_arg;
}		t_timer;

t_timer	*timer_start(int ms);
void	*timer_check(void *v_timer);
void	*timer_verify(void *v_timer);
void	timer_wait(t_timer *timer);
void	timer_set_callback(t_timer *timer, void (*callback)(void *), void *arg);

#endif
