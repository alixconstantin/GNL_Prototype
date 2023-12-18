#include "get_next_line.h"

char	*ft_extract_first_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc(sizeof(char) * i + 1);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}
char	*ft_remove_first_line(char *buffer)
{
	char	*lines;
	char	*newline_loc;
	int		i;

	newline_loc = ft_strchr(buffer, '\n');
	if (!newline_loc || !buffer)
	{
		free(buffer);
		return (NULL);
	}
	lines = malloc(sizeof(char) * ft_strlen(newline_loc));
	if (!lines)
	{
		free(buffer);
		return (NULL);
	}
	i = 0;
	newline_loc++;
	while (newline_loc[i])
	{
		lines[i] = newline_loc[i];
		i++;
	}
	lines[i] = '\0';
	free(buffer);
	return (lines);
}
char	*ft_join_free(char *str1, char *str2)
{
	char	*temp;

	temp = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (temp);
}
char	*ft_extract_buffer(int fd, char *buffer)
{
	char	*stash;
	int		read_statut;

	read_statut = 1;
	if (!buffer)
		buffer = ft_calloc(1, 1);
	while (read_statut > 0)
	{
		stash = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
		if (!stash)
			return (NULL);
		read_statut = read(fd, stash, BUFFER_SIZE);
		if (read_statut == -1)
		{
			free(stash);
			return (NULL);
		}
		buffer[read_statut] = 0;
		buffer = ft_join_free(buffer, stash);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(stash);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (buffer == NULL || !ft_strchr(buffer, '\n'))
		buffer = ft_extract_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_extract_first_line(buffer);
	buffer = ft_remove_first_line(buffer);
	return (line);
}
