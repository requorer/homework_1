#include "guild_base.h"
#include "constants.h"
#include <fstream>
#include <sstream>

std::vector<Adventurer> GuildBase::readData() {
	std::ifstream input_file(filename);
	
	if (!input_file.is_open()) {
		return std::vector<Adventurer>();
	}
	
	std::string line;
	int max_id = 0;
	
	while (std::getline(input_file, line)) {
		if (line.empty()) continue;
		
		std::stringstream ss(line);
		std::string token;
		
		int id, level, reputation;
		std::string name, surname, role;
		
		// Parsing: id;name;surname;role;level;reputation
		if (std::getline(ss, token, ';')) id = std::stoi(token);
		if (std::getline(ss, name, ';'));
		if (std::getline(ss, surname, ';'));
		if (std::getline(ss, role, ';'));
		if (std::getline(ss, token, ';')) level = std::stoi(token);
		if (std::getline(ss, token, ';')) reputation = std::stoi(token);
		
		adventurers.emplace_back(id, name, surname, role, level, reputation);
		if (id >= max_id) max_id = id;
	}
	
	id_counter = max_id + 1;
	input_file.close();
	
	return adventurers;
}

bool GuildBase::saveData()
{
	std::ofstream output_file(filename);
	
	if (!output_file.is_open()) {
		return false;
	}
	
	for (const auto& adventurer : adventurers) {
		output_file << adventurer.getId() << ";"
	           << adventurer.name << ";"
	           << adventurer.surname << ";"
	           << adventurer.role << ";"
	           << adventurer.level << ";"
	           << adventurer.getReputation() << "\n";
	}
	
	output_file.close();
	return true;
}

void GuildBase::addAdventurer(const std::string& name, const std::string& surname,
							   const std::string& role, int level, int reputation)
{
	Adventurer new_adventurer(id_counter++, name, surname, role, level, reputation);
	adventurers.push_back(new_adventurer);

}

bool GuildBase::removeAdventurer(int id)
{
	if (adventurers.empty()) {
		return false;
	}
	
	for (int i = 0; i < adventurers.size(); ++i) {
		if (adventurers[i].getId() == id) {
			adventurers.erase(adventurers.begin() + i);
			return true;
		}
	}
	
	return false;
}

bool GuildBase::updateAdventurer(int id, const std::string& name,
                                  const std::string& surname,
                                  const std::string& role, int level,
                                  int reputation)
{
	for (int i = 0; i < adventurers.size(); ++i) {
		if (adventurers[i].getId() == id) {
			adventurers[i].name = name;
			adventurers[i].surname = surname;
			adventurers[i].role = role;
			adventurers[i].level = level;
			adventurers[i].setReputation(reputation);
			return true;
		}
	}

	return false;
}

bool GuildBase::addReputation(int id, int reputation)
{
	for (int i = 0; i < adventurers.size(); ++i) {
		if (adventurers[i].getId() == id) {
			adventurers[i].addReputation(reputation);
			return true;
		}
	}

	return false;
}

std::vector<Adventurer> GuildBase::findById(int id) const
{
	return findBy([id](const Adventurer& adventurer) {
		return adventurer.getId() == id;
	});
}

std::vector<Adventurer> GuildBase::findByName(std::string name) const
{
		return findBy([name](const Adventurer& adventurer) {
			return adventurer.name == name;
		});
}

std::vector<Adventurer> GuildBase::findBySurname(std::string surname) const
{
		return findBy([surname](const Adventurer& adventurer) {
			return adventurer.surname == surname;
		});
}

std::vector<Adventurer> GuildBase::findByRank(std::string rank) const
{
		return findBy([rank](const Adventurer& adventurer) {
			return adventurer.getRank() == rank;
		});
}

std::vector<Adventurer> GuildBase::findByLevel(int level) const
{
	return findBy([level](const Adventurer& adventurer) {
		return adventurer.level == level;
	});
}

std::vector<Adventurer> GuildBase::findByRole(std::string role) const
{
	return findBy([role](const Adventurer& adventurer) {
		return adventurer.role == role;
	});
}

std::vector<Adventurer> GuildBase::findByReputation(int reputation) const
{
	return findBy([reputation](const Adventurer& adventurer) {
		return adventurer.getReputation() == reputation;
	});
}

template<typename Predicate>
std::vector<Adventurer> GuildBase::findBy(Predicate predicate) const {
  std::vector<Adventurer> found;

  for (const auto& adventurer : adventurers) {
    if (predicate(adventurer)) {
      found.push_back(adventurer);
    }
  }

  return found;
}

const std::vector<Adventurer>& GuildBase::getAllAdventurers() const {
	return adventurers;
}