//
// Created by sergiogd on 3/24/23.
//

#include "main.h"

int to_str(Map *map, char res[(MAX_MAP_W + 1) * MAX_MAP_H])
{
    char temp[MAX_MAP_W];
    int err = 0;
    for (int i = 0; i < map->h; i++)
    {
        temp[0] = '\0';
        for (int j = 0; j < map->w; j++)
        {
            switch (map->tiles[i][j])
            {
            case 0:
                sprintf(temp, "%s%s", temp, " ");
                break;
            case 1:
                sprintf(temp, "%s%s", temp, "#");
                break;
            case 2:
                sprintf(temp, "%s%s", temp, "H");
                break;
            default:
                sprintf(temp, "%s%s", temp, " ");
                err = 1;
                break;
            }
        }
        sprintf(res, "%s%s\n", res, temp);
    }
    return err;
}

void from_str(Map *map, char res[(MAX_MAP_W + 1) * MAX_MAP_H])
{
    char *p = strtok(res, "\n");
    int i;
    int j;
    char temp[MAX_MAP_W];
    for (i = 0; p != NULL; i++)
    {
        strcpy(temp, p);
        for (j = 0; j < strlen(temp); j++)
        {
            switch (temp[j])
            {
            case '1':
            case '|':
            case '#':
                map->tiles[i][j] = 1;
                break;
            case '2':
            case 'H':
                map->tiles[i][j] = 2;
                break;
            default:
                map->tiles[i][j] = 0;
                break;
            }
        }
        p = strtok(NULL, "\n");
    }
    map->h = i;
    map->w = j;
}

void to_str_lines(Map *map, char res[MAX_MAP_H][MAX_MAP_W], int x, int y)
{
    char temp[MAX_MAP_W];
    for (int i = 0; i < map->h; i++)
    {
        temp[0] = '\0';
        for (int j = 0; j < map->w; j++)
        {
            if (x == j && y == i)
            {
                switch (map->tiles[i][j])
                {
                case 0:
                    sprintf(temp, "%s%s", temp, " + ");
                    break;
                case 1:
                    sprintf(temp, "%s%s", temp, "#+#");
                    break;
                case 2:
                    sprintf(temp, "%s%s", temp, "H+H");
                    break;
                default:
                    sprintf(temp, "%s%s", temp, " + ");
                }
            }
            else
            {
                switch (map->tiles[i][j])
                {
                case 0:
                    sprintf(temp, "%s%s", temp, " . ");
                    break;
                case 1:
                    sprintf(temp, "%s%s", temp, "###");
                    break;
                case 2:
                    sprintf(temp, "%s%s", temp, "HHH");
                    break;
                default:
                    sprintf(temp, "%s%s", temp, " . ");
                }
            }
        }
        strcpy(res[i], temp);
    }
}

void print_map(Map *map, int x, int y)
{
    int valid = xy_valid(map, x, y);
    char temp[MAX_MAP_W];
    for (int i = 0; i < map->h; i++)
    {
        temp[0] = '\0';
        for (int j = 0; j < map->w; j++)
        {
            if (x == j && y == i)
            {
                switch (map->tiles[i][j])
                {
                case 0:
                    sprintf(temp, "%s%s", temp, " + ");
                    break;
                case 1:
                    sprintf(temp, "%s%s", temp, "#+#");
                    break;
                case 2:
                    sprintf(temp, "%s%s", temp, "H+H");
                    break;
                default:
                    sprintf(temp, "%s%s", temp, " + ");
                }
            }
            else
            {
                switch (map->tiles[i][j])
                {
                case 0:
                    sprintf(temp, "%s%s", temp, " . ");
                    break;
                case 1:
                    sprintf(temp, "%s%s", temp, "###");
                    break;
                case 2:
                    sprintf(temp, "%s%s", temp, "HHH");
                    break;
                default:
                    sprintf(temp, "%s%s", temp, " . ");
                }
            }
        }
        printf("%s\n", temp);
    }
}

