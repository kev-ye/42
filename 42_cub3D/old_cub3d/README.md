# 42 project : Cub3d

## Index

* [Infomation](#Information)
* [How_to_run](#How_to_run)
* [Some_debug](#Some_debug)

## Infomation

Old cub3d with old subject.  
Mandatory part: Textures + Sprites.  
Bonus part: Game music + Minimap + Rotation up & down + Multi sprites.  
Program are tested in Macos and linux.  

## How_to_run

Mandadory part :

    make && ./cub3D map/map.cub

Bonus part :

    make bonus && ./cub3D_bonus map/map_bonus.cub

## Some_debug

    My program is not prefect because it have some "Still reachable" leaks in linux (found with valgrind).

    “still reachable” means your program is probably ok – it didn’t free some memory it could have. This is quite common and often reasonable. Don’t use –show-reachable=yes if you don’t want to see these reports.

Solution :

    Use the function "mlx_destroy_display(void *mlx_ptr)" to destroy your mlx pointer and free it.