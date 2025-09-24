#ifndef DONOR_H
#define DONOR_H

#include <string>
#include <vector>
class Donor {
public: // FALLO CRITICO DE SEGURIDAD: Se debe evitar el uso de miembros
        // publicos para los atributos de una clase. debe ser privado. No se
        // usan getters y setters. Se debe usar el principio de encapsulamiento.
  int donorId, district;
  std::string name, address, number, bloodType, date, donationAmount;

  void donorDetails() const;
  std::string getItemsDonorInfo(const std::string& item) const;

  static Donor parseLine(const std::string &line);

private:
  std::vector<std::string> infoElementsDonorString = {
       "name", "address", "number", "bloodType","date"};
  std::vector<std::string> infoElementsDonorInt = {
  "donorId",  "district", "donationAmount" };
  static std::string trim(const std::string &str);
};

#endif // DONOR_H

