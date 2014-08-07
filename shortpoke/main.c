#include <stdint.h>
#include <osbind.h>

void short_poke(uint16_t value, uint16_t * dest);

char debugbuf[512];

static const char inputbuf[6] = "Hallo";

int main(void)
{
	Cconws("Pokeit!\r\n");
	Cconin();
	short_poke(0xF0F, (uint16_t *)0xffff8240);
	Cconws("done\r\n");
	
	debugbuf[0] = inputbuf[0];
	debugbuf[1] = inputbuf[1];
	debugbuf[2] = inputbuf[2];
	debugbuf[3] = inputbuf[3];
	debugbuf[4] = inputbuf[4];
	
	Cconin();
	return 0;
}
