#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


int setLed(struct gpiod_line* line, int ledIsOn) {
	return  gpiod_line_set_value(line, ledIsOn);
}

int toggleLed(struct gpiod_line* line) {
	int ledIsOn = 1;
	int returned_value;

	do {
		returned_value = setLed(line, ledIsOn);
		if (returned_value < 0)
			return -1;
		sleep(1);
		ledIsOn = !ledIsOn;
	} while (1);
}

int main(int argc, char *argv[]){
	struct gpiod_chip *chip;
	struct gpiod_line *line;

	char *chip_name = "gpiochip0";
	int line_number = 21;
	int ledIsOn;
	int returned_value;

	chip = gpiod_chip_open_by_name(chip_name);
	if (!chip) {
		perror("ERROR: open chip");
		goto end;
	}

	line = gpiod_chip_get_line(chip, line_number);
	if (!line) {
		perror("ERROR: get line number");
		goto close_chip;
	}

	returned_value = gpiod_line_request_output(line, "Consumer", 0);
	if (returned_value < 0) {
		perror("ERROR: couldn't request line as output");
		goto release_line;
	}

	if (strcmp(argv[1], "on") == 0){
		ledIsOn = 1;
		returned_value = setLed(line, ledIsOn);
	}
	else if (strcmp(argv[1], "off") == 0){
		ledIsOn = 0;
		returned_value = setLed(line, ledIsOn);
	}
	else if (strcmp(argv[1], "toggle") == 0){
		returned_value = toggleLed(line);
	}
	else {
		printf("Wrong command line argmuent.");
	}
	
	if (returned_value < 0) {
		perror("ERROR: couldn't set output line");
		goto release_line;
	}

release_line:
	gpiod_line_release(line);
close_chip:
	gpiod_chip_close(chip);
end:
	return 0;
}
