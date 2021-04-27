/*
  Program to interact with LED's which are attached on the raspberrypi.
  LED's:
    red   => GPIO 16
    green => GPIO 20

  OPTIONS:
    toggle => Toggle the LED (on => off, off => on)
    on     => Turn LED on (stays on if already on)
    off    => Turn LED off (stays off of already off)

  Attention:
    At the time of implementation, it seems like the gpiod library is not able to read an outputs value
    without manipulating it (mostly resetting it to zero).
    Thus a status file will be created.
    Means: if an led is turned on we create '/tmp/led_red'
    When toggling we can check if the file exist and behave accordingly.

  Author: Lennart Brun
  Date  : 20.04.2021

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <gpiod.h>
#include <unistd.h>

#define LED_RED 16
#define LED_GRN 20


static void print_help(void) {
    printf("Usage: led_set [LED] [ACTION]\n");
    printf("\n");
    printf("Perform different actions on a given set of leds.\n\n");
    printf("LED:\n");
    printf("\tred, green\n");
    printf("ACTION:\n");
    printf("\ttoggle:\tToggle the state of the LED (on => off, off => on)\n");
    printf("\ton:\tTurn LED on (stays on if already on)\n");
    printf("\toff:\tTurn LED off (stays off if already off)\n");
}


// Set the given value on the line
int set_line_value(struct gpiod_line *line, int value) {
  int req, set;

  // Reserve line for write access, 1 = default value
  req = gpiod_line_request_output(line, "led_set", value);
  if (req) {
    fprintf(stderr, "Could not reserve the line\n");
    return -1;
  }

  // Write a 1 => turn led on
  set = gpiod_line_set_value(line, value);
  if (set){
    fprintf(stderr, "Failed to turn on the led\n");
    return -1;
  }

  return 0;
}


int main(int argc, char *argv[]) {
  struct gpiod_chip *chip;
	struct gpiod_line *line;

	int active_led;

  // Check for right amount of arguments
  if (3 != argc) {
    print_help();
    exit(EXIT_FAILURE);
  }


  // Get LED number and set active led accordingly
  if (0 == strcmp(argv[1], "red")) {
    active_led = LED_RED;   
  }else if (0 == strcmp(argv[1], "green")) {
    active_led = LED_GRN;   
  }else {
    print_help();
    exit(EXIT_FAILURE);
  }


  // Open the chip (gpiochip0 is the only one on the pi)
	chip = gpiod_chip_open("/dev/gpiochip0");
	if (!chip) {
    fprintf(stderr, "Failed to get chip\n");
    exit(EXIT_FAILURE);
  }


  // Get handle for LED line
	line = gpiod_chip_get_line(chip, active_led);
	if (!line) {
    fprintf(stderr, "Failed to get line\n");
		gpiod_chip_close(chip);
    exit(EXIT_FAILURE);
  }


  // Perform action according to the second argument
  if (0 == strcmp(argv[2], "toggle")) {
    // Check if a status file exists
    char file[] = "led_";
    strcat(file, argv[1])

    int stat = stat
    
  }else if (0 == strcmp(argv[2], "on")) {
    // Turn the LED on
    set_line_value(line, 1);
  }else if (0 == strcmp(argv[2], "off")) {
    // Turn the LED off
    set_line_value(line, 0);
  }else {
    print_help();
    exit(EXIT_FAILURE);
  }


  // Clean up 
  gpiod_chip_close(chip);
  exit(EXIT_SUCCESS);
}
