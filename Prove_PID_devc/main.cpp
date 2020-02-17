#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int Setpoint, Resto, Output;

int main(int argc, char** argv) 
{
	printf("Hello \n");
	
	while(1)
	{	
		printf("Setpoint: ");
		scanf("%d", &Setpoint);
		
		Output = (Setpoint / 50) * 5;
		Resto = (Setpoint % 50);
		if (Resto >= 25)
			Output += 5;
			
		printf("Output: %d, Resto: %d \n", Output, Resto);
	}
	return 0;
}
