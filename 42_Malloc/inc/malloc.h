#ifndef MALLOC_H
# define MALLOC_H

/* -- Includes */

#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/mman.h>

/* -- Macros */

// anscii code
# define S_NONE "\033[0m"
# define S_BLACK "\033[1;30m"
# define S_RED "\033[1;31m"
# define S_GREEN "\033[1;32m"
# define S_YELLOW "\033[1;33m"
# define S_BLUE "\033[1;34m"
# define S_PURPLE "\033[1;35m"
# define S_CYAN "\033[1;36m"

// aligns pointer
#if __SIZEOF_LONG__ == 4
	#define ALIGN(x) ((((x - 1) >> 2) << 2) + __SIZEOF_LONG__)
	#define TINY_PAGE 4U
	#define SMALL_PAGE 32U
#elif __SIZEOF_LONG__ == 8
	#define ALIGN(x) ((((x - 1) >> 3) << 3) + __SIZEOF_LONG__)
	#define TINY_PAGE 32U
	#define SMALL_PAGE 128U
#else
	#error "Unsupported system architecture, it should be 32 or 64 bit"
#endif

#define BLOCK_SIZE sizeof(block_t)

#define TINY_ZONE getpagesize() * TINY_PAGE
#define SMALL_ZONE getpagesize() * SMALL_PAGE

#define TINY_BLOCK_SIZE TINY_ZONE / 128U
#define SMALL_BLOCK_SIZE SMALL_ZONE / 128U

#define IS_FREE 0
#define IS_ALLOCATED 1

enum {
	TINY,
	SMALL,
	LARGE
};


#define DEFINE_BLOCK_SIZE(size) ((size + BLOCK_SIZE <= TINY_BLOCK_SIZE) ? TINY_ZONE : \
								(size + BLOCK_SIZE <= SMALL_BLOCK_SIZE) ? SMALL_ZONE : size + BLOCK_SIZE)
#define DEFINE_BLOCK_ZONE(zsize) ((zsize <= TINY_ZONE) ? TINY : \
								(zsize <= SMALL_ZONE) ? SMALL : LARGE)
#define GET_BLOCK(ptr) ((void *)ptr + BLOCK_SIZE)
#define GET_META(ptr) ((void *)ptr - BLOCK_SIZE)

/* -- Structures */

typedef struct s_block block_t;
struct s_block {
	uint8_t		zone : 2;
	uint8_t		alloc_status : 2;
	size_t		size;
	block_t*	prev;
	block_t*	next;
};

/* -- Global */

extern block_t*			g_first_block;
extern pthread_mutex_t	g_memory_mutex;

/* -- Prototypes */

// common
void		split_block(block_t *current_b, size_t size);
block_t*	merge_free_block(block_t *b);
block_t*	get_next_zone(block_t* curr_zone);

// utils
void*		ft_memcpy(void *dst, const void *src, size_t n);
void*		ft_memset(void *b, int c, size_t len);
void		ft_putstr_fd(const char *s, int fd);
void		ft_putnbr_fd(size_t n, int fd, size_t padding);
void		ft_putaddr_fd(const void *addr, int fd);

// mandatory utils
void*		_malloc(size_t size);
void		_free(void *ptr);
void		_show_alloc_mem_info(void);


// mandatory
void*		malloc(size_t size);
void*		calloc(size_t count, size_t size);
void*		realloc(void *ptr, size_t size);
void		free(void *ptr);

// debug
void		show_alloc_mem(void);
void		show_alloc_mem_info(void);
void		show_alloc_mem_leak(void);

#endif
