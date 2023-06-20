/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_syntax_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:01:46 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/06/06 17:06:23 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    ft_strcmpx(char *s1, char *s2)
{
    int    i;

    i = 0;
    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return (1);
        i++;
    }
    return (0);
}

int    check_pipe(char **container)
{
    int    i;

    i = 0;
    if (ft_strcmpx(container[i], "|") == 0)
    {
        printf("syntax error\n");
        return (0);
    }
    while (container[i])
        i++;
    if (ft_strcmp(container[i - 1], "|") == 0)
    {
        printf("syntax error\n");
        return (0);
    }
    return (1);
}

int    check_cout(char *str)
{
    int        i;
    char    c;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '\"')
        {
            c = str[i++];
            while (str[i] != c)
            {
                if (str[i] == '\0')
                {
                    printf("syntax error\n");
                    return (0);
                }
                i++;
            }
        }
        i++;
    }
    return (1);
}

int    check_error(char *str)
{
    int    len;

    len = ft_strlen(str);
    if (str[0] == '|' && len > 1)
        return (0);
    if (len == 2)
    {
        if (str[0] == str[1])
            return (1);
    }
    else if (len == 1)
        return (1);
    return (0);
}

int    check_redirection(char **str)
{
    int    i;

    i = 0;
    while (str[i])
    {
        if (str[i][0] == '>' || str[i][0] == '<' || str[i][0] == '|')
        {
            if (check_error(str[i]) == 0)
            {
                printf("syntax error\n");
                return (0);
            }
        }
        i++;
    }
    return (1);
}

int    check_orderly(char **str)
{
    int    i;

    i = 0;
    while (str[i])
    {
        if (str[i][0] == '>' || str[i][0] == '<')
        {
            if (str[i + 1] == NULL || str[i + 1][0] == '>' || str[i
                + 1][0] == '<' || str[i + 1][0] == '|')
            {
                printf("syntax error\n");
                return (0);
            }
        }
        i++;
    }
    return (1);
}

int    p_syntax_error(char **container, char *buffer)
{
    if(container[0] != NULL && buffer != NULL)
    {
        if (check_orderly(container) == 0 || check_pipe(container) == 0
            || check_cout(buffer) == 0 || check_redirection(container) == 0)
            return (0);
    }
    return (1);
}