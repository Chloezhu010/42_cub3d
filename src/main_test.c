#include "../incl/cub3D.h"

/* initialize map */
char    **get_map(void)
{
    char **map = malloc(sizeof(char *) * 11);
    map[0] = ft_strdup("111111111111111");
    map[1] = ft_strdup("100000000000001");
    map[2] = ft_strdup("100000000000001");
    map[3] = ft_strdup("100000100000001");
    map[4] = ft_strdup("100000000000001");
    map[5] = ft_strdup("100000010000001");
    map[6] = ft_strdup("100001000000001");
    map[7] = ft_strdup("100000000000001");
    map[8] = ft_strdup("100000000000001");
    map[9] = ft_strdup("111111111111111");
    map[10] = NULL;
    return (map);
}

t_wall_side get_wall_side(float ray_x, float ray_y, float dx, float dy)
{
    int map_x = ray_x / BLOCK;
    int map_y = ray_y / BLOCK;
    
    // Calculate which face was hit using ray direction
    float prev_x = ray_x - dx;
    float prev_y = ray_y - dy;
    int prev_map_x = prev_x / BLOCK;
    int prev_map_y = prev_y / BLOCK;
    
    // Horizontal movement detected (crossed vertical grid line)
    if (prev_map_x < map_x)
        return WALL_WEST;
    else if (prev_map_x > map_x)
        return WALL_EAST;
    
    // Vertical movement detected (crossed horizontal grid line)
    if (prev_map_y < map_y)
        return WALL_NORTH;
    else if (prev_map_y > map_y)
        return WALL_SOUTH;
    
    // Default case
    return WALL_NORTH;
}

int get_wall_color(t_wall_side side)
{
    switch(side) {
        case WALL_NORTH:
            return 0xFF0000; // Red
        case WALL_SOUTH:
            return 0x00FF00; // Green
        case WALL_EAST:
            return 0x0000FF; // Blue
        case WALL_WEST:
            return 0xFFFF00; // Yellow
        default:
            return 0xFFFFFF; // White
    }
}

float distance(float x, float y){
    return sqrt(x * x + y * y);
}

float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
    float delta_x = x2 - x1;
    float delta_y = y2 - y1;
    float angle = atan2(delta_y, delta_x) - game->player.angle;
    float fix_dist = distance(delta_x, delta_y) * cos(angle);
    return fix_dist;
}

/* put pixel into the buffer, then display */
void    put_pixel(int x, int y, int color, t_game *game)
{
    int index;
    
    if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return ;
    /* cal the exact memory position for the pixel */
    index = y * game->size_line + x * game->bpp / 8;
    /* write color channels: blue, green, red */
    game->data[index] = color & 0xFF;
    game->data[index + 1] = (color >> 8) & 0xFF;
    game->data[index + 2] = (color >> 16) & 0xFF;
}

/* draw a square represents the player */
void    draw_square(int x, int y, int size, int color, t_game *game)
{
    for (int i = 0; i < size; i++)
        put_pixel(x + i, y, color, game);
    for (int i = 0; i < size; i++)
        put_pixel(x, y + i, color, game);
    for (int i = 0; i < size; i++)
        put_pixel(x + size, y + i, color, game);
    for (int i = 0; i < size; i++)
        put_pixel(x + i, y + size, color, game);
}

/* draw the 2D map */
void    draw_map(t_game *game)
{
    char **map = game->map;
    int color = 0x0000FF;

    for (int y = 0; map[y]; y++)
        for (int x = 0; map[y][x]; x++)
            if (map[y][x] == '1')
                draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
}

void    init_game(t_game *game)
{
    init_player(&game->player); // init player
    game->map = get_map(); // init map
    /* init mlx, win, data */
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        ft_printf("mlx_init failed\n");
        cleanup(game);
        exit(1);
    }
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
    if (!game->win)
    {
        ft_printf("mlx_new_window failed\n");
        cleanup(game);
        exit(1);
    }
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    if (!game->img)
    {
        ft_printf("mlx_new_image failed\n");
        cleanup(game);
        exit(1);
    }
    game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
    if (!game->data)
    {
        ft_printf("mlx_get_data_addr failed\n");
        cleanup(game);
        exit(1);
    }

    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

/* helper function for draw_loop */
void    clear_image(t_game *game)
{
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            put_pixel(x, y, 0, game);
}

/* detect whether the ray touches the wall */
bool touch(float px, float py, t_game *game)
{
    int x;
    int y;

    //player pos / BLOCK size
    x = px / BLOCK;
    y = py / BLOCK; 
    if (game->map[y][x] == '1')
        return (true);
    return (false);
}

void draw_line(t_player *player, t_game *game, float start_x, int i)
{
    float cos_angle = cos(start_x);
    float sin_angle = sin(start_x);
    float ray_x = player->pos_x;
    float ray_y = player->pos_y;
    float prev_x, prev_y;
    float step_x = cos_angle;
    float step_y = sin_angle;

    while(!touch(ray_x, ray_y, game))
    {
        if(DEBUG)
            put_pixel(ray_x, ray_y, 0xFF0000, game);
        prev_x = ray_x;
        prev_y = ray_y;
        ray_x += step_x;
        ray_y += step_y;
    }
    
    if(!DEBUG)
    {
        // Determine wall face using last step
        t_wall_side wall_side = get_wall_side(ray_x, ray_y, step_x, step_y);
        
        // Get appropriate color
        int wall_color = get_wall_color(wall_side);
        
        float dist = fixed_dist(player->pos_x, player->pos_y, ray_x, ray_y, game);
        float height = (BLOCK / dist) * (WIDTH / 2);
        int start_y = (HEIGHT - height) / 2;
        int end = start_y + height;
        
        // Apply shading based on distance
        float shade = 1.0f - (dist / (WIDTH / 2));
        if (shade < 0.2f) shade = 0.2f;
        if (shade > 1.0f) shade = 1.0f;
        
        int r = ((wall_color >> 16) & 0xFF) * shade;
        int g = ((wall_color >> 8) & 0xFF) * shade;
        int b = (wall_color & 0xFF) * shade;
        int shaded_color = (r << 16) | (g << 8) | b;
        
        // Ensure bounds
        if (start_y < 0) start_y = 0;
        if (end > HEIGHT) end = HEIGHT;
        
        // Define ceiling and floor colors
        int ceiling_color = 0x87CEEB; // Sky blue for ceiling
        int floor_color = 0x8B4513;   // Saddle brown for floor
        
        // Draw ceiling (from top to wall start)
        for (int y = 0; y < start_y; y++) {
            put_pixel(i, y, ceiling_color, game);
        }
        
        // Draw wall (as before)
        for (int y = start_y; y < end; y++) {
            put_pixel(i, y, shaded_color, game);
        }
        
        // Draw floor (from wall end to bottom)
        for (int y = end; y < HEIGHT; y++) {
            put_pixel(i, y, floor_color, game);
        }
    }
}

int draw_loop(t_game *game)
{
    t_player *player;
    float ray_x;
    float ray_y;
    float cos_angle;
    float sin_angle;

    player = &game->player;
    ray_x = player->pos_x;
    ray_y = player->pos_y;
    cos_angle = cos(player->angle);
    sin_angle = sin(player->angle);
    /* player movement control logic */
    move_player(player, game);
    /* clear the screen */
    clear_image(game);
    /* draw the square */
    // draw_square(player->pos_x, player->pos_y, 10, 0x00FF00, game);
    // draw_map(game);
    /* draw the ray & stop if it touches the wall */
	float fraction = PI / 3 / WIDTH;
    float start_x = player->angle + PI / 6;
    int i = 0;
    while(i < WIDTH)
    {
        draw_line(player, game, start_x, i);
        start_x -= fraction;
        i++;
    }

    /* put the img to the win */
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return (0);
}

/* click cross to close the win */
int	cross_close(t_game *game)
{
	(void)game;
	cleanup(game);
	exit(0);
}

int main(void)
{
    t_game  game;

    init_game(&game);
    /* key hooks for movement */
    mlx_hook(game.win, 2, 1L<<0, key_press, &game);
    mlx_hook(game.win, 3, 1L<<1, key_release, &game);
    /* click hook for cross-close */
    mlx_hook(game.win, 17, 0, cross_close, &game);
    /* loop */
    mlx_loop_hook(game.mlx, draw_loop, &game);
    mlx_loop(game.mlx);
    return (0);
}