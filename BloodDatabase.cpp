
#include "BloodDatabase.h"
#include <algorithm>
#include <cctype>
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

std::string BloodDatabase::getInformation(const std::string infoRequired) {
  std::string info = "";
  std::cout << "Ingrese " << infoRequired << " :" << std::endl;
  clearConsole();
  std::getline(std::cin, info);
  // cin >> info;

  Donor d; // donante temporal para comprovar si los datos existen en la clase
  if (d.getItemsDonorInfo(infoRequired) == "string") {

    info = getValidatedStringInput(
        info, infoRequired); // VALIDA LA ENTRADA DEL USUARIO
  } else if (d.getItemsDonorInfo(infoRequired) == "int") {
    info = std::to_string(getValidatedInput(
        info, infoRequired)); // VALIDA LA ENTRADA DEL USUARIO com entero

  } else {
    std::cout << "El tipo de dato no es válido." << std::endl;
  }
  return info;
}

void BloodDatabase::displayProvinces() {
  std::cout << "Elige el departamento:\n";
  std::cout << "1. Putumayo\n";
  std::cout << "2. Cauca\n";
  std::cout << "3. Valle del Cauca\n";
  std::cout << "4. Amazonas\n";
  std::cout << "5. Risaralda\n";
  std::cout << "6. Antioquia\n";
  std::cout << "7. Norte de Santander\n";
  std::cout << "8. Choco\n";
  std::cout << "9. Arauca\n";
  std::cout << "10. Guainía\n" << std::endl;
} // MUESTRA LOS DEPARTAMENTOS

void BloodDatabase::clearConsole() {
#ifdef _WIN32
  system("cls");
#else
  //   system("clear");
#endif
} // LIMPIA LA CONSOLA

void BloodDatabase::waitForKeyPress() {
  std::cout << "Presiona cualquier tecla para continuar..." << std::endl;
  std::cin.ignore();
  std::cin.get();
} // ESPERA A QUE EL USUARIO PRESIONE UNA TECLA

