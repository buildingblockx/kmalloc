#include <memory/allocator/compound_page.h>
#include <memory/allocator/slabcache.h>
#include <memory/page_flags.h>
#include <kmalloc.h>
#include <bitops/fls.h>

const static struct kmalloc_info_struct kmalloc_info[] = {
	{NULL,                  0},	{NULL,                  0},
	{NULL,                  0},	{"kmalloc-8",           8},
	{"kmalloc-16",         16},	{"kmalloc-32",         32},
	{"kmalloc-64",         64},	{"kmalloc-128",       128},
	{"kmalloc-256",       256},	{"kmalloc-512",       512},
	{"kmalloc-1k",       1024},	{"kmalloc-2k",       2048},
	{"kmalloc-4k",       4096}
};

static struct slab_cache *kmalloc_caches[KMALLOC_SHIFT_HIGH + 1];

/*
 * Create the kmalloc cache array by slab allocator.
 */
void kmalloc_init(void)
{
	const char *name;
	unsigned int object_size;
	int i;

	for (i = KMALLOC_SHIFT_LOW; i <= KMALLOC_SHIFT_HIGH; i++) {
		name = kmalloc_info[i].name;
		object_size = kmalloc_info[i].object_size;

		kmalloc_caches[i] = slab_cache_create(name, object_size,
						sizeof(unsigned long), 0);
	}
}

static inline int get_order(unsigned long size)
{
	if (size < (1UL << PAGE_SHIFT))
		return 0;

	return fls(size - 1) - PAGE_SHIFT + 1;
}

static void *kmalloc_large(size_t size, gfp_t flags)
{
	unsigned int order;

	order = get_order(size);

	return alloc_compound_pages(flags, order);
}

/*
 * Find the slab_cache structure that serves a given size of
 * allocation
 */
static struct slab_cache *kmalloc_cache(size_t size, gfp_t flags)
{
	unsigned int index;

	index = fls(size - 1);
	if (index > KMALLOC_SHIFT_HIGH)
		return NULL;

	return kmalloc_caches[index];
}

/**
 * allocate memory
 * @size: how many bytes of memory are required.
 * @flags: the type of memory to allocate.
 *
 * kmalloc is the normal method of allocating memory for kernel.
 * when objects smaller than page size, allocate by slab allocator.
 * when objects bigger than page size, allocate by page allocator.
 */
void *kmalloc(size_t size, gfp_t flags)
{
	struct slab_cache *s;
	void *ret;

	if (size > KMALLOC_MAX_CACHE_SIZE)
		return kmalloc_large(size, flags);

	s = kmalloc_cache(size, flags);
	if (s == NULL)
		return NULL;

	ret = slab_cache_alloc(s, flags);
	return ret;
}

/**
 * free memory
 * @object: object of want to free
 *
 * kfree is the normal method of free memory for kernel.
 * when objects smaller than page size, free by slab allocator.
 * when objects bigger than page size, free by page allocator.
 */
void kfree(void *object)
{
	struct page *page;

	if (object == NULL)
		return;

	page = virt_to_head_page(object);
	if (page_compound(page)) {
		__free_compound_pages(page);
		return;
	}

	slab_cache_free(page->slab_cache, object);
}
