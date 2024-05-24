#include <cstdint>
#include <vector>

import Image;

int main() {
    Image test {3, 2, 255};
    std::vector<uint8_t> pixels {255, 0, 0, 0, 255, 0, 0, 0, 255, 255, 255, 0, 255, 255, 255, 0, 0, 0};
    test.set_pixels(pixels);
    test.print_as_ppm();
    return 0;
}
