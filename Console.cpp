
#include "Console.h"
#include "Donor.h"
#include <sstream>
#include <iostream>
#include <algorithm>

void Console::clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
void Console::waitForKeyPress() {
  std::cout << "Presiona cualquier tecla para continuar..." << std::endl;
  std::cin.ignore();
  std::cin.get();
} // ESPERA A QUE EL USUARIO PRESIONE UNA TECLA
int Console::getValidatedInput(const std::string &value,
                                     const std::string &infoType) {
  int newValue = 0;
  std::string info = value;

  while (true) {
    try {
      // Validar que todos los caracteres sean dígitos
      if (!std::all_of(info.begin(), info.end(),
                       [](unsigned char c) { return std::isdigit(c); })) {
        throw std::invalid_argument(
            "La entrada contiene caracteres no numéricos");
      }

      // Convertir a entero
      newValue = std::stoi(info);

      break; // salida del while si todo salió bien

    } catch (const std::invalid_argument &e) {
      std::cout << "Entrada no válida: " << e.what()
                << ". Por favor ingrese un número válido." << std::endl;

      info = getInformation(infoType); // obtienes nuevo valor
    } catch (const std::out_of_range &e) {
      std::cout << "Entrada fuera de rango: " << e.what()
                << ". Por favor ingrese un número válido." << std::endl;
      info = getInformation(infoType);
    }
  }

  return newValue;
}
std::string Console::getValidatedStringInput(const std::string &value,
                                       const std::string &infoType) {

  if (value.length() > 20) {
    std::cout << "La entrada debe tener maximo 20 caracteres. Inténtalo "
                 "de nuevo."
              << std::endl;
    return getInformation(
        infoType); // Llamada recursiva para obtener una entrada válida si la
                   // actual no es válida Y devolverla a la funcion que la llamo
  }

  return value; //
} // VALIDA LA ENTRADA DEL USUARIO  , TAMBIEN SI RECIBE UN ERROR DE VERIFICACION
std::string Console::getInformation(const std::string infoRequired)//verifica si el dato que se pide existe en la clase Donante
{
  std::string info = "";
  std::cout << "Ingrese " << infoRequired << " :" << std::endl;
  
  std::getline(std::cin, info);
  // cin >> info;

  Donor d; // donante temporal para comprovar si los datos existen en la clase
  if (d.getItemsDonorInfo(infoRequired) == "string") {

    info = getValidatedStringInput(info, infoRequired); // VALIDA LA ENTRADA DEL USUARIO

  } else if (d.getItemsDonorInfo(infoRequired) == "int") {
    info = std::to_string(getValidatedInput(info, infoRequired)); // VALIDA LA ENTRADA DEL USUARIO com entero

  } else {
    std::cout << "El tipo de dato no es válido." << std::endl;
  }
  return info;
}
Console::Console() {}