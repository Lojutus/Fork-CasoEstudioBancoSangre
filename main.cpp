
#include "BloodDatabase.h"
#include "Donor.h"
#include <iostream>
#include <limits>
#include <string>
using namespace std;

int main() {
  std::string donorName;
  BloodDatabase database;
  int choice;

  std::string valor;

  while (true) {
    BloodDatabase::clearConsole();

    std::cout << " ░█████╗░██████╗░██╗░░░██╗███████╗  ██████╗░░█████╗░░░░░░██╗░"
                 "█████╗░\n"
                 " ██╔══██╗██╔══██╗██║░░░██║╚════██║  ██╔══██╗██╔══██╗░░░░░██║█"
                 "█╔══██╗\n"
                 " ██║░░╚═╝██████╔╝██║░░░██║░░███╔═╝  ██████╔╝██║░░██║░░░░░██║█"
                 "██████║\n"
                 " ██║░░██╗██╔══██╗██║░░░██║██╔══╝░░  ██╔══██╗██║░░██║██╗░░██║█"
                 "█╔══██║\n"
                 " ╚█████╔╝██║░░██║╚██████╔╝███████╗  ██║░░██║╚█████╔╝╚█████╔╝█"
                 "█║░░██║\n"
                 " ░╚════╝░╚═╝░░╚═╝░╚═════╝░╚══════╝  ╚═╝░░╚═╝░╚════╝░░╚════╝░╚"
                 "═╝░░╚═╝\n";

    std::cout << "1. Registrar donante\n";
    std::cout << "2. Buscar donante\n";
    std::cout << "3. Eliminar donante\n";
    std::cout << "4. Salir\n";
    std::cout << "5. Reporte de donaciones\n";
    std::cout << "Ingrese su elección: ";

    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                    '\n'); // descartar cualquier entrada extra

    switch (choice) {
    case 1:
      database.getDonorDetails();
      database.writeDataToFile();
      std::cout << "Donante registrado exitosamente.\n";
      break;
    case 2:
      database.searchAndDisplay();
      break;
    case 3:
      std::cout << "Ingrese el nombre del donante a eliminar: ";
      std::getline(std::cin, donorName);
      database.deleteDonor(donorName);
      BloodDatabase::waitForKeyPress();
      break;

    case 4:
      std::cout << "Gracias por usar el Sistema de la Cruz Roja" << std::endl;
      return 0;

    case 5:
      std::cout << "Reporte de donaciones" << std::endl;
      database.readDataFromFileAndSave();
      break;

    default:
      std::cout << "Opción no válida. Inténtalo de nuevo.\n";
      BloodDatabase::waitForKeyPress();
      break;
    }
  }
}
