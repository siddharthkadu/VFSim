#include "FileSystem.h"
#include <iostream>
#include <sstream>

FileSystem::FileSystem() {
    root = std::make_shared<Node>("/", Node::Type::DIRECTORY);
}

std::shared_ptr<Node> FileSystem::navigateTo(const std::string& path) {
    auto current = root;
    std::istringstream ss(path);
    std::string part;

    while (std::getline(ss, part, '/')) {
        if (part.empty()) continue;
        if (current->children.find(part) == current->children.end()) {
            throw std::runtime_error("Path not found: " + path);
        }
        current = current->children[part];
    }
    return current;
}

void FileSystem::createFile(const std::string& path, const std::string& content) {
    auto pos = path.find_last_of('/');
    std::string dirPath = path.substr(0, pos);
    std::string fileName = path.substr(pos + 1);

    auto parent = navigateTo(dirPath.empty() ? "/" : dirPath);
    if (!parent->isDirectory()) {
        throw std::runtime_error("Cannot create file in non-directory.");
    }
    parent->children[fileName] = std::make_shared<Node>(fileName, Node::Type::FILE);
    parent->children[fileName]->content = content;
}

void FileSystem::createDirectory(const std::string& path) {
    auto pos = path.find_last_of('/');
    std::string dirPath = path.substr(0, pos);
    std::string dirName = path.substr(pos + 1);

    auto parent = navigateTo(dirPath.empty() ? "/" : dirPath);
    if (!parent->isDirectory()) {
        throw std::runtime_error("Cannot create directory in non-directory.");
    }
    parent->children[dirName] = std::make_shared<Node>(dirName, Node::Type::DIRECTORY);
}

void FileSystem::deleteNode(const std::string& path) {
    auto pos = path.find_last_of('/');
    std::string dirPath = path.substr(0, pos);
    std::string nodeName = path.substr(pos + 1);

    auto parent = navigateTo(dirPath.empty() ? "/" : dirPath);
    parent->children.erase(nodeName);
}

std::string FileSystem::readFile(const std::string& path) {
    auto node = navigateTo(path);
    if (node->isDirectory()) {
        throw std::runtime_error("Cannot read a directory.");
    }
    return node->content;
}

void FileSystem::writeFile(const std::string& path, const std::string& content) {
    auto node = navigateTo(path);
    if (node->isDirectory()) {
        throw std::runtime_error("Cannot write to a directory.");
    }
    node->content = content;
}

void FileSystem::listDirectory(const std::string& path) {
    auto node = navigateTo(path);
    if (!node->isDirectory()) {
        throw std::runtime_error("Path is not a directory.");
    }
    // Replace structured bindings with traditional pair iteration
    for (const auto& pair : node->children) {
        const std::string& name = pair.first;
        const std::shared_ptr<Node>& child = pair.second;
        std::cout << (child->isDirectory() ? "[DIR] " : "[FILE] ") << name << "\n";
    }
}
