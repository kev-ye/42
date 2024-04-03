# 42 project : Cub3d

## Index

* [Infomation](#Information)
* [To_do](#To_do)
* [Singleton](#Singleton)
* [How_to_run](#How_to_run)

## Information

The code is cleaner than my old cub3d.  
Mandatory part: Textures  
Program are tested in Macos.

## To_do
 - [x] parser part: note: use split is better
 - [x] mlx part: done
 - [x] raycasting part: done
 - [ ] run in linux
 - [ ] add a beautiful texture

## Singleton

### What is a singleton?

[__What_is_a_singlton__](https://fr.wikipedia.org/wiki/Singleton_(patron_de_conception))
  
Singletons are just static variables with some encapsulation.  
So you can use it like a global variable.

### Why use it?

Because usually at 42, use the global variable is forbidden.

### Example

``` c
void	*singleton(void)
{
	static void	*singleton = NULL;

	if (NULL == singleton)
	{
		singleton = calloc(1, sizeof(void *));
		if (NULL == singleton)
			exit(EXIT_FAILURE);
	}
	return (singleton);
}
```

### Note

I use this to save my variables.

``` c
typedef struct s_cub3d
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**config;
	t_map		map_info;
	t_img		mlx_img;
	t_img		tex_img[TEXMAX];
	t_player	player;
	BOOL		key[KEYMAX];
}	t_cub3d;
```

## How_to_run

	make && ./cub3D map/map.cub
