gpio_LED: led.o
	gcc -o gpio_LED -lgpiod led.o

led.o: led.c
	gcc -c -lgpiod led.c
