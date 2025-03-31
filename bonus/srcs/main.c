/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:53:45 by yabukirento       #+#    #+#             */
/*   Updated: 2025/03/31 13:55:42 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

__attribute__((destructor))
static void	destructor(void)
{
	system("leaks -q a.out");
}

int	main(void)
{
	int		fd;
	char	*line1;
	char	*line2;
	char	*line3;

	fd = open("test.txt", O_RDONLY);
	line1 = get_next_line(fd);
	line2 = get_next_line(fd);
	line3 = get_next_line(fd);
	printf("line1: [%s]\n", line1);
	printf("line2: [%s]\n", line2);
	printf("line3: [%s]\n", line3);
	free(line1);
	free(line2);
	free(line3);
	system("leaks a.out");
	return (EXIT_SUCCESS);
}
