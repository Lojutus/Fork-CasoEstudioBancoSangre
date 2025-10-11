#ifndef DONOR_H
#define DONOR_H

#include <string>
#include <vector>
class Donor {
public: 
  //Seters y Getters
  int getDonorId() const { return donorId; }
  void setDonorId(int id) { donorId = id; }

  std::string getName() const { return name; }
  void setName(const std::string &n) { name = n; }

  std::string getAddress() const { return address; }
  void setAddress(const std::string &addr) { address = addr; }

  int getDistrict() const { return district; }
  void setDistrict(int dist) { district = dist; }

  std::string getBloodType() const { return bloodType; }
  void setBloodType(const std::string &bt) { bloodType = bt; }

  std::string getNumber() const { return number; }
  void setNumber(const std::string &num) { number = num; }

  std::string getDate() const { return date; }
  void setDate(const std::string &d) { date = d; }
  
  int getDonationAmount() const { return donationAmount; }
  void setDonationAmount(int amount) { donationAmount = amount; }

  

  void donorDetails() const;
  std::string getItemsDonorInfo(const std::string& item) const;

  static Donor parseLine(const std::string &line);

private:
  int donorId, district, donationAmount;
  std::string name, address, number, bloodType, date;
  std::vector<std::string> infoElementsDonorString = {"name", "address", "number", "bloodType","date"};
  std::vector<std::string> infoElementsDonorInt = {"donorId",  "district", "donationAmount" };
  static std::string trim(const std::string &str);
};

#endif // DONOR_H

