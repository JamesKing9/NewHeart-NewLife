swap(&a, &b);

void swap(int *px, int *py)
{
	int temp;

	temp = *px;
	*px = *py;
	*py = temp;
}


/*################################*/
#include <ctype.h>

int getch(void);
void ungetch(int);

int getint(int *pn){
	int c, sign;

	while (isspace( c=getch() ))
		;
	if ( !isdigit(c) && c != EOF && c != '+' && c != '-') {
		ubgetch(c);
		return 0;
	}
	sign = (c == '-')? -1:1;
	
}