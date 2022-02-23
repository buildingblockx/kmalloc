#ifndef __KMALLOC_H
#define __KMALLOC_H

#include <memory/allocator/kmalloc.h>

#define KMALLOC_SHIFT_MAX	(MAX_ORDER + PAGE_SHIFT - 1)
#define KMALLOC_SHIFT_HIGH	(PAGE_SHIFT)
#define KMALLOC_SHIFT_LOW	3

/* Maximum allocatable size */
#define KMALLOC_MAX_SIZE	(1UL << KMALLOC_SHIFT_MAX)
/* Maximum size for which we actually use a slab allocator */
#define KMALLOC_MAX_CACHE_SIZE	(1UL << KMALLOC_SHIFT_HIGH)
/* Minimum allocatable size */
#define KMALLOC_MIN_SIZE	(1UL << KMALLOC_SHIFT_LOW)

/* Maximum order allocatable via the slab allocagtor */
#define KMALLOC_MAX_ORDER	(KMALLOC_SHIFT_MAX - PAGE_SHIFT)

struct kmalloc_info_struct {
	const char *name;
	unsigned int object_size;
};

#endif /* __KMALLOC_H */

