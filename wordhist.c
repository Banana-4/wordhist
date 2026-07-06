#include "include/error_codes.h"
#include "include/histogram.h"
#include "include/input.h"
#include "include/memory.h"

int main(int argc, char* argv[]) {
	bool horizontal = false;
	if (argc == 2) {
  		if (argv[1][0] == 'h'){
  			horizontal = true;
    	} else {
     		fprintf(stderr, "Usage: ./wordhist (h) \n");
     	}
  	}
  	StrArray *words = new_StrArray();
   	if (!words) {
    	return 1;
    }
   	int h = 0;
   	ERROR_CODES signal = input_loop(&words, &h);
   	if (signal == ALLOCATION_FAIL) {
    	fprintf(stderr, "Critical error exiting...\n");
     	del_StrArray(words);
      exit(signal);
    }
    histogram(words, h, horizontal);
    del_StrArray(words);
    return 0;
}
