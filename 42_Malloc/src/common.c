#include "malloc.h"


void		split_block(block_t *current_b, size_t size) {
	block_t	old_b;
	size_t	diff_size;

	ft_memcpy(&old_b, current_b, BLOCK_SIZE);
	current_b->zone = old_b.zone;
	current_b->alloc_status = IS_ALLOCATED;
	current_b->size = size + BLOCK_SIZE;
	current_b->prev = old_b.prev;

	if (old_b.size - current_b->size == 0)
		return;
	current_b->next = (void *)current_b + size + BLOCK_SIZE;
	current_b->next->zone = old_b.zone;
	current_b->next->alloc_status = IS_FREE;
	diff_size = old_b.size - current_b->size;
	if (diff_size != 0 && diff_size < BLOCK_SIZE) {
		current_b->next->size = diff_size + old_b.next->size;
		current_b->next->next = old_b.next->next;
	}
	else {
		current_b->next->size = diff_size;
		current_b->next->next = old_b.next;
	}
	current_b->next->prev = current_b;
}

block_t*	merge_free_block(block_t *b) {
	if (b &&
			b->next &&
			b->next->alloc_status == IS_FREE &&
			b->next->zone == b->zone) {
		b->size = b->size + b->next->size;
		b->next = b->next->next;
		if (b->next)
			b->next->prev = b;
	}
	return b;
}

block_t*	get_next_zone(block_t* curr_zone) {
	block_t*	next_zone = NULL;

	for (block_t *b = curr_zone; b != NULL; b = b->next) {
		if (b->next && b->next->zone != curr_zone->zone) {
			next_zone = b->next;
			break;
		}
		else if (b->next == NULL) {
			next_zone = NULL;
		}
	}
	return next_zone;
}

block_t*	get_current_block(block_t *block) {
	for (block_t *b = g_first_block; b != NULL; b = b->next) {
		if (b == block)
			return b;
	}
	return NULL;
}
