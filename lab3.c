#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int	flag;

void	ft_change_led(int state)
{
	if (state == 0)
		write(1, "0\n", 2);
	else
		write(1, "1\n", 2);
}	

void	ft_init(int	sig)
{
	ft_change_led(0);
	exit(0);
}

void	ft_swap_value(int sig)
{
	flag = 1;
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		fd[2];
	int		status;
	int		not_enought;
	
	if (argc == 1)
		return (0);
	if (argc == 2 && !strncmp("-h", argv[1], 2))
	{
        printf("You realy need help...\n");		
		return (0);
	}
	else
		if (pipe(fd))
			return (0);
	not_enought = atoi(argv[1]);
	pid = fork();
	if (pid == 0)
	{
		int	state;

		flag = 0;
		state = 0;
		close(fd[1]);
		signal(SIGINT, ft_init);
		signal(SIGUSR1, ft_swap_value);
		while (1)
		{
			if (flag)
			{
				if (read(fd[0], &not_enought, 4) <= 0)
					return (0);
				flag = 0;
			}
			ft_change_led(state);
			state = !state;
			usleep(not_enought);
		}
	}
	close(fd[0]);
	while (1)
	{
		scanf("%d", &not_enought);
		if (not_enought <= 0)
			break;
		write(fd[1], &not_enought, sizeof(int));
		kill(pid, SIGUSR1);
	}
	return (0);
}
