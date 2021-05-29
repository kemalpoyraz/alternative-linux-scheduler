// /usr/src/linux-2.4.20/kernel/sched.c

#include <linux/random.h>

/*KEMAL*/
extern int sched_choice;
/*KEMAL*/

// ...

repeat_schedule:

	/*KEMAL*/

	next = idle_task(this_cpu);
	if(sched_choice == 0)
	{
		c = -1000;
		list_for_each(tmp, &runqueue_head)
		{
			p = list_entry(tmp, struct task_struct, run_list);
			if (can_schedule(p, this_cpu))
			{
				int weight = goodness(p, this_cpu, prev->active_mm);
				if (weight > c)
				{
					c = weight, next = p;
				}
			}
		}

		if (unlikely(!c))
		{
			struct task_struct *p;
			spin_unlock_irq(&runqueue_lock);
			read_lock(&tasklist_lock);
			for_each_task(p)
				p->counter = (p->counter >> 1) + NICE_TO_TICKS(p->nice);
			read_unlock(&tasklist_lock);
			spin_lock_irq(&runqueue_lock);
			goto repeat_schedule;
		}
	}else if (sched_choice  == 1)
	{
		int maxPassValue;
		int clm = 1;

		list_for_each(tmp, &runqueue_head)
		{
			p = list_entry(tmp, struct task_struct, run_list);
			clm = clm * p->ticket;
		}

		maxPassValue = 2 * clm;

		list_for_each(tmp, &runqueue_head)
		{
			p = list_entry(tmp, struct task_struct, run_list);
			p->walking_step = maxPassValue / p->ticket;
		}

		int i = 0;
		list_for_each(tmp, &runqueue_head)
		{
			p = list_entry(tmp, struct task_struct, run_list);
			if (i = 0)
			{
				next = p;
				i++;
			}else if (p->passValue < next->passValue)
			{
				next = p;
			}
		}

		if (next->passValue != maxPassValue)
		{
			next->passValue = next->passValue + next->walking_step;
		}else
		{
			list_for_each(tmp, &runqueue_head)
			{
				p = list_entry(tmp, struct task_struct, run_list);
				unsigned int t;
				get_random_bytes(&t, sizeof(t));
				p->ticket = (t % 5) + 1;
				p->walking_step = 0;
				p->passValue = 0;
				goto repeat_schedule;
			}
		}
	}else
	{
		printk("\nError: sched_choice not correct!\n");
	}

	/*KEMAL*/

	// ...