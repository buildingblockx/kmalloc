#include <memory/allocator/kmalloc.h>
#include <print.h>

void kmalloc_test_slab_allocate(void)
{
	unsigned long *buf;

	pr_info("Enter %s\n", __func__);

	pr_info("\tkmalloc\n");
	buf = kmalloc(sizeof(unsigned long), 0);
	*buf = 0x1234567890;
	pr_info("\tbuf address %p, buf value 0x%lx\n", buf, *buf);

	pr_info("\tkfree\n");
	kfree(buf);

	pr_info("Exit %s\n", __func__);
}

void kmalloc_test_page_allocate(void)
{
	unsigned long *buf;

	pr_info("Enter %s\n", __func__);

	pr_info("\tkmalloc\n");
	buf = kmalloc(8192, 0);
	*buf = 0xaa;
	pr_info("\tbuf address %p, buf value 0x%lx\n", buf, *buf);

	pr_info("\tkfree\n");
	kfree(buf);

	pr_info("Exit %s\n", __func__);
}

int kmalloc_test(void)
{
	pr_info("\nkmalloc init\n");
	kmalloc_init();

	kmalloc_test_slab_allocate();
	kmalloc_test_page_allocate();

	return 0;
}
