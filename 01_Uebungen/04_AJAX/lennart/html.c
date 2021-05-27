/*
  This C-file handles cgi and HTML related stuff.

  Author: Lennart Brun
  Date  : 10.05.2021

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gpio.h"


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
 * @returns Parsed action struct which contains action for for each led
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