void print_valid(Map *map, int x, int y)
{
    int valid = xy_valid(map, x, y);
    char temp[MAX_MAP_W];
    for (int i = 0; i < map->h; i++)
    {
        temp[0] = '\0';
        for (int j = 0; j < map->w; j++)
        {
            if (x == j && y == i)
            {
                switch (map->valid_table[i][j])
                {
                case 0:
                    sprintf(temp, "%s%s", temp, " + ");
                    break;
                case 1:
                    sprintf(temp, "%s%s", temp, "#+#");
                    break;
                case 2:
                    sprintf(temp, "%s%s", temp, "H+H");
                    break;
                default:
                    sprintf(temp, "%s%s", temp, " + ");
                }
            }
            else
            {
                switch (map->valid_table[i][j])
                {
                case 0:
                    sprintf(temp, "%s%s", temp, " . ");
                    break;
                case 1:
                    sprintf(temp, "%s%s", temp, "###");
                    break;
                case 2:
                    sprintf(temp, "%s%s", temp, "HHH");
                    break;
                default:
                    sprintf(temp, "%s%s", temp, " . ");
                }
            }
        }
        printf("%s\n", temp);
    }
}

void reverse(const int arr[], int n, int res[])
{
    for (int i = 0; i < n / 2; i++)
    {
        int temp = arr[i];
        res[i] = arr[n - i - 1];
        res[n - i - 1] = temp;
    }
}

void mirror_tiles(Map *map)
{
    int len = map->w;
    int temp[len];
    int i, j;
    for (i = 0; i < map->h; i++)
    {
        reverse(map->tiles[i], map->w, temp);
        for (j = 0; j < map->w; j++)
        {
            map->tiles[i][map->w + j] = temp[j];
        }
    }
    map->w += j;
}

int xy_valid(Map *map, int x, int y)
{
    return x >= 0 && x < map->w && y >= 0 && y < map->h;
}

int get_tile(Map *map, int x, int y)
{
    if (xy_valid(map, x, y) == 0)
        return 1000;
    return map->tiles[y][x];
}

void add_wall(Map *map, int x, int y)
{
    if (xy_valid(map, x, y) == 1)
        map->tiles[y][x] = 1;
}

int is_wall_block_filled(Map *map, int x, int y)
{

    return ((get_tile(map, x + 1, y + 1) > 0 &&
             get_tile(map, x + 2, y + 1) > 0) &&
            (get_tile(map, x + 2, y + 1) > 0 &&
             get_tile(map, x + 2, y + 2) > 0)) &&
           (get_tile(map, x + 1, y + 1) != 1000 &&
            get_tile(map, x + 2, y + 1) != 1000) &&
           (get_tile(map, x + 2, y + 1) != 1000 &&
            get_tile(map, x + 2, y + 2) != 1000);
}

void add_wall_block(Map *map, int x, int y)
{
    add_wall(map, x + 1, y + 1);
    add_wall(map, x + 2, y + 1);
    add_wall(map, x + 1, y + 2);
    add_wall(map, x + 2, y + 2);
}

int can_new_block_fit(Map *map, int x, int y)
{
    if (!(xy_valid(map, x, y) == 1 && xy_valid(map, x + 3, y + 3) == 1))
        return 0;
    for (int i = y; i < y + 4; i++)
    {
        for (int j = x; j < x + 4; j++)
        {
            if (get_tile(map, j, i) > 0) // && get_tile(map, j, i)!=1000
                return 0;
        }
    }
    return 1;
}

void update_pos_list(Map *map)
{
    memset(map->valid_table, 0, sizeof(map->valid_table));
    memset(map->valid_list, 0, sizeof(map->valid_list));
    map->valid_count = 0;
    for (int i = 0; i < map->h; i++)
    {
        for (int j = 0; j < map->w; j++)
        {
            map->valid_table[i][j] = can_new_block_fit(map, j, i);
            if (map->valid_table[i][j] == 1)
            {
                map->valid_list[map->valid_count][0] = j;
                map->valid_list[map->valid_count][1] = i;
                map->valid_count++;
            }
        }
    }
}

void reset_connections(Map *map)
{
    for (int i = 0; i < map->h; i++)
    {
        for (int j = 0; j < map->w; j++)
        {
            map->connections_lens[i][j] = 0;
        }
    }
}

void connect(Map *map, int x, int y, int x0, int y0)
{
    if (map->valid_table[x0][y0] == 1)
    {
        map->connections[y0][x0][map->connections_lens[y0][x0]][0] = x;
        map->connections[y0][x0][map->connections_lens[y0][x0]][1] = y;
        map->connections_lens[y0][x0]++;
    }
}

