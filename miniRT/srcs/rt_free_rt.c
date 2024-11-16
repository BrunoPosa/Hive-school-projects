#include "../inc/file_to_list.h"


// if we keep the list as one list, we can free like that?

// or we coudl section the list into different bits?

free_list(t_scene *rt)
{
// if there is a next, go there
// free that, go back?
// recursive?
}

/// free all the memory allocated for the rt struct
void free_rt(t_scene *rt)
{
    free(rt->mlx);
    free(rt->img);
    free(rt->light);
    free(rt->camera);
    free(((void*)rt->ambiant));
    free_list(rt->cylinder);
    free_list(rt->plane);
    free_list(rt->sphere);
    (rt);
}