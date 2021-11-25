#define VIDEO_MEM 0xb8000


void dummy_test_entrypoint() {
}

void printl( const unsigned char *string, int pos);
int printnl( const unsigned char * string, int current_line);
void print(const unsigned char *string);
void clear_screen();
void fill_screen(int color);

void main() {
    int line = 0;

    line = printnl("Kernel loaded sucsefully!", line);
    clear_screen();
    line = 0;
    line = printnl("Welcome to BenjiOS", line);

}

void print( const unsigned char *string) {

    int colour = 0x0a;
    unsigned char *vid = (unsigned char*) VIDEO_MEM;
    while(*string != 0)
    {
        *vid = *string;
        *(vid+1) = colour;
        ++string;
        vid+=2;
    }

}

void printl( const unsigned char *string, int pos) {

    int colour = 0x0a;
    unsigned char *vid = (unsigned char*) VIDEO_MEM;
    vid+=pos*160;
    while(*string != 0)
    {
        *vid = *string;
        *(vid+1) = colour;
        ++string;
        vid+=2;
    }

}

int printnl(const unsigned char *string, int current_line) {

    printl(string, current_line);
    int new_line = ++current_line;
    return new_line;

}

void clear_screen(){
    unsigned char *vid = (unsigned char*) VIDEO_MEM;
    for (int i = 0; i<(30*160); i++) {
        *vid = ' ';
        *(vid+1) = 0x00;
        vid+=2;
    }
}

void fill_screen(int color) {
    unsigned char *vid = (unsigned char*) VIDEO_MEM;
    for (int i = 0; i<(30*160); i++) {
        *(vid+1) = color;
        vid+=2;
    }
}