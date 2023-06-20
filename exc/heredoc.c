/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:16:26 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/06/20 14:36:33 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_addback(t_heredoc **head, int ptr)
{
	t_heredoc	*new;
	t_heredoc	*last;

	new = malloc(sizeof(t_heredoc));
	new->data = ptr;
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

void	ft_heredoc_list(t_parc **head, t_heredoc **idfd, t_env *env)
{
	t_parc	*tmp;
	int		i;
int x = 0;
	i = 0;
	tmp = *head;
	while (tmp)
	{
		i = 0;
		while (tmp->name[i])
		{
			if (tmp->tab[i] == 4)
				x =  ft_heredoc(*head, tmp->name[i], env);
			i++;
		}
        ft_addback(idfd, x);
		tmp = tmp->next;
	}
}

int	ft_heredoc(t_parc *head, char *ptr, t_env *env)
{
	int		perout;
	int		fd[2];
	char	*buffer;
	char	*bufptr;
    
	perout = -1;
	pipe(fd);
	while (1)
	{
		buffer = get_next_line(0);
		bufptr = ft_strtrim(buffer, "\n");
		if (ft_strcmp(bufptr, ptr) == 0)
		{
			free(buffer);
			free(bufptr);
			break ;
		}
		buffer = ft_expand(buffer, env, 0);
		perout = ft_open_outfile(head);
		ft_putstr_fd(buffer, fd[1]);
		free(bufptr);
		free(buffer);
	}
	close(fd[1]);
	return (fd[0]);
}
