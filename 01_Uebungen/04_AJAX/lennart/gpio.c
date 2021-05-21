/*
  This C-file contains functions to interact with the GPIO's

  Attention:
    At the time of implementation, it seems like the gpiod library is not able to read an outputs value
    without manipulating it (mostly resetting it to zero).
    Thus a status file will be created.
    Means: if an led is turned on we create '/tmp/led_red'
    When toggling we can check if the file exist and behave accordingly.

  Author: Lennart Brun
  Date  : 10.05.2021

*/
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <gpiod.h>

#include "html.h"
#include "gpio.h"

/**
 * Set the given value on the line
 * @param line Ponter to the gpiod_line
 * @param pin_number The number of the pin that should be manipulated
 * @param value The value to set the line to (should be 0 or 1)
 * @returns 0 on success
 */
static int set_line_value(struct gpiod_line *line, int pin_number, int value) {
  int req, set;

  // Reserve line for write access
  req = gpiod_line_request_output(line, "led_set", value);
  if (req) {
    printf("Error: Could not reserve the line\n");
    printf("ERRNO: %s<br>", strerror(errno));
    exit(EXIT_FAILURE);
  }

  // Write the value 
  set = gpiod_line_set_value(line, value);
  if (set){
    printf("Error: Failed to turn on the led\n");
    printf("ERRNO: %s<br>", strerror(errno));
    exit(EXIT_FAILURE);
  }

  // Create the file name
  char file[15];
  sprintf(file,"/tmp/pin_%i", pin_number); 

  // Create or delete file representing the status
  if (0 == value) {
    // Delete file
    unlink(file);

  }else {
    // Create file
    int fd = open(file, O_WRONLY|O_CREAT);

    /*
      As we don't set permissions when creating the file,
      we get a "access error" when trying to open the file
      and it already exists (tunring led on, when it is).
      Thus we filter this error out.
    */
    if (fd < 0 && errno != EACCES) {
      printf("Error: Failed to open file\n");
      printf("ERRNO: %s<br>", strerror(errno));
      exit(EXIT_FAILURE);
    }
    close(fd);
  }

  return 0;
}

/**
 * Get the current status of an led
 * @param pin_number The number of the pin, that should be checked
 * @returns 0 if pin is low, 1 if pin is high
 */
int gpio_get_led_status(int pin_number) {
  char file[15];
  int stat_result;

  sprintf(file, "/tmp/pin_%i", pin_number);
  struct stat stats;
  stat_result = stat(file, &stats);

  if (-1 == stat_result && errno == ENOENT) {
    // File does not exist -> means led is off
    //printf("File not found -> led is off.\n");
    return 0;
  } else {
    // File does exist -> means led is on 
    //printf("File found -> led is on\n");
    return 1;
  }
}


/**
 * Switch leds according to the given struct
 * @param pac Struct containing the info abaout the actions to perform on each led
 */
void gpio_handle_led_actions(struct Parsed_actions pac) {
  // Return if no actions are needed
  if (pac.red_action_to_perform == NO_ACTION && pac.green_action_to_perform == NO_ACTION) return;

  struct gpiod_chip *chip;
  
  // Open the chip (gpiochip0 is the only one on the pi)
	chip = gpiod_chip_open("/dev/gpiochip0");
	if (NULL == chip) {
    printf("Error: Failed to get chip");
    printf("ERRNO: %s<br>", strerror(errno));
    exit(EXIT_FAILURE);
  }

  if (pac.red_action_to_perform != NO_ACTION) {
    // Get handle for LED line
	  struct gpiod_line *line = gpiod_chip_get_line(chip, LED_RED);
	  if (!line) {
      printf("Error: Failed to get line");
      exit(EXIT_FAILURE);
    }

    if      (pac.red_action_to_perform == ON)  set_line_value(line, LED_RED, 1);
    else if (pac.red_action_to_perform == OFF) set_line_value(line, LED_RED, 0);
    else if (pac.red_action_to_perform == TOGGLE) {
      int val = gpio_get_led_status(LED_RED);

      if (0 == val) set_line_value(line, LED_RED, 1);
      if (1 == val) set_line_value(line, LED_RED, 0);
    }
    gpiod_line_release(line);
  }


  if (pac.green_action_to_perform != NO_ACTION) {
    // Get handle for LED line
	  struct gpiod_line *line = gpiod_chip_get_line(chip, LED_GRN);
	  if (!line) {
      printf("Error: Failed to get line");
      printf("ERRNO: %s<br>", strerror(errno));
      
      exit(EXIT_FAILURE);
    }

    if      (pac.green_action_to_perform == ON)  set_line_value(line, LED_GRN, 1);
    else if (pac.green_action_to_perform == OFF) set_line_value(line, LED_GRN, 0);
    else if (pac.green_action_to_perform == TOGGLE) {
      int val = gpio_get_led_status(LED_GRN);

      if (0 == val) set_line_value(line, LED_GRN, 1);
      if (1 == val) set_line_value(line, LED_GRN, 0);
    }

    gpiod_line_release(line);
  }

  gpiod_chip_close(chip);
}
