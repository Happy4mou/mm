/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:07:43 by rchmouk           #+#    #+#             */
/*   Updated: 2023/06/20 11:18:17 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct replace_arg
{
	int		start;
	char	*tmp;
	char	*s1;
	char	*s3;
	char	*big;
}			t_arg;

void	ft_replace(char **str, int i, t_env *env)
{
	t_arg	a;

	a.start = i++;
	a.s1 = NULL;
	a.s3 = NULL;
	a.big = NULL;
	while ((*str)[i] && (*str)[i] != ' ' && (ft_isalpha((*str)[i]) == 1
			|| ft_isdigit((*str)[i]) == 1 || (*str)[i] == '_'))
		i++;
	a.tmp = ft_substr(*str, a.start + 1, i - a.start - 1);
	while (env)
	{
		if (ft_strncmp(a.tmp, env->var, ft_strlen(a.tmp)) == 0
			&& ft_strlen(a.tmp) == ft_strlen(env->var))
			break ;
		env = env->next;
	}
	a.s1 = ft_substr(*str, 0, a.start);
	a.s3 = ft_substr(*str, i, ft_strlen(*str) - i);
	if (env != NULL)
		a.s1 = replace_free(a.s1, env->val);
	a.big = ft_strjoin(a.s1, a.s3);
	str_free(a.tmp, a.s1, a.s3, *str);
	*str = a.big;
}

void	single_cout(char *str, int *i)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] == '\'')
		(*i)++;
}

int	check_heredoc(char *str, int i)
{
	int	*tab;
	int	len;
	int	x;

	len = ft_strlen(str);
	tab = string_to_nbr(str);
	x = tab[i];
	while (i > 0 && tab[i] == 0)
		i--;
	while (i > 0 && tab[i] == 1)
		i--;
	if (i > 0 && tab[i] == 2 && tab[i - 1] == 2)
	{
		if (str[i] == '<' && str[i - 1] == '<')
		{
			free(tab);
			return (1);
		}
	}
	free(tab);
	return (0);
}

void	doubl_cout(int *i, t_env *env, char **str)
{
	(*i)++;
	while ((*str)[(*i)] && (*str)[(*i)] != '\"')
	{
		if ((*str)[(*i)] == '$' && (ft_isalpha((*str)[*i + 1]) == 1
				|| ft_isdigit((*str)[*i + 1]) == 1 || (*str)[*i + 1] == '_')
			&& check_heredoc(*str, *i) == 0)
		{
			ft_replace(str, (*i), env);
			(*i) = 0;
		}
		else
			(*i)++;
	}
	if ((*str)[*i] == '\"')
		(*i)++;
}

char	*ft_expand(char *str, t_env *env, int i)
{
    char    *str2;
    str2 = ft_strdup(str);
	while (str2[i])
	{
		if (str2[i] == '\"')
			doubl_cout(&i, env, &str2);
		else if (str2[i] == '\'')
			single_cout(str2, &i);
		else
		{
			while (str2[i] && str2[i] != '\'' && str2[i] != '\"')
			{
				if (str2[i] == '$' && (ft_isalpha(str2[i + 1]) == 1
						|| ft_isdigit(str2[i + 1]) == 1 || str2[i + 1] == '_')
					&& check_heredoc(str2, i) == 0)
				{
					ft_replace(&str2, i, env);
					i = 0;
				}
				else
					i++;
			}
		}
	}
    free(str);
	return (str2);
}
