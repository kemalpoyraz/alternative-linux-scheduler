// usr/src/linux-2.4.20/kernel/fork.c

#include <linux/random.h>

// ...

int do_fork(unsigned int clone_flags, unsigned long stack_start, struct pt_regs *regs, unsigned long stack_size)
{
	//...
	// @711 p->pdeath_signal = 0;
	/*KEMAL*/

	p->passValue = 0;
	p->walking_step = 0;
	unsigned int t;
	get_random_bytes(&t, sizeof(t));
	p->ticket = (t % 5) + 1;

	/*KEMAL*/
	//p->counter  = (current->counter + 1) >> 1;
	//...
}

// ...