#include <wiringPi.h>
#include <mcp3004.h>
#include <stdio.h>
#include <stdlib.h>

#define SPI_CHAN 0
#define MY_PIN 12345

int main(void)
{
int x[8],i;
float v[8];
float k = 3.3/1024;

  wiringPiSetup() ;
  mcp3004Setup (MY_PIN, SPI_CHAN); // 3004 and 3008 are the same 4/8 channels

	for (i=0;i<8;i++)
	{
		x[i] = analogRead (MY_PIN + i ) ;
		v[i] = k * (float)(x[i]);
	}
	printf("AD ch: = %4d %4d %4d %4d %4d %4d %4d %4d \n",
			x[0],x[1],x[2],x[3],x[4],x[5],x[6],x[7]);
	printf("AD vd: = %2.2f %2.2f %2.2f %2.2f %2.2f %2.2f %2.2f %2.2f\n",
			v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7]);

	return 0;
}

