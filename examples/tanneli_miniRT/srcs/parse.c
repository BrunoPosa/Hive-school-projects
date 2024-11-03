/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:26:47 by tvalimak          #+#    #+#             */
/*   Updated: 2024/08/19 14:46:16 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int read_to_parse(t_element_count *element_count, t_map *map)
{
	int		fd;
	char	*line;

	fd = open("/home/tvalimak/Hive/miniRTParse/srcs/test.rt", O_RDONLY);
	//fd = open("/home/tvalimak/miniRTparsing/srcs/test.rt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error in fd\n");
		return (0);
	}
	printf("%d\n", fd);
	line = get_next_line(fd);
	while (line)
	{
		if (validate_lines(line, element_count, map) == 0)
		{
			free(line);
			printf("Invalid file\n");
			close(fd);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	printf("File was valid\n");
	close(fd);
	return (1);
}

int	setup_data(t_element_count *element_count, t_map *map)
{
	printf("inside setup_data\n");
	map->element_count = element_count;
	printf("end of setup_data\n");
	return (1);
}

int	print_data(t_map *map)
{
	// Print Ambient
	if (map->ambient)
	{
		printf("Ambient:\n");
		printf("  Ratio: %f\n", map->ambient->ratio);
		printf("  Color: (R: %d, G: %d, B: %d)\n", map->ambient->r, map->ambient->g, map->ambient->b);
	}

	// Print Camera List
	t_camera *camera = map->camera;
	while (camera)
	{
		printf("Camera:\n");
		printf("  Position: (%f, %f, %f)\n", camera->x, camera->y, camera->z);
		printf("  Orientation: (%f, %f, %f)\n", camera->nx, camera->ny, camera->nz);
		printf("  FOV: %d\n", camera->fov);
		camera = camera->next;
	}

	// Print Light List
	t_light *light = map->light;
	while (light)
	{
		printf("Light:\n");
		printf("  Position: (%f, %f, %f)\n", light->x, light->y, light->z);
		printf("  Ratio: %f\n", light->ratio);
		printf("  Color: (R: %d, G: %d, B: %d)\n", light->r, light->g, light->b);
		light = light->next;
	}

	// Print Sphere List
	t_sphere *sphere = map->sphere;
	while (sphere)
	{
		printf("Sphere:\n");
		printf("  Position: (%f, %f, %f)\n", sphere->x, sphere->y, sphere->z);
		printf("  Diameter: %f\n", sphere->diameter);
		printf("  Color: (R: %d, G: %d, B: %d)\n", sphere->r, sphere->g, sphere->b);
		sphere = sphere->next;
	}

	// Print Plane List
	t_plane *plane = map->plane;
	while (plane)
	{
		printf("Plane:\n");
		printf("  Position: (%f, %f, %f)\n", plane->x, plane->y, plane->z);
		printf("  Normal: (%f, %f, %f)\n", plane->nx, plane->ny, plane->nz);
		printf("  Color: (R: %d, G: %d, B: %d)\n", plane->r, plane->g, plane->b);
		plane = plane->next;
	}

	// Print Cylinder List
	t_cylinder *cylinder = map->cylinder;
	while (cylinder)
	{
		printf("Cylinder:\n");
		printf("  Position: (%f, %f, %f)\n", cylinder->x, cylinder->y, cylinder->z);
		printf("  Normal: (%f, %f, %f)\n", cylinder->nx, cylinder->ny, cylinder->nz);
		printf("  Diameter: %f\n", cylinder->diameter);
		printf("  Height: %f\n", cylinder->height);
		printf("  Color: (R: %d, G: %d, B: %d)\n", cylinder->r, cylinder->g, cylinder->b);
		cylinder = cylinder->next;
	}

	// Print Element Count
	if (map->element_count)
	{
		printf("Element Count:\n");
		printf("  Ambients: %d\n", map->element_count->ambient);
		printf("  Cameras: %d\n", map->element_count->camera);
		printf("  Lights: %d\n", map->element_count->light);
		printf("  Spheres: %d\n", map->element_count->sphere);
		printf("  Planes: %d\n", map->element_count->plane);
		printf("  Cylinders: %d\n", map->element_count->cylinder);
	}

	return 0;
}

int terminate_data(t_map *map, char *error)
{
	t_camera *camera;
    t_light *light;
    t_camera *next_camera;
    t_light *next_light;
    t_sphere *sphere;
    t_sphere *next_sphere;
    t_plane *plane;
    t_plane *next_plane;
    t_cylinder *cylinder;
    t_cylinder *next_cylinder;

    if (error)
        printf("%s\n", error);
    if (map->ambient)
		free(map->ambient);
	camera = map->camera;
    while (camera)
    {
        next_camera = camera->next;
        free(camera);
        camera = next_camera;
    }
	light = map->light;
    while (light)
    {
        next_light = light->next;
        free(light);
        light = next_light;
    }
    sphere = map->sphere;
    while (sphere)
    {
        next_sphere = sphere->next;
        free(sphere);
        sphere = next_sphere;
    }
    plane = map->plane;
    while (plane)
    {
        next_plane = plane->next;
        free(plane);
        plane = next_plane;
    }
    cylinder = map->cylinder;
    while (cylinder)
    {
        next_cylinder = cylinder->next;
        free(cylinder);
        cylinder = next_cylinder;
    }
    free(map);
    return (1);
}

int main(void)
{
    t_element_count element_count;
    t_map *map;

    ft_memset(&element_count, 0, sizeof(t_element_count));
    map = malloc(sizeof(t_map));
    setup_data(&element_count, map);
    if (!map)
        return (0);
    if (read_to_parse(&element_count, map) == 0)
        return (0);
    print_data(map);
	terminate_data(map, "program ended successfully\n");
    return (0);
}
