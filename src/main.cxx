#include <string>

import Image;

int main() {
    Image test {255, 255, 255};
    std::string path = "../src/test.png";
    test.read_png(path);
    test.save_as_ppm("try2.ppm");
    return 0;
}