void add_connection(Map *map, int x, int y, int dx, int dy)
{
    if (map->valid_table[y][x] == 1)
    {
        connect(map, x, y, x + dx, y + dy);
        connect(map, x, y, x + dx * 2, y + dy * 2);
        if (map->valid_table[y - dx][x - dy] == 0)
        {
            connect(map, x, y, x + dx - dy, y + dy - dx);
        }
        if (map->valid_table[y + dx][x + dy] == 0)
        {
            connect(map, x, y, x + dx + dy, y + dy + dx);
        }
        if (map->valid_table[y + dy - dx][x + dx - dy] == 0)
        {
            connect(map, x, y, x + 2 * dx - dy, y + 2 * dy - dx);
        }
        if (map->valid_table[y + dy + dx][x + dx + dy] == 0)
        {
            connect(map, x, y, x + 2 * dx + dy, y + 2 * dy + dx);
        }
    }
}

void update_connections(Map *map)
{
    reset_connections(map);
    for (int i = 0; i < map->h; i++)
    {
        for (int j = 0; j < map->w; j++)
        {
            if (map->valid_table[i][j] == 1)
            {
                if ((get_tile(map, j - 1, i) > 0 && get_tile(map, j - 1, i) != 1000) ||
                    (get_tile(map, j - 1, i + 1) > 0 && get_tile(map, j - 1, i + 1) != 1000) ||
                    (get_tile(map, j - 1, i + 2) > 0 && get_tile(map, j - 1, i + 2) != 1000) ||
                    get_tile(map, j - 1, i + 3) > 0 && get_tile(map, j - 1, i + 3) != 1000)
                    add_connection(map, j, i, 1, 0);
            }
        }
    }
}

void update(Map *map)
{
    update_pos_list(map);
    update_connections(map);
}

int expand(Map *map, int x, int y, int visited[MAX_MAP_H][MAX_MAP_W])
{
    int count = 0;
    int x0, y0;
    if (visited[y][x] == 1)
        return 0;
    visited[y][x] = 1;
    if (map->connections_lens[y][x] > 0)
    {
        for (int i = 0; i < map->connections_lens[y][x]; i++)
        {
            x0 = map->connections[y][x][i][0];
            y0 = map->connections[y][x][i][1];
            if (is_wall_block_filled(map, x0, y0) == 0)
            {
                count++;
                add_wall_block(map, x0, y0);
            }
            count += expand(map, x0, y0, visited);
        }
    }
    return count;
}

int expand_wall(Map *map, int x, int y)
{
    int visited[MAX_MAP_H][MAX_MAP_W];
    memset(visited, 0, sizeof(visited));
    return expand(map, x, y, visited);
}

/*
int get_most_open_dir(Map *map, int x, int y, int max_dir[2])
{
    int dirs[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_usec);
    int choice = rand() % 4;
    max_dir[0] = dirs[choice][0];
    max_dir[1] = dirs[choice][1];
    int max_len = 0;
    int len;
    int dx, dy;
    for (int i = 0; i < 4; i++)
    {
        dx = dirs[i][0];
        dy = dirs[i][1];
        len = 0;
        while (map->valid_table[x + dx * len][y + dy * len] == 1)
        {
            len++;
        }
        if (len > max_len)
        {
            max_dir[0] = dx;
            max_dir[1] = dy;
            max_len = len;
        }
    }
    return max_len;
}
*/

int add_wall_obstacle(Map *map, int x, int y, int extend)
{
    print_map(map, -1, -1);
    printf("updating\n");
    update(map);
    struct timeval tv;
    if (map->valid_count == 0)
    {
        return 0;
    }
    printf("selecting positions\n");
    if (xy_valid(map, x, y) == 0)
    {
        gettimeofday(&tv, NULL);
        srand(tv.tv_usec);
        int choice = rand() % map->valid_count;
        x = map->valid_list[choice][0];
        y = map->valid_list[choice][1];
    }
    print_valid(map, x, y);
    printf("seeding\n");
    add_wall_block(map, x, y);
    char first_lines[MAX_MAP_H][MAX_MAP_W];
    char grow_lines[MAX_MAP_H][MAX_MAP_W];
    char extend_lines[MAX_MAP_H][MAX_MAP_W];
    to_str_lines(map, first_lines, x, y);
    printf("growing\n");
    int count = expand_wall(map, x, y);
    if (count > 0)
        to_str_lines(map, grow_lines, x, y);
    printf("extending\n");
    if (extend == 1)
    {
        int max_blocks = 4;
        int turn = 0;
        int turn_blocks = max_blocks;

        gettimeofday(&tv, NULL);
        srand(tv.tv_usec);
        int rn = rand() % 100;
        if (rn <= 50)
        {
            turn_blocks = 4;
            max_blocks += turn_blocks;
        }
        int dirs[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
        gettimeofday(&tv, NULL);
        srand(tv.tv_usec);
        int choice = rand() % 4;
        int dx = dirs[choice][0];
        int dy = dirs[choice][1];
        int orgdir[] = {dx, dy};
        int i = 0;
        int x0, y0, px0, py0;
        int len = 0;
        while (count < max_blocks)
        {
            x0 = x + dx * i;
            y0 = y + dy * i;
            if ((turn == 0 && count >= turn_blocks) || map->valid_table[y0][x0] == 0)
            {
                turn = 1;
                int temp_x = dx;
                dx = -dy;
                dy = temp_x;
                i = 1;
                if (orgdir[0] == dx && orgdir[1] == dy)
                    break;
                else
                    continue;
            }

            printf("%d;%d,%d,%d;%d,%d;%d,%d,%d,%d;%d,%d\n",
                   i,turn, count, turn_blocks,
                   x0, y0,
                   get_tile(map, x0 + 1, y0 + 1),
                   get_tile(map, x0 + 2, y0 + 1),
                   get_tile(map, x0 + 2, y0 + 1),
                   get_tile(map, x0 + 2, y0 + 2),
                   (get_tile(map, x0 + 1, y0 + 1) > 0 &&
                    get_tile(map, x0 + 2, y0 + 1) > 0),
                   (get_tile(map, x0 + 2, y0 + 1) > 0 &&
                    get_tile(map, x0 + 2, y0 + 2) > 0));

            if (is_wall_block_filled(map, x0, y0) == 0)
            {
                print_map(map,x0,y0);
                add_wall_block(map, x0, y0);
                count += 1 + expand_wall(map, x0, y0);
            }
            if (i > 10 || len > 40)
            {
                print_valid(map, x, y);
                print_map(map, x0, y0);
                exit(1);
            }

            i += 1;
            px0 = x0;
            py0 = y0;
            len++;
        }
        to_str_lines(map, extend_lines, x, y);
    }
    if (map->verbose == 1)
    {
        printf("added block at %d %d\n", x, y);
        for (int j = 0; j < map->h; j++)
        {
            printf("%s  %s  %s\n", first_lines[j], grow_lines[j], extend_lines[j]);
        }
    }
    return 1;
}

int main()
{
    Map *map;
    map = malloc(sizeof(Map));
    char lmapstr[(MAX_MAP_W + 1) * MAX_MAP_H];
    strcpy(lmapstr,
           "||||||||||||||||\n"
           "|...............\n"
           "|...............\n"
           "|...............\n"
           "|...............\n"
           "|...............\n"
           "|...............\n"
           "|...............\n"
           "|...............\n"
           "|...............\n"
           "|...............\n"
           "|...............\n"
           "|.........|||||.\n"
           "|.........|HHHHH\n"
           "|.........|HHHHH\n"
           "|.........|HHHHH\n"
           "|.........|HHHHH\n"
           "|.........||||||\n"
           "|...............\n"
           "|...............\n"
           "|...............\n"
           "|...............\n"
           "|...............\n"
           "|...............\n"
           "|...............\n"
           "|...............\n"
           "|...............\n"
           "|...............\n"
           "|...............\n"
           "|...............\n"
           "|...............\n"
           "||||||||||||||||");
    from_str(map, lmapstr);
    map->verbose = 1;
    printf("starting\n");
    while(add_wall_obstacle(map, -1, -1, 1)){

        printf("%d,%d\n", map->w, map->h);
    }
    print_valid(map, -1, -1);
    print_map(map, -1, -1);
    printf("%d,%d\n", map->w, map->h);
    update(map);
    print_valid(map, -1, -1);
    mirror_tiles(map);
    print_map(map,-1,-1);
}