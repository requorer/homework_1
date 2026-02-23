#ifndef GUILD_BASE_H_
#define GUILD_BASE_H_

#include "adventurer.h"
#include "fstream"
#include "vector"

class GuildBase {
  std::vector<Adventurer> adventurers;
  std::string filename = "adventurers_data.txt";
  int id_counter = 1;

 public:
 GuildBase() {}
 GuildBase(const std::string& filename) : filename(filename) {}

  std::vector<Adventurer> readData();
  bool saveData();

  void printAll();

  void addAdventurer(const std::string& name, const std::string& surname,
                      const std::string& role, int level, int reputation);
  bool removeAdventurer(int id);
  bool updateAdventurer(int id, const std::string& name, const std::string& surname,
                         const std::string& role, int level, int reputation);
  bool addReputation(int id, int reputation);

  std::vector<Adventurer> findById(int id) const;
  std::vector<Adventurer> findByName(std::string name) const;
  std::vector<Adventurer> findBySurname(std::string surname) const;
  std::vector<Adventurer> findByRank(std::string rank) const;
  std::vector<Adventurer> findByLevel(int level) const;
  std::vector<Adventurer> findByRole(std::string role) const;
  std::vector<Adventurer> findByReputation(int reputation) const;
  const std::vector<Adventurer>& getAllAdventurers() const;
  
  private:
  template<typename Predicate>
  std::vector<Adventurer> findBy(Predicate predicate) const;
};

#endif  // GUILD_BASE_H_
