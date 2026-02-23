#ifndef ADVENTURER_H_
#define ADVENTURER_H_

#include <iostream>
#include <random>
#include <string>

#include "constants.h"

class Adventurer {
 public:
  std::string name;
  std::string surname;
  std::string role;
  int level;

  Adventurer(int id, std::string name, std::string surname, std::string role,
             int level, int reputation);

  int getReputation() const;
  void setReputation(int reputation);
  void addReputation(int rep);

  int getId() const;

  std::string getRank() const;

 private:
  int id;
  int reputation;
  std::string rank;
  void calcRank();
};

#endif  // ADVENTURER_H_
