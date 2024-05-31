#include <cstdint>
#include <string>

import Image;

int main() {
    Image<uint8_t, (uint8_t)3> test (255, 255, 255);
    std::string path = "../src/test.png";
    test.read_png(path);
    test.save_as_file<3>("try2.ppm");
    return 0;
}
