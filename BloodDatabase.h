
#ifndef BLOODDATABASE_H
#define BLOODDATABASE_H

#include "Donor.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class BloodDatabase {
private:
  const std::string fileName = "data.txt";
  std::vector<Donor> donors;

  static void displayProvinces();

public:
  static void clearConsole();

  static void waitForKeyPress();

  static int getValidatedInput(const std::string &prompt, const std::string &infoType);

  static std::string getValidatedStringInput(const std::string &prompt, const std::string &infoType);

  static std::string getInformation(const std::string infoRequired);

  std::string getZoneName(int zoneCode) const;
  
  std::string normalizeBloodType(const std::string& bloodType) const;
  
  void readDataFromFileAndSave();

  void getDonorDetails();

  void writeDataToFile();

  void searchAndDisplay() const;

  void deleteDonor(const std::string &donorName);

  

}; // BloodDatabase Cumple el Principio de open/closed? Creo que si dado que se
   // puede agregar nuevas funcionalidades sin modificar el codigo existente.

#endif // BLOODDATABASE_H
