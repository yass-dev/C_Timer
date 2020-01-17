#include "timer.h"

void	*timer_check(void *v_timer)
{
	t_val	now;
	int	delta;
	t_timer	*timer;

	timer = (t_timer*)v_timer;
	while (1)
	{
		gettimeofday(&now, NULL);
		delta = now.tv_sec - timer->start.tv_sec;
		if (timer->time == delta)
		{
			pthread_mutex_lock(&timer->mutex);
			pthread_cond_signal(&timer->cond);
			pthread_mutex_unlock(&timer->mutex);
			return (NULL);
		}
	}
}

void	*timer_verify(void *arg)
{
	t_timer *timer;

	timer = (t_timer*)arg;
	while (1)
	{
		pthread_cond_wait(&timer->cond, &timer->mutex);
		timer->callback(timer->callback_arg);
		return NULL;
	}
}

t_timer	*timer_start(int ms)
{
	t_timer	*timer;
	void	*ptr;

	timer = malloc(sizeof(t_timer));
	ptr = timer;
	timer->time = ms;
	gettimeofday(&timer->start, NULL);
	pthread_create(&timer->thread, NULL, &timer_check, ptr);
	pthread_mutex_init(&timer->mutex, NULL);
	pthread_create(&timer->check, NULL, &timer_verify, ptr);
	return (timer);
}

void	timer_wait(t_timer *timer)
{
	pthread_join(timer->thread, NULL);
	pthread_join(timer->check, NULL);
}

void	timer_set_callback(t_timer *timer, void (*f)(void *), void *arg)
{
	timer->callback = f;
	timer->callback_arg = arg;
}
