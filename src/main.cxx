#include <vector>
#include <cstdint>

import Image;

int main() {
    Image test {255, 255, 255};
    const char* path = "../src/test.png";
    test.read_png(path);
    test.print_as_ppm();
    return 0;
}
