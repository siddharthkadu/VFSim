#ifndef NODE_H
#define NODE_H

#include <string>
#include <unordered_map>
#include <ctime>
#include <memory>

class Node {
public:
    enum class Type { FILE, DIRECTORY };

    std::string name;
    Type type;
    std::string content; // For files
    std::unordered_map<std::string, std::shared_ptr<Node>> children; // For directories
    std::time_t creationTime;

    Node(const std::string& name, Type type);
    bool isDirectory() const;
};

#endif // NODE_H
