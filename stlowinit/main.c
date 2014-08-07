#include <stdint.h>
#include <osbind.h>

int main(void)
{
	(*(uint16_t *)0xFFFF8240) = 0x31; // we are in Supervisor so this should work

	(*(uint16_t *)0xFFFF825E) = 0xFFF;

	(void)Cconws( "press any key\n");

	Cconin();

	return 0;
}

