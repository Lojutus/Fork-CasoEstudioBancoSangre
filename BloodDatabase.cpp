
#include "BloodDatabase.h"
#include "Console.h"
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

std::vector<Donor> BloodDatabase::donors;





void BloodDatabase::displayProvinces() {

  std::string mensaje =
    "Elige el departamento:\n" "1. Putumayo\n" "2. Cauca\n" "3. Valle del Cauca\n" "4. Amazonas\n"
    "5. Risaralda\n" "6. Antioquia\n" "7. Norte de Santander\n" "8. Choco\n"
    "9. Arauca\n" "10. Guainía\n";

Console::showInfoMessage(mensaje);

} // MUESTRA LOS DEPARTAMENTOS






// VALIDA LA ENTRADA DEL USUARIO


  // PIDE EL VALOR DE NUEVO, se verifica los inputs strings

void BloodDatabase::getDonorDetails() {//Guarda los donantes en el vector
  Console::clearConsole();
  std::string mensaje = "Ingrese los detalles del donante\n";
  Console::showInfoMessage(mensaje);

  Donor newDonor;
  newDonor.setDonorId(std::stoi(Console::getInformation("donorId")));
  newDonor.setName(Console::getInformation("name"));
  newDonor.setAddress(Console::getInformation("address"));
  displayProvinces();
  newDonor.setDistrict(std::stoi(Console::getInformation("district")));
  std::string messageBloodTypes = "Tipos de sangre disponibles:\n";
  messageBloodTypes += bloodTypes;
  Console::showInfoMessage(messageBloodTypes);
  newDonor.setBloodType(Console::getInformation("bloodType"));
  newDonor.setNumber(Console::getInformation("number"));
  newDonor.setDate(Console::getInformation("date"));
  newDonor.setDonationAmount(std::stoi(Console::getInformation("donationAmount")));

  donors.push_back(newDonor);
} // PRIMERO PIDE LOS DATOS DEL DONANTE Y LUEGO LOS USA PARA  GUARDAR EN EL VECTOR DE DONANTES,

void BloodDatabase::writeDataToFile() {
  std::ofstream outfile(fileName, std::ios::app);

  if (!outfile) {
    std::string mensaje = "Error al abrir el archivo para escribir.\n";
    Console::showInfoMessage(mensaje);

    return;
  }

  Donor newDonor = donors.back();
  outfile << newDonor.getDonorId() << ",    " << newDonor.getName() << ",    "
          << newDonor.getAddress() << ",    " << newDonor.getDistrict() << ",    "
          << newDonor.getBloodType()  << ",    " << newDonor.getNumber() << ",    "
          << newDonor.getDate() << ",    " << newDonor.getDonationAmount() << std::endl;

  outfile.close();
} // ESCRIBE LOS DATOS DEL DONANTE EN EL ARCHIVO, RESPETA SRP , , Y OPen/Closed
void  BloodDatabase::loadDonorsFromFile() const {
  std::ifstream inFile(fileName);

  if (!inFile) {
    Console::showInfoMessage("Error al abrir el archivo para leer.");

    return;
  }

  std::string line;
  donors.clear(); // Limpiar el vector antes de cargar nuevos datos

  while (std::getline(inFile, line)) {
    try {
      Donor d = Donor::parseLine(line);
      donors.push_back(d);
    } catch (const std::exception &e) {
      std::cerr << "Error procesando línea: " << line << std::endl;
      std::cerr << "Mensaje de error: " << e.what() << std::endl;
      continue; // Omitir líneas con errores y continuar
    }
  }
  Console::showInfoMessage("Datos cargados correctamente desde el archivo.");

  inFile.close();
} // ABRE EL ARCHIVO PARA LEER , LEE LINEA POR LINEA Y LA PARSEA , SI HAY UN ERROR
  // LO MANEJA
void BloodDatabase::searchAndDisplay() const {
  Console::clearConsole();
  displayProvinces();
  int provinceName = std::stoi(Console::getInformation("district"));

  Console::showInfoMessage("Ingrese la dirección (dejar en blanco para omitir): ");
  std::string addressFilter;
  addressFilter = Console::getInformation("address");

  Console::showInfoMessage("Ingrese el tipo de sangre (dejar en blanco para omitir): ");
  std::string bloodTypeFilter;
  bloodTypeFilter = Console::getInformation("bloodType");

  std::ifstream inFile(fileName);

  if (!inFile) {
    Console::showInfoMessage("Error al abrir el archivo para leer.");
    return;
  }

  std::vector<Donor> donors; // Vector para almacenar los donantes que coinciden ya estaba definido como atributo, error logico 
  std::string line;
  bool found = false;

  while (std::getline(inFile, line)) {
    try {
      Donor d = Donor::parseLine(line);

      bool match = d.getDistrict() == provinceName &&
                   (addressFilter.empty() ||
                    d.getAddress().find(addressFilter) != std::string::npos) &&
                   (bloodTypeFilter.empty() || d.getBloodType()  == bloodTypeFilter);

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
  Console::showInfoMessage(std::string("No se encontraron personas del departamento ") + getZoneName(provinceName));
  std::string message;
  if (!addressFilter.empty()) {
    message += " con dirección que contiene '" + addressFilter + "'";
  }
  if (!bloodTypeFilter.empty()) {
    message += " y tipo de sangre '" + bloodTypeFilter + "'";
  }
  Console::showInfoMessage(message);
} else {
  std::string message = std::string("Personas del departamento ") + getZoneName(provinceName);

  if (!addressFilter.empty()) {
    message += " con dirección que contiene '" + addressFilter + "'";
  }
  if (!bloodTypeFilter.empty()) {
    message += " y tipo de sangre '" + bloodTypeFilter + "'";
  }
  message += ":\n";

  for (const auto &d : donors) {
    message += "Nombre: " + d.getName() + "\n";
    message += "Dirección: " + d.getAddress() + "\n";
    message += "Departamento: " + getZoneName(d.getDistrict()) + "\n";
    message += "Tipo de sangre: " + d.getBloodType() + "\n";
    message += "Número de móvil: " + d.getNumber() + "\n\n";
  }

  Console::showInfoMessage(message);

}

  inFile.close();
  Console::waitForKeyPress();
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
    try
    {
    while (std::getline(inFile, line)) {
      try {
        Donor d = Donor::parseLine(line);} catch (const std::exception &e) { std::cerr << "Error procesando línea: " << line << std::endl;}
        Donor d = Donor::parseLine(line);
        if (d.getName() == donorName) {
          found = true;

          std::string message;
          message += "Nombre: " + d.getName() + "\n";
          message += "Dirección: " + d.getAddress() + "\n";
          message += "Tipo de sangre: " + d.getBloodType() + "\n";
          message += "Número de móvil: " + d.getNumber() + "\n\n";
          message += "¿Está seguro de que desea eliminar al donante? [s/n]: ";

          Console::showInfoMessage(message);


          char sureChoice;
          std::cin >> sureChoice;
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                          '\n'); // descartar cualquier entrada extra

          if (sureChoice == 's' || sureChoice == 'S') {
            continue;
          }
        }

        tempFile << d.getDonorId() << ",    " << d.getName() << ",    " << d.getAddress()
                << ",    " << d.getDistrict() << ",    " << d.getBloodType()  << ",    "
                << d.getNumber() << ",    " << d.getDate() << ",    " << d.getDonationAmount() << std::endl;
      }
    }
    catch(const std::exception& e)
    {
      std::cerr <<"error de : " << e.what() << '\n';
      return;

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
    Console::showInfoMessage("No se encontró ningún donante con el nombre " + donorName);

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

BloodDatabase::DonorsData BloodDatabase::readDataFromFileAndSaveStats() { // FUNCION QUE LEE EL ARCHIVO Y GENERA EL REPORTE
  DonorsData stats; // Estructura para almacenar los datos de donantes
  // Mapas para contar donantes por zona y tipo de sangre
  std::map<int, std::map<std::string, int>> donorsByZoneAndType;// mapa anidado para contar donantes por zona y tipo de sangre
  std::map<int, int> totalDonorsByZone; //Total de donantes por MUNICIPIO con key el codigo del municipio
  // LOS MAPS SON DICCIONRIOS QUE PERMITEN ALMACENAR DATOS DE FORMA ORDENADA Y ACCEDER A ELLOS RÁPIDAMENTE POR UNA CLAVE

  std::ifstream inFile(fileName);

  if (!inFile) {
    Console::showInfoMessage("Error al abrir el archivo para leer.");

    Console::waitForKeyPress();
    return stats;
  }
  
  
  std::string line; // Linea de donante
  int totalValidDonors = 0; // Contador de donantes con datos válidos
  int invalidLines = 0; // Contador de líneas con datos inválidos

  while (std::getline(inFile, line)) {
    if (line.empty()) continue;

    try {
      Donor d = Donor::parseLine(line);

      // Normalizar tipo de sangre
      std::string normalizedBloodType = normalizeBloodType(d.getBloodType() );

      // Solo contar donantes con datos válidos
      if (d.getDistrict() >= 1 && d.getDistrict() <= 10 && normalizedBloodType != "DESCONOCIDO") { // Aqui Deberia de contar la longitud de el arreglo de zonas ( pero como no hay se hace con codigo duro )
        donorsByZoneAndType[d.getDistrict()][normalizedBloodType]++;
        totalDonorsByZone[d.getDistrict()]++;
        totalValidDonors++;
      } else {
        invalidLines++;
      }
    } catch (const std::exception &e) {
      invalidLines++;
      continue;
    }
  }
  
  if (totalValidDonors == 0) {
    Console::showInfoMessage("No se encontraron donantes con datos válidos.");
    Console::waitForKeyPress();
    return stats;
  }


  std::cout << std::endl;

  inFile.close();
  stats.donorsByZoneAndType = donorsByZoneAndType;
  stats.totalDonorsByZone = totalDonorsByZone;
  return stats;
}
void BloodDatabase::report(BloodDatabase::DonorsData stats) {
  std::map<int, std::map<std::string, int>> donorsByZoneAndType = stats.donorsByZoneAndType;
  std::map<int, int> totalDonorsByZone = stats.totalDonorsByZone;

  // FUNCION QUE LEE EL ARCHIVO Y GENERA EL REPORTE
  // REPORTE DESDE AQUI
  Console::clearConsole();
  std::string message = "=== REPORTE DE DONANTES POR TIPO DE SANGRE Y ZONA ===\n";
  message += "======================================================\n";
  Console::showInfoMessage(message);

  // Tipos de sangre a reportar
  
  
  std::vector<std::string> bloodTypesVector = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
 

  // Reporte por zona
  for (int zone = 1; zone <= 10; zone++) {//zona 1 a 10 definido en codigo duro
    if (totalDonorsByZone.find(zone) != totalDonorsByZone.end()) {
      std::cout << "--- " << getZoneName(zone) << " ---" << std::endl;
      std::cout << "Total de donantes en esta zona: " << totalDonorsByZone[zone] << std::endl;

      for (const std::string& bloodType : bloodTypesVector) {
        int count = 0;//Contador de donantes por tipo de sangre en la zona actual
        if (donorsByZoneAndType[zone].find(bloodType) != donorsByZoneAndType[zone].end()) {
          count = donorsByZoneAndType[zone][bloodType];
        }

        double percentage = (totalDonorsByZone[zone] > 0) ? 
                           (static_cast<double>(count) / totalDonorsByZone[zone]) * 100.0 : 0.0;// Porcentaje de donantes de este tipo en la zona

        std::cout << "  " << bloodType << ": " << count << " donantes (" 
                  << std::fixed << std::setprecision(1) << percentage << "%)" << std::endl;
      }
      std::cout << std::endl;
    }
  }

  // Resumen nacional por tipo de sangre
  Console::showInfoMessage("=== RESUMEN NACIONAL POR TIPO DE SANGRE ===");

  std::map<std::string, int> nationalCounts;// Mapa para contar donantes por tipo de sangre a nivel nacional

  for (const auto& zone : donorsByZoneAndType) { // El auto configura el tipo de dato automáticamente
    for (const auto& bloodType : zone.second) {
      nationalCounts[bloodType.first] += bloodType.second;
    }
  }
  int totalValidDonors = 0;
  for (const auto& par : totalDonorsByZone) {
      totalValidDonors += par.second;
  }

  for (const std::string& bloodType : bloodTypesVector) {
    int count = nationalCounts[bloodType];
    double percentage = (totalValidDonors > 0) ? 
                       (static_cast<double>(count) / totalValidDonors) * 100.0 : 0.0;

    std::cout << bloodType << ": " << count << " donantes (" 
              << std::fixed << std::setprecision(1) << percentage << "% del total nacional)" << std::endl;
  }
  
  std::cout << std::endl;
 
  //Reporte del tipo de sangre mas comun en la poblacion
  Console::showInfoMessage("=== TIPO DE SANGRE MÁS COMÚN EN LA POBLACIÓN ===");
  std::string mostCommonBloodType;
  int highestCount = 0;
  for (const std::string& bloodType : bloodTypesVector) {
    int count = nationalCounts[bloodType];
    if (count > highestCount) {
      highestCount = count;
      mostCommonBloodType = bloodType;
    }
  }

  Console::showInfoMessage("Tipo de sangre más común: " + mostCommonBloodType + " (" + std::to_string(highestCount) + " donantes)");
  Console::waitForKeyPress();
}
std::vector<Donor> BloodDatabase::getAllDonors() {
    return donors;
}
