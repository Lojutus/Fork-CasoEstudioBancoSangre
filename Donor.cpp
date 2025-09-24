
#include "Donor.h"
#include <sstream>
#include <iostream>
#include <algorithm>

void Donor::donorDetails() const {
    std::cout << "Nombre del donante: " << name << std::endl;
    std::cout << "Distrito del donante: " << district << std::endl;
    std::cout << "Tipo de sangre del donante: " << bloodType << std::endl;
}
std::string Donor::getItemsDonorInfo(const std::string& item) const{
    //BLOQUES DE COMPARCION DEL ITEM
    if (std::find(infoElementsDonorString.begin(), infoElementsDonorString.end(), item) != infoElementsDonorString.end()) {
        return "string";
    }

    // Buscamos en vector de enteros
    if (std::find(infoElementsDonorInt.begin(), infoElementsDonorInt.end(), item) != infoElementsDonorInt.end()) {
        return "int";
    }
    // Si no lo encontramos en ninguno
    return "desconocido";
};// Esta funcion se compone de dos bloques de if los cuales comparan el item con los vectores de strings e ints, si lo encuentra devuelve el tipo de dato, si no lo encuentra devuelve desconocido, intentando respetar el principio Open/Closed
Donor Donor::parseLine(const std::string& line) {
    Donor d;
    std::stringstream ss(line);
    std::string token;

    getline(ss, token, ','); d.donorId = std::stoi(trim(token));
    getline(ss, token, ','); d.name = trim(token);
    getline(ss, token, ','); d.address = trim(token);
    getline(ss, token, ','); d.district = std::stoi(trim(token));
    getline(ss, token, ','); d.bloodType = trim(token);
    getline(ss, token, ','); d.number = trim(token);
    getline(ss, token, ','); d.date = trim(token);
    getline(ss, token, ','); d.donationAmount = std::stoi(trim(token));

    return d;
}

std::string Donor::trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
