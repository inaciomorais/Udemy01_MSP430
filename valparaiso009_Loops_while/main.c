#include <msp430.h> 

main()
{
	char x = 0;
	char y = 0;

	while (x < 10) {
	    y = y + x;
	    x = x + 1;
	}
	
	while(1);
}
