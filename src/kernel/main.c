#define VIDEO_MEM 0xb8000

#include "../drivers/display.h"

void dummy_test_entrypoint() {
}

void printl( const unsigned char *string, int pos);
int printnl( const unsigned char * string, int current_line);
void print(const unsigned char *string);
void clear_screen();
void fill_screen(int color);

void main() {
    clear_screen();
    print_string("Hello, World!\n");
    for (int i=0; i<24; i++){
        print_string("test\n");
    }
}
