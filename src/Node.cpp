#include "Node.h"

Node::Node(const std::string& name, Type type)
    : name(name), type(type), creationTime(std::time(nullptr)) {}

bool Node::isDirectory() const {
    return type == Type::DIRECTORY;
}
