/* SPDX-License-Identifier: GPL-2.0 */
/* Canonical native waiter type shared by rwsem and its vendor consumers. */
#ifndef _KERNEL_LOCKING_RWSEM_H
#define _KERNEL_LOCKING_RWSEM_H
#include <linux/list.h>
#include <linux/types.h>
struct task_struct;

enum rwsem_waiter_type {
	RWSEM_WAITING_FOR_WRITE,
	RWSEM_WAITING_FOR_READ
};

struct rwsem_waiter {
	struct list_head list;
	struct task_struct *task;
	enum rwsem_waiter_type type;
	unsigned long timeout;
	bool handoff_set;
};
#endif
