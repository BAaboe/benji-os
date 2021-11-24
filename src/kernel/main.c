#define VIDEO_MEM 0xb8000


void dummy_test_entrypoint() {
}

void printl( int colour, const unsigned char *string, int pos);
int printnl( int colour, const unsigned char * string, int current_line);
void print( int colour, const unsigned char *string);



void main() {
    int line = 0;

    line = printnl(0x1f, "Kernel loaded sucsefully!", line);
    line = printnl(0x1f, "Welcome to BenjiOS", line);
}

void print( int colour, const unsigned char *string) {

    unsigned char *vid = (unsigned char*) VIDEO_MEM;
    while(*string != 0)
    {
        *vid = *string;
        *(vid+1) = colour;
        ++string;
        vid+=2;
    }

}

void printl( int colour, const unsigned char *string, int pos) {

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

int printnl( int colour, const unsigned char *string, int current_line) {

    int new_line = current_line++;


    printl(colour, string, new_line);

    return new_line;

}