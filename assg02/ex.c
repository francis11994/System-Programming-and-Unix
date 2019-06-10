#include <stdio.h>

int main()
{
	double a;
	
	scanf("%lf", &a);
	
	if(a > 0){
		printf("%lf", a);
	}else{
		printf("err\n");
	}
	return 0;
}
