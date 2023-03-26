//
// Created by sergiogd on 3/24/23.
//

#ifndef SERVER_MAP_H
#define SERVER_MAP_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define MAX_MAP_H 128
#define MAX_MAP_W 128
typedef struct
{
    int tiles[MAX_MAP_H][MAX_MAP_W];
    int connections_lens[MAX_MAP_H][MAX_MAP_W];
    int connections[MAX_MAP_H][MAX_MAP_W][MAX_MAP_H * MAX_MAP_W][2];
    int h;
    int w;
    int valid_table[MAX_MAP_H][MAX_MAP_W];
    int valid_count;
    int valid_list[MAX_MAP_H*MAX_MAP_W][2];
    int verbose;
} Map;

int to_str(Map *map, char res[(MAX_MAP_W + 1) * MAX_MAP_H]);
int xy_valid(Map *map, int x, int y);
int get_tile(Map *map, int x, int y);
void add_wall(Map *map, int x, int y);
int is_wall_block_filled(Map *map, int x, int y);
void add_wall_block(Map *map, int x, int y);
int can_new_block_fit(Map *map, int x, int y);
void update_pos_list(Map *map);
void reset_connections(Map *map);
void add_connection(Map *map, int x, int y, int dx, int dy);
void update_connections(Map *map);
void reverse(const int arr[], int n, int res[]);
void mirror_tiles(Map *map);
#endif // SERVER_MAP_H
