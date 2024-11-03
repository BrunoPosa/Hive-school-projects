/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:05:28 by tvalimak          #+#    #+#             */
/*   Updated: 2024/08/19 14:57:47 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

// Camera data parser has to handle:
/*
∗ identifier: C
∗ x,y,z coordinates of the view point: -50.0,0,20
∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
∗ FOV : Horizontal field of view in degrees in range [0,180]: 70*/

int decimal_check(char *str, int min, int max)
{
    double  value;
    char    *c;

    c = str;
    while (*c)
    {
        if (ft_isdigit(*c) && *c != '.' && *c != '-')
        {
            printf("returning 0 from decimal check 0\n");
            return 0;
        }
        c++;
    }
    value = ft_atof(str);
    if (*c == '-')
        c++;
    while (!ft_isdigit(*c))
        c++;
    if (*c == '.')
        c++;
    while (!ft_isdigit(*c))
        c++;
    if (*c != '\0' || value < min || value > max) 
    {
        printf("returning 0 from decimal check 1\n");
        return 0;
    }
    printf("returned 1 from decimal check\n");
    return 1;
}

// range for coordinates x,y,z are -10000 to 10000
int xyz_check(char *str)
{
    char    **split;
    int     i;

    i = 0;
    split = ft_split(str, ',');
    if (!split[0] || !split[1] || !split[2] || split[3])
    {
        printf("returning 0 from xyz check 0\n");
        return (free_split(split));
    }
    printf("%s\n%s\n%s\n%s", split[0], split[1], split[2], split[3]);
    while (split[i])
    {
        if (decimal_check(split[i], -10000, 10000) == 0)
        {
            printf("returning 0 from xyz check 1\n");
            return (free_split(split));
        }
        i++;
    }
    free_split(split);
    printf("returning 1 from xyz check\n");
    return (1);
}

int degree_check(char *str, int min, int max)
{
    if (ft_atoi(str) < min || ft_atoi(str) > max)
    {
        printf("returning 0 from degree_check 0\n");
        return (0);
    }
    printf("returning 1 from degree check\n");
    return (1);
}
// 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
// 0.0,0.0,1.0
int vectors_check(char *str)
{
    int i;
    char **split;

    i = 0;
    split = ft_split(str, ',');
    printf("%s\n%s\n%s\n", split[0], split[1], split[2]);
    while (split[i])
    {
        if (decimal_check(split[i], -1, 1) == 0)
        {
            printf("returning 0 from vectors_check 0\n");
            return (free_split(split));
        }
        i++;
    }
    free_split(split);
    printf("returning 1 from vectors_check\n");
    return (1);
}

int	validate_camera(char *line, t_element_count *element_count, \
    t_map *map)
{
    char	**split;

    printf("inside validate_camera\n");
	split = ft_split(line, ' ');
	printf("%s\n%s\n%s\n%s", split[0], split[1], split[2], split[3]);
    if (split[0][0] != 'C' || split[0][1] != '\0')
    {
        printf("returning 0 from validate_camera 0\n");
		return (free_split(split));
    }
    if (split[1] == NULL || split[2] == NULL || split[3] == NULL || split[4] != NULL)
    {
        printf("returning 0 from validate_camera 0.5\n");
        return (free_split(split));
    }
    // add unsigned decimal check
    if (xyz_check(split[1]) == 0)
    {
        printf("returning 0 from validate_camera 3\n");
        return (free_split(split));
    }
    // add vectors check
    if (vectors_check(split[2]) == 0)
    {
        printf("returning 0 from validate_camera 4\n");
        return (free_split(split));
    }
    // add FOV check
    if (degree_check(split[3], 0, 180) == 0)
    {
        printf("returning 0 from camera check 5\n");
        return (free_split(split));
    }
    if (setup_camera(split, map) == 0)
    {
        printf("returning 0 from camera check 6\n");
        return (free_split(split));
    }
    free_split(split);
    element_count->camera++;
    printf("returned 1 from camera check\n");
    return (1);
}
