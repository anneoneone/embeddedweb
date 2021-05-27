#pragma once

void html_print();
void html_print_error(const char*);

int html_get_request_method();
struct Parsed_actions html_parse_stdin();

