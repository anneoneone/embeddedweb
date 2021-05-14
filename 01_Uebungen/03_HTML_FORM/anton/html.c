#include <stdio.h>
#include <string.h>
#include <gpiod.h>
#include <unistd.h>

int setLed(struct gpiod_line* line, int ledIsOn) {
	return  gpiod_line_set_value(line, ledIsOn);
}

int main(int argc, char *argv[]){

	struct gpiod_chip *chip;
	struct gpiod_line *line;

	char *chip_name = "gpiochip0";
	int line_number = 21;
	int ledIsOn;
	int returned_value;
    
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);

    printf(
        "Context-type:text/html\n\n"
        "<html class='no-js' lang=''>\n"
            "<head>\n"
                "<meta charset='utf-8'>\n"
                "<meta http-equiv='X-UA-Compatible' content='IE=edge,chrome=1'>\n"
                "<title>Antons Cgi Seite</title>\n"
                "<meta name='description' content=''>\n"
                "<meta name='viewport' content='width=device-width, initial-scale=1'>\n"

            "</head>\n"
            "<body>\n"

                "<p>Control the LED</p>\n"
                "<form action='index-cgi' method='POST'>\n"
                    "<input type='radio' id='input1' name='led' value='on'>\n"
                    "<label for='input1'>LED on </label>\n"
                    "<input type='radio' id='input2' name='led' value='off'>\n"
                    "<label for='input2'>LED off </label>\n"
					"<br />\n"
					"<br />\n"
                    "<input type='submit' id='submit1' >\n"
                "</form>\n"
                
                "<script src='https://ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js'></script>\n"

            "</body>\n"
        "</html>\n"

    );

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

	if (strstr(buffer, "on") != NULL){
		ledIsOn = 1;
		returned_value = setLed(line, ledIsOn);
	}
	else if (strstr(buffer, "off") != NULL){
		ledIsOn = 0;
		returned_value = setLed(line, ledIsOn);
	}
	else {
		printf("Could not set LED");
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