#include <cstring>
#include <iostream>
#include <Forgebase.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <MODE> | [PARAMETER]" << std::endl;
        return -1;
    }
    const auto mode = argv[1];
    if (strcmp(mode, "index") == 0) {
        Forgebase::index();
    } else {
        if (argc < 3) {
            std::cout << "Missing search keyword!" << std::endl;
            return -1;
        }
        const auto keyword = argv[2];
        Forgebase::search(keyword);
    }
    return 0;
}
