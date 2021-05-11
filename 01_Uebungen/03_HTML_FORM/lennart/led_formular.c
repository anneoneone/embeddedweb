/*
  Advanced led setter.
  Expands the last taks by adding a CGI wrapper.
  Commands like 'red=on' should be passed via stdin.
  Which happens when executing a POST request on this program.

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
  Date  : 10.05.2021

*/
#include "html.h"
#include "gpio.h"

#define LED_RED 16
#define LED_GRN 20


int main() {

  // Check the request method (1-GET, 0-POST)
  int req_m = html_get_request_method();
  if (req_m == 1) {
    // Just send HTML
    html_print();

  }else if(req_m == 0){
    // Handle stdin
    struct Parsed_actions pac = html_parse_stdin();
    gpio_handle_led_actions(pac);
    html_print();

  }else {
    html_print_error("Unknown request method");
  }

  exit(EXIT_SUCCESS);
}
