#include "FileSystem.h"
#include <iostream>

int main() {
    FileSystem fs;

    try {
        fs.createDirectory("/home");
        fs.createFile("/home/file1.txt", "Hello, World!");
        fs.createDirectory("/home/docs");
        fs.createFile("/home/docs/file2.txt", "C++ File System");

        std::cout << "Listing /home:\n";
        fs.listDirectory("/home");

        std::cout << "\nReading /home/file1.txt:\n";
        std::cout << fs.readFile("/home/file1.txt") << "\n";

        fs.deleteNode("/home/file1.txt");
        std::cout << "\nAfter deleting file1.txt:\n";
        fs.listDirectory("/home");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
