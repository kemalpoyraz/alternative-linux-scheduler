// usr/src/linux-2.4.20/include/linux/sched.h

// ...

struct task_struct 
{
	//@426
	/*KEMAL*/

	unsigned int ticket;
	unsigned int passValue;
	unsigned int walking_step;

	/*KEMAL*/

	// ...
}

// ...