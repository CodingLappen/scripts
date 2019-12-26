#define HELP_TXT 
#define SYNTAX
#define FLAG
#define c
#include <string.h> 

bool has_str(char * String, char * inString){
	 return false;
	 // Find the function of the string who exactly does that, or build it yourself.
}
char * String_first_Remove(char * String, char * inString) {
	 return null;
}




int main (int argc, char *argv[] ) {
	/*
	 *  Parsing the Input
	 * */
	bool QUERY_SET = false;
	bool verbose;
	bool version;
	bool file_out;
	bool file_must_be_set;
	bool std_out;
	bool replace_by;


	char * file;
	char * regex;
	int operator = 0;
	char *c; 
	if (argc < 1) stdout << HELP_TXT ;
	else {
		for (operator=0; operator< argc; operator++) {
			c = argv[operator];
			if ( file_must_be_set ) {
				file = c; 
		       		continue;
			}
			else if (replace_by) {
				regex =c;
			} else if (has_str(c, FLAG)) {
				c = String_first_Remove(c, FLAG) ;
				if (c == null) continue; 
				if (strcmp(c, "--verbose") verbose = true; else {
				if (strcmp(c, "--version") version = true; else {
				if (strcmp(c, "--output-file") {
						 file_out = true;
						 file_must_be_set = true;
						}else {
				if (strcmp(c, "--stdout") std_out=true; else {
				if (strcmp(c, "--replace") replace_by=true; else {
					continue;
						}}}}}
			}
		}
	}
}
