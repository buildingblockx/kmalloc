#include <memory/allocator/kmalloc.h>

void kmalloc_test_slab_allocate(void)
{
	unsigned long *buf;

	printf("Enter %s\n", __func__);

	printf("\tkmalloc\n");
	buf = kmalloc(sizeof(unsigned long), 0);
	*buf = 0x1234567890;
	printf("\tbuf address %p, buf value 0x%lx\n", buf, *buf);

	printf("\tkfree\n");
	kfree(buf);

	printf("Exit %s\n", __func__);
}

void kmalloc_test_page_allocate(void)
{
	unsigned long *buf;

	printf("Enter %s\n", __func__);

	printf("\tkmalloc\n");
	buf = kmalloc(8192, 0);
	*buf = 0xaa;
	printf("\tbuf address %p, buf value 0x%lx\n", buf, *buf);

	printf("\tkfree\n");
	kfree(buf);

	printf("Exit %s\n", __func__);
}

int kmalloc_test(void)
{
	printf("\nkmalloc init\n");
	kmalloc_init();

	kmalloc_test_slab_allocate();
	kmalloc_test_page_allocate();

	return 0;
}
