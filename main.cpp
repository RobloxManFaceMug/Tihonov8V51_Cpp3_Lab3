#include <iostream>
#include <iterator>
#include <stdexcept>
#include "containers.hpp"

int main() {
    std::cout << "-DynamicArray-" << std::endl;
    DynamicArray<int> Container;
    Container.push_back(0);
    Container.push_back(1);
    Container.push_back(2);
    Container.push_back(3);
    Container.push_back(4);
    Container.push_back(5);
    Container.push_back(6);
    Container.push_back(7);
    Container.push_back(8);
    Container.push_back(9);
    for (size_t i = 0; i < Container.size(); i++) {
        std::cout << Container[i] << " ";
    }

    std::cout << std::endl << Container.size() << std::endl;

    Container.erase(2);
    Container.erase(3);
    Container.erase(4);
    for (size_t i = 0; i < Container.size(); i++) {
        std::cout << Container[i] << " ";
    }
    std::cout << std::endl;

    Container.insert(0, 10);
    for (size_t i = 0; i < Container.size(); i++) {
        std::cout << Container[i] << " ";
    }
    std::cout << std::endl;

    Container.insert(4, 20);
    for (size_t i = 0; i < Container.size(); i++) {
        std::cout << Container[i] << " ";
    }
    std::cout << std::endl;

    Container.push_back(30);
    for (size_t i = 0; i < Container.size(); i++) {
        std::cout << Container[i] << " ";
    }
    std::cout << std::endl;


    std::cout << "-list-" << std::endl;
    List<int> Container2;
    Container2.push_back(0);
    Container2.push_back(1);
    Container2.push_back(2);
    Container2.push_back(3);
    Container2.push_back(4);
    Container2.push_back(5);
    Container2.push_back(6);
    Container2.push_back(7);
    Container2.push_back(8);
    Container2.push_back(9);
    for (size_t i = 0; i < Container2.size(); i++) {
        std::cout << Container2[i] << " ";
    }

    std::cout << std::endl << Container2.size() << std::endl;

    Container2.erase(2);
    Container2.erase(3);
    Container2.erase(4);
    for (size_t i = 0; i < Container2.size(); i++) {
        std::cout << Container2[i] << " ";
    }
    std::cout << std::endl;
    
    Container2.push_front(10);
    for (size_t i = 0; i < Container2.size(); i++) {
        std::cout << Container2[i] << " ";
    }
    std::cout << std::endl;

    Container2.insert(4, 20);
    for (size_t i = 0; i < Container2.size(); i++) {
        std::cout << Container2[i] << " ";
    }
    std::cout << std::endl;

    Container2.push_back(30);
    for (size_t i = 0; i < Container2.size(); i++) {
        std::cout << Container2[i] << " ";
    }
    std::cout << std::endl;
}