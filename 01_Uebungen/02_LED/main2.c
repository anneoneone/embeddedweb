#include <stdio.h>
#include <gpiod.h>

int main() {
   struct gpiod_chip *chip;
   struct gpiod_line *line;
   int req, value;

   chip = gpiod_chip_open("/dev/gpiochip0");
   if (chip)
      printf("no chip");
      return -1;


   line = gpiod_chip_get_line(chip, 21);
   if (line) {
      printf("no line");
      gpiod_chip_close(chip);
      return -1;
   }

   req = gpiod_line_request_input(line, "gpio_state");
   if (req) {
      printf("%i", req);
      gpiod_chip_close(chip);
      return -1;
   }

   value = gpiod_line_get_value(line);

   printf("GPIO value is: %d\n", value);

   gpiod_chip_close(chip);

   return 0;
}
