#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Node.h"
#include <memory>
#include <string>
#include <vector>

class FileSystem {
private:
    std::shared_ptr<Node> root;
    std::shared_ptr<Node> navigateTo(const std::string& path);

public:
    FileSystem();
    void createFile(const std::string& path, const std::string& content = "");
    void createDirectory(const std::string& path);
    void deleteNode(const std::string& path);
    std::string readFile(const std::string& path);
    void writeFile(const std::string& path, const std::string& content);
    void listDirectory(const std::string& path);
};

#endif // FILESYSTEM_H
