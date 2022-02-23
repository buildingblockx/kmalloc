# kmalloc subsystem

## 概述

为了方便分配内存，自动从需要申请的内存大小进行判断使用哪一个内存分配器进行分配内存；释放内存，同理可得；于是 kmalloc subsystem 就诞生了。

## 原理

```
              ┌─────────────────┐
              │kmalloc subsystem│
              └────┬───────┬────┘
                  /         \
size > one page  /           \  size <= one page
                /             \
     ┌────────────────┐   ┌────────────────┐
     │ page allocator │   │ slab allocator │
     └────────────────┘   └────────────────┘
```

当我们需要分配大于一页内存时，自动从page allocator进行分配内存。

当我们需要分配小于等于一页内存时，自动从slab allocator进行分配内存。

## 如何使用？

使用`kmalloc subsystem`时，只需要在`page allocater`与`slab allocater`初始化结束后，调用`kmalloc_init()`即可，接下来就可以调用 `kmalloc()/kfree()` 进行 分配/释放 内存

使用时记得加上头文件：`#include <memory/allocator/kmalloc.h>`

## 功能

* 已完成功能：

1. 分配/释放任意大小的内存

* 未完成功能：

1.
