/*
  This C-file handles cgi and HTML related stuff.

  Author: Lennart Brun
  Date  : 10.05.2021

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "gpio.h"



static const char* red_led_fieldset = "\
 <fieldset> \
 <legend>RED LED</legend> \
 <input type='radio' name='red' value='on'>Turn on</input><br> \
 <input type='radio' name='red' value='off'>Turn off</input><br> \
 <input type='radio' name='red' value='toggle'>Toggle</input><br> \
 </fieldset>";

static const char* green_led_fieldset = "\
 <fieldset> \
 <legend>GREEN LED</legend> \
 <input type='radio' name='green' value='on'>Turn on</input><br> \
 <input type='radio' name='green' value='off'>Turn off</input><br> \
 <input type='radio' name='green' value='toggle'>Toggle</input><br> \
 </fieldset>";


/**
 * Prints a error HTML response
 * @param error_str A string that should describe the error.
 */
void html_print_error(const char* error_str) {
  printf("Content-type: text/html\n\n");
  printf("<html><title>LED Setter</title><body>\n");
  printf("ERROR: %s<br>", error_str);
  printf("ERRNO: %s<br>", strerror(errno));
  printf("</body></html>");
}

/**
 * Prints the normal HTML response
 */
void html_print() {
  // Print header
  printf("Content-type: text/html\n\n");
  printf("<html><title>LED Setter</title><body>\n");
 
  // Print current states
  printf("<h2>Current state:</h2>");
  printf("<table style='width: 300px;'><tr><td>RED LED</td><td>GREEN LED</td></tr><tr><td>\n");

  int ret = gpio_get_led_status(LED_RED);
  const char *color = ret == 1 ? "f00" : "8a4141";
  const char *state = ret == 1 ? "ON" : "OFF";
  printf("<span style='height: 25px; width: 25px; border-radius:50%; display: inline-block;  background-color: %s'></span>%s<br>", color, state); 
  
  printf("</td><td>");

  ret = gpio_get_led_status(LED_GRN);
  color = ret == 1 ? "19eb15" : "0f5c0e";
  state = ret == 1 ? "ON" : "OFF";
  printf("<span style='height: 25px; width: 25px; border-radius:50%; display: inline-block;  background-color: %s'></span>%s", color, state); 
  
  printf("</td></tr></table>");

  // Print form for manipulation of leds
  printf("<h2>Manipulate state:</h2>");
  printf("<form action='/cgi-bin/led_formular' method='POST'>\n");
  printf("<table><tr><td>");
  printf(red_led_fieldset);
  printf("</td><td>");
  printf(green_led_fieldset);
  printf("</td><tr></table>");
  printf("<input type='submit'>\n");
  printf("</form><br>");
  printf("</body></html>");
}


/**
 * Checks the environment variable "REQUEST_METHOD"
 * @returns 0 for POST, 1 for GET, -1 on error
 */
int html_get_request_method() {
  const char* env = getenv("REQUEST_METHOD");
  
  if (env == NULL) return -1;
  if (strcmp(env, "POST") == 0) return 0;
  if (strcmp(env, "GET")  == 0) return 1;
  return -1;
}


/**
 * Parse the stdin for red/green led commands
 * @returns Parsed action struct which contains action infor for each led
 */
struct Parsed_actions html_parse_stdin() {
  struct Parsed_actions pac;
  char buffer[100];

  // Set default actions
  pac.red_action_to_perform = NO_ACTION;
  pac.green_action_to_perform = NO_ACTION;
  
  // Read from stdin
  char* ret = fgets(buffer, sizeof(buffer), stdin);

  if (ret == NULL) return pac;
  
  char sep[1] = "&";
  char *result;

  result = strtok(buffer, sep);

  while (result != NULL) {
    // Parse command
    const char* command = strchr(result, (int)'=') + 1;

    int command_num;
    if      (strcmp(command, "on")     == 0) command_num = ON;
    else if (strcmp(command, "off")    == 0) command_num = OFF;
    else if (strcmp(command, "toggle") == 0) command_num = TOGGLE;
    else command_num = NO_ACTION;
   
    // Check for color and set the corresponding action
    if      (strstr(result, "red")   != NULL) pac.red_action_to_perform = command_num;
    else if (strstr(result, "green") != NULL) pac.green_action_to_perform = command_num;

    // Search for next command
    result = strtok(NULL, sep);
  }

  return pac;
}
