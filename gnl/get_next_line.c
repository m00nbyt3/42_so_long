/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 14:02:04 by ycarro            #+#    #+#             */
/*   Updated: 2021/10/25 10:51:07 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_save(char *save, char *buf);
int		srch_line(char	*str);
char	*cutme(char **ptr, int pos);
char	*ft_inic(char *save, int fd);

char	*get_next_line(int fd)
{
	int			pos;
	char		*aux;
	static char	*save[FD_SETSIZE];

	if (fd < 0 || fd > FD_SETSIZE || BUFFER_SIZE < 0)
		return (0);
	if (!(save[fd]))
	{
		save[fd] = ft_inic(save[fd], fd);
		if (!(save[fd]))
			return (0);
	}
	aux = 0;
	pos = srch_line (save[fd]);
	if (pos >= 0)
		return (cutme(&save[fd], pos));
	if (pos == -1)
		aux = ft_strdup (save[fd]);
	free (save[fd]);
	save[fd] = 0;
	return (aux);
}

char	*ft_save(char *save, char *buf)
{
	char	*str;

	if (!save)
	{
		str = ft_strdup(buf);
		if (!str)
			return (0);
	}
	else
	{
		str = ft_strjoin(save, buf);
		if (!str)
			return (0);
		free (save);
	}
	return (str);
}

int	srch_line(char	*str)
{
	int	i;

	if (str[0] == 0)
		return (-2);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*cutme(char **ptr, int pos)
{
	char	*str;
	char	*tmp;
	char	*line;

	str = *ptr;
	str[pos] = 0;
	line = ft_strdup (str);
	if (!line)
		return (0);
	tmp = ft_strdup (str + pos + 1);
	if (!tmp)
	{
		free (*ptr);
		free (line);
		return (0);
	}
	free (*ptr);
	*ptr = tmp;
	str = ft_strjoin(line, "\n");
	free (line);
	return (str);
}

char	*ft_inic(char *save, int fd)
{
	char		*buf;
	ssize_t		tam;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (0);
	tam = read (fd, buf, BUFFER_SIZE);
	if (tam <= 0)
	{
		free(buf);
		return (0);
	}
	while (tam > 0)
	{
		buf[tam] = 0;
		save = ft_save (save, buf);
		if (!save)
		{
			free (buf);
			return (0);
		}
		tam = read (fd, buf, BUFFER_SIZE);
	}
	free (buf);
	return (save);
}