int BloodDatabase::getValidatedInput(const std::string &value,
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
// VALIDA LA ENTRADA DEL USUARIO

std::string
BloodDatabase::getValidatedStringInput(const std::string &value,
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
  // PIDE EL VALOR DE NUEVO, se verifica los inputs strings

void BloodDatabase::getDonorDetails() {
  clearConsole();
  std::cout << "Ingrese los detalles del donante\n" << std::endl;

  Donor newDonor;
  newDonor.donorId = std::stoi(getInformation("donorId"));
  newDonor.name = getInformation("name");
  newDonor.address = getInformation("address");
  displayProvinces();
  newDonor.district = std::stoi(getInformation("district"));
  std::cout << "Tipo de sangre: \n 1. A+\n 2. A-\n 3. B+\n 4. B-\n 5. AB+\n 6. "
               "AB-\n 7. "
               "O+\n 8. O- \n ";
  newDonor.bloodType = std::stoi(getInformation("bloodType"));
  newDonor.number = getInformation("number");
  newDonor.date = getInformation("Fecha de donacion");
  newDonor.donationAmount = std::stoi(getInformation("Cantiddad de donacion"));

  donors.push_back(newDonor);
} // PRIMERO PIDE LOS DATOS DEL DONANTE Y LUEGO LOS USA PARA  GUARDAR EN EL
  // VECTOR DE DONANTES,

void BloodDatabase::writeDataToFile() {
  std::ofstream outfile(fileName, std::ios::app);

  if (!outfile) {
    std::cout << "Error al abrir el archivo para escribir." << std::endl;
    return;
  }

  Donor newDonor = donors.back();
  outfile << newDonor.donorId << ",    " << newDonor.name << ",    "
          << newDonor.address << ",    " << newDonor.district << ",    "
          << newDonor.bloodType << ",    " << newDonor.number << ",    "
          << newDonor.date << std::endl;

  outfile.close();
} // ESCRIBE LOS DATOS DEL DONANTE EN EL ARCHIVO, RESPETA SRP , , Y OPen/Closed

void BloodDatabase::searchAndDisplay() const {
  clearConsole();
  displayProvinces();
  int provinceName = std::stoi(getInformation("district"));

  std::cout << "Ingrese la dirección (dejar en blanco para omitir): "
            << std::endl;
  std::string addressFilter;
  addressFilter = getInformation("address");

  std::cout << "Ingrese el tipo de sangre (dejar en blanco para omitir): "
            << std::endl;

  std::string bloodTypeFilter;
  bloodTypeFilter = getInformation("bloodType");

  std::ifstream inFile(fileName);

  if (!inFile) {
    std::cout << "Error al abrir el archivo para leer." << std::endl;
    return;
  }

  std::vector<Donor> donors;
  std::string line;
  bool found = false;

  while (std::getline(inFile, line)) {
    try {
      Donor d = Donor::parseLine(line);

      bool match = d.district == provinceName &&
                   (addressFilter.empty() ||
                    d.address.find(addressFilter) != std::string::npos) &&
                   (bloodTypeFilter.empty() || d.bloodType == bloodTypeFilter);

      if (match) {
        donors.push_back(d);
        found = true;
      }
    } catch (const std::exception &e) {
      std::cerr << "Error procesando línea: " << line << std::endl;
      std::cerr << "Mensaje de error: " << e.what() << std::endl;
      return;
    }
  }

  if (!found) {
    std::cout << "No se encontraron personas de la departamento "
              << provinceName;
    if (!addressFilter.empty()) {
      std::cout << " con dirección que contiene '" << addressFilter << "'";
    }
    if (!bloodTypeFilter.empty()) {
      std::cout << " y tipo de sangre '" << bloodTypeFilter << "'";
    }
    std::cout << "." << std::endl;
  } else {
    std::cout << "Personas de la departamento " << provinceName;
    if (!addressFilter.empty()) {
      std::cout << " con dirección que contiene '" << addressFilter << "'";
    }
    if (!bloodTypeFilter.empty()) {
      std::cout << " y tipo de sangre '" << bloodTypeFilter << "'";
    }
    std::cout << ":" << std::endl;
    for (const auto &d : donors) {

      std::cout << "Nombre: " << d.name << std::endl;
      std::cout << "Dirección: " << d.address << std::endl;
      std::cout << "departamento: " << d.district << std::endl;
      std::cout << "Tipo de sangre: " << d.bloodType << std::endl;
      std::cout << "Número de móvil: " << d.number << std::endl;
      std::cout << std::endl;
    }
  }

  inFile.close();
  waitForKeyPress();
} // PIDE LA DIRECCION , PIDE LA SANGRE , ABRE EL ARCHIVO PARA LEER,BUSCA EN  EL
  // ARCHIVO .

void BloodDatabase::deleteDonor(const std::string &donorName) {
  std::ifstream inFile(fileName);
  std::ofstream tempFile("temp.txt");

  if (!inFile) {
    std::cerr << "Error al abrir el archivo " << fileName << std::endl;
    return;
  }

  if (!tempFile) {
    std::cerr << "Error al crear el archivo temporal" << std::endl;
    return;
  }

  std::string line;
  bool found = false;

  while (std::getline(inFile, line)) {
    Donor d = Donor::parseLine(line);
    if (d.name == donorName) {
      found = true;
      std::cout << "Nombre: " << d.name << std::endl;
      std::cout << "Dirección: " << d.address << std::endl;
      std::cout << "Tipo de sangre: " << d.bloodType << std::endl;
      std::cout << "Número de móvil: " << d.number << std::endl;
      std::cout << std::endl;
      std::cout << "¿Está seguro de que desea eliminar al donante? [s/n]: ";
      char sureChoice;
      std::cin >> sureChoice;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                      '\n'); // descartar cualquier entrada extra

      if (sureChoice == 's' || sureChoice == 'S') {
        continue;
      }
    }

    tempFile << d.donorId << ",    " << d.name << ",    " << d.address
             << ",    " << d.district << ",    " << d.bloodType << ",    "
             << d.number << std::endl;
  }

  inFile.close();
  tempFile.close();

  if (std::remove(fileName.c_str()) != 0) {
    std::cerr << "Error al eliminar el archivo original" << std::endl;
    return;
  }

  if (std::rename("temp.txt", fileName.c_str()) != 0) {
    std::cerr << "Error al renombrar el archivo temporal" << std::endl;
    return;
  }

  if (!found) {
    std::cout << "No se encontró ningún donante con el nombre " << donorName
              << std::endl;
  }
} // ABRE EL ARCHIVO ( FUNCION EXTERNA), VERIFICA SI ESTA SEGURO DE ELIMINAR EL
  // DONANTE, SI LO ESTA LO ELIMINA, CIERRA EL ARCHIVO
  // el OPen/Closed
std::string BloodDatabase::getZoneName(int zoneCode) const { // DEBERIA DE SER UN ARREGLO PARA PODER MODIFICARLO MAS FACILMENTE
  switch(zoneCode) {
    case 1: return "Putumayo";
    case 2: return "Cauca";
    case 3: return "Valle del Cauca";
    case 4: return "Amazonas";
    case 5: return "Risaralda";
    case 6: return "Antioquia";
    case 7: return "Norte de Santander";
    case 8: return "Choco";
    case 9: return "Arauca";
    case 10: return "Guainía";
    default: return "Zona Desconocida";
  }
}

std::string BloodDatabase::normalizeBloodType(const std::string& bloodType) const {
  // Si es un número (del menú), convertir a tipo de sangre
  if (bloodType == "1") return "A+";
  if (bloodType == "2") return "A-";
  if (bloodType == "3") return "B+";
  if (bloodType == "4") return "B-";
  if (bloodType == "5") return "AB+";
  if (bloodType == "6") return "AB-";
  if (bloodType == "7") return "O+";
  if (bloodType == "8") return "O-";

  // Si ya es texto, normalizar el formato
  std::string normalized = bloodType;
  std::transform(normalized.begin(), normalized.end(), normalized.begin(), ::toupper);

  // Validar que sea un tipo de sangre conocido
  if (normalized == "A+" || normalized == "A-" || 
      normalized == "B+" || normalized == "B-" ||
      normalized == "AB+" || normalized == "AB-" ||
      normalized == "O+" || normalized == "O-") {
    return normalized;
  }

  return "DESCONOCIDO";
}

void BloodDatabase::readDataFromFileAndSave() {
  std::ifstream inFile(fileName);

  if (!inFile) {
    std::cout << "Error al abrir el archivo para leer." << std::endl;
    waitForKeyPress();
    return;
  }

  // Mapas para contar donantes por zona y tipo de sangre
  std::map<int, std::map<std::string, int>> donorsByZoneAndType;
  std::map<int, int> totalDonorsByZone; // LOS MAPS SON DICCIONRIOS QUE PERMITEN ALMACENAR DATOS DE FORMA ORDENADA Y ACCEDER A ELLOS RÁPIDAMENTE POR UNA CLAVE

  std::string line;
  int totalValidDonors = 0;
  int invalidLines = 0;

  while (std::getline(inFile, line)) {
    if (line.empty()) continue;

    try {
      Donor d = Donor::parseLine(line);

      // Normalizar tipo de sangre
      std::string normalizedBloodType = normalizeBloodType(d.bloodType);

      // Solo contar donantes con datos válidos
      if (d.district >= 1 && d.district <= 10 && normalizedBloodType != "DESCONOCIDO") { // Aqui Deberia de contar la longitud de el arreglo de zonas ( pero como no hay se hace con codigo duro )
        donorsByZoneAndType[d.district][normalizedBloodType]++;
        totalDonorsByZone[d.district]++;
        totalValidDonors++;
      } else {
        invalidLines++;
      }
    } catch (const std::exception &e) {
      invalidLines++;
      continue;
    }
  }

  inFile.close();

  // Mostrar el reporte
  clearConsole();
  std::cout << "=== REPORTE DE DONANTES POR TIPO DE SANGRE Y ZONA ===" << std::endl;
  std::cout << "======================================================" << std::endl << std::endl;

  if (totalValidDonors == 0) {
    std::cout << "No se encontraron donantes con datos válidos." << std::endl;
    waitForKeyPress();
    return;
  }

  // Mostrar estadísticas generales
  std::cout << "Total de donantes válidos: " << totalValidDonors << std::endl;
  if (invalidLines > 0) {
    std::cout << "Líneas con datos inválidos ignoradas: " << invalidLines << std::endl;
  }
  std::cout << std::endl;

  // Tipos de sangre a reportar
  std::vector<std::string> bloodTypes = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};

  // Reporte por zona
  for (int zone = 1; zone <= 10; zone++) {
    if (totalDonorsByZone.find(zone) != totalDonorsByZone.end()) {
      std::cout << "--- " << getZoneName(zone) << " ---" << std::endl;
      std::cout << "Total de donantes en esta zona: " << totalDonorsByZone[zone] << std::endl;

      for (const std::string& bloodType : bloodTypes) {
        int count = 0;
        if (donorsByZoneAndType[zone].find(bloodType) != donorsByZoneAndType[zone].end()) {
          count = donorsByZoneAndType[zone][bloodType];
        }

        double percentage = (totalDonorsByZone[zone] > 0) ? 
                           (static_cast<double>(count) / totalDonorsByZone[zone]) * 100.0 : 0.0;

        std::cout << "  " << bloodType << ": " << count << " donantes (" 
                  << std::fixed << std::setprecision(1) << percentage << "%)" << std::endl;
      }
      std::cout << std::endl;
    }
  }

  // Resumen nacional por tipo de sangre
  std::cout << "=== RESUMEN NACIONAL POR TIPO DE SANGRE ===" << std::endl;
  std::map<std::string, int> nationalCounts;

  for (const auto& zone : donorsByZoneAndType) {
    for (const auto& bloodType : zone.second) {
      nationalCounts[bloodType.first] += bloodType.second;
    }
  }

  for (const std::string& bloodType : bloodTypes) {
    int count = nationalCounts[bloodType];
    double percentage = (totalValidDonors > 0) ? 
                       (static_cast<double>(count) / totalValidDonors) * 100.0 : 0.0;

    std::cout << bloodType << ": " << count << " donantes (" 
              << std::fixed << std::setprecision(1) << percentage << "% del total nacional)" << std::endl;
  }

  std::cout << std::endl;
  waitForKeyPress();
}