
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
  
public:
  struct DonorsData { // Estructura para almacenar datos de donantes por zona y tipo de sangre Para poder usarlos luego y añadir informacion estadistica facilemente
    std::map<int, std::map<std::string, int>> donorsByZoneAndType;
    std::map<int, int> totalDonorsByZone;
  };
  static std::vector<Donor> getAllDonors();
  

  std::string getZoneName(int zoneCode) const;

  DonorsData readDataFromFileAndSaveStats();

  void report(DonorsData stats);
  void getDonorDetails();

  void writeDataToFile();

  void searchAndDisplay() const;

  void loadDonorsFromFile() const;

  void deleteDonor(const std::string &donorName);

  

private:
  const std::string fileName = "data.txt";
  static std::vector<Donor> donors;
  std::string normalizeBloodType(const std::string& bloodType) const;
  
  static void displayProvinces();

  

}; // BloodDatabase Cumple el Principio de open/closed? Creo que si dado que se
   // puede agregar nuevas funcionalidades sin modificar el codigo existente.

#endif // BLOODDATABASE_H
