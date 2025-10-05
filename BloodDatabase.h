
#ifndef BLOODDATABASE_H
#define BLOODDATABASE_H

#include "Donor.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>

class BloodDatabase {
private:
  const std::string fileName = "data.txt";
  static std::vector<Donor> donors;

  static void displayProvinces();

  

public:
  struct DonorsData { // Estructura para almacenar datos de donantes por zona y tipo de sangre Para poder usarlos luego y añadir informacion estadistica facilemente
    std::map<int, std::map<std::string, int>> donorsByZoneAndType;
    std::map<int, int> totalDonorsByZone;
  };
  static std::vector<Donor> getAllDonors();
  static void clearConsole();

  static void waitForKeyPress();

  static int getValidatedInput(const std::string &prompt, const std::string &infoType);

  static std::string getValidatedStringInput(const std::string &prompt, const std::string &infoType);

  static std::string getInformation(const std::string infoRequired);

  std::string getZoneName(int zoneCode) const;
  
  std::string normalizeBloodType(const std::string& bloodType) const;

  DonorsData readDataFromFileAndSaveStats();

  void report(DonorsData stats);
  void getDonorDetails();

  void writeDataToFile();

  void searchAndDisplay() const;

  void loadDonorsFromFile() const;

  void deleteDonor(const std::string &donorName);

  

}; // BloodDatabase Cumple el Principio de open/closed? Creo que si dado que se
   // puede agregar nuevas funcionalidades sin modificar el codigo existente.

#endif // BLOODDATABASE_H
