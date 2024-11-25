void	initialize_camera(t_rt *rt)
{
	t_init_cam	i;

    // set aspect ratio
	rt->aspect_ratio = (float) WIDTH / HEIGHT;

    // calculate focal len
	i.focal_length = (rt->width / 2) / (tanf((rt->c.fov * (PI / 180)) / 2));

    // viewport ?
	i.viewport_w = rt->width * 2;
	i.viewport_h = i.viewport_w / rt->aspect_ratio;

    // camera_f?
	i.camera_f = unit_vec(rt->c.or_vec);
	if (vec_len(cross_prod((t_vec){0, 1, 0}, i.camera_f)) != 0)
		i.camera_r = unit_vec(cross_prod((t_vec){0, 1, 0}, i.camera_f));
	else
		i.camera_r = unit_vec(cross_prod((t_vec){0, 1, -0.00001}, i.camera_f));

    // use a function to calcuate heigh?
	i.camera_up = cross_prod(i.camera_f, i.camera_r);

    // viewport
	i.viewport_u = vec_mult(i.camera_r, i.viewport_w);
	i.viewport_v = vec_mult(i.camera_up, i.viewport_h);


	rt->c.px_delta_u = vec_div(i.viewport_u, rt->width);
	rt->c.px_delta_v = vec_div(i.viewport_v, rt->height);

    //
	i.focal = vec_mult(i.camera_f, i.focal_length);


	i.viewport_up_l = vec_sub(rt->c.point, i.focal);
	i.viewport_up_l = vec_sub(i.viewport_up_l, vec_div(i.viewport_u, 2));
	i.viewport_up_l = vec_sub(i.viewport_up_l, vec_div(i.viewport_v, 2));

    
	rt->c.px00loc = vec_mult(vec_add(rt->c.px_delta_u, rt->c.px_delta_v), 0.5);
	rt->c.px00loc = vec_add(rt->c.px00loc, i.viewport_up_l);
}