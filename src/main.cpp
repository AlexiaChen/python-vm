#include "bufferedInputStream.hpp"

int main(int argc, char** argv) {
    if (argc <= 1) {
        printf("vm need a parameter : filename\n");
        return 0;
    }

    BufferedInputStream stream(argv[1]);
    printf("magic number is 0x%x\n", stream.read_int());

    return 0;
}

