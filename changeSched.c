// /home

#include <linux/myschedule.h>
#include <stdio.h>

int main()
{
	int input;
	printf("Enter scheduler option: ");
	scanf("%d", &input);
	myschedule(input);
	return 0;
}