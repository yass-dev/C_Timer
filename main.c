#include "timer.h"

void	print(void *arg)
{
	char *str = (char*)arg;
	printf("PERFECT : %s !\n", str);
}

int	main(int argc, char **argv)
{
	t_timer *timer;

	timer = timer_start(5);
	timer_set_callback(timer, &print, "yassou200121");
	timer_wait(timer);
}
