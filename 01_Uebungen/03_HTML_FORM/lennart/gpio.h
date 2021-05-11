#pragma once

#define LED_RED 16
#define LED_GRN 20

#include <gpiod.h>

enum gpio_action_to_perform{NO_ACTION, ON, OFF, TOGGLE};
struct Parsed_actions {
  int red_action_to_perform;
  int green_action_to_perform;
};


static int set_line_value(struct gpiod_line*, int, int);
int gpio_get_led_status(int);
void gpio_handle_led_actions(struct Parsed_actions);
