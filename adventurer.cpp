#include "adventurer.h"

Adventurer::Adventurer(int id, std::string name, std::string surname,
                       std::string role, int level, int reputation)
    : id(id),
      name(name),
      surname(surname),
      role(role),
      level(level),
      reputation(reputation) {
  calcRank();
}

int Adventurer::getReputation() const
{
    return reputation;
}

void Adventurer::setReputation(int reputation)
{
    this->reputation = reputation;
    calcRank();
}

void Adventurer::addReputation(int rep)
{
    reputation += rep;
    calcRank();
}

int Adventurer::getId() const
{
    return id;
}

std::string Adventurer::getRank() const
{
    return rank;
}

void Adventurer::calcRank() {
  if (reputation < RANK_THRESHOLD_ADVENTURER) {
    rank = "Novice";
  } else if (reputation < RANK_THRESHOLD_GUARDIAN) {
    rank = "Adventurer";
  } else if (reputation < RANK_THRESHOLD_VETERAN) {
    rank = "Guardian";
  } else if (reputation < RANK_THRESHOLD_HERO) {
    rank = "Veteran";
  } else if (reputation < RANK_THRESHOLD_RENOWNED_HERO) {
    rank = "Hero";
  } else if (reputation < RANK_THRESHOLD_LEGEND) {
    rank = "Renowned Hero";
  } else {
    rank = "Legend";
  }
}
