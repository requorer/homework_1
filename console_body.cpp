#include "console_body.h"

int score = 0;

static int readInt() {
  int value = 0;
  while (true) {
    if (std::cin >> value) {
      std::cin.ignore(10000, '\n');
      return value;
    }

    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << "Invalid number, try again.\n";
  }
}

void mainMenuScreen() {
  std::cout << ""
            << "\n|****************************|"
            << "\n|                            |"
            << "\n|                            |"
            << "\n|       Adventurers Guild    |"
            << "\n|            Archive         |"
            << "\n|                            |"
            << "\n|****************************|"
            << "\n";

  std::cout << "\n1. Register new member"
   << "\n2. View all records"     
   << "\n3. Search for adventurer" 
   << "\n4. Exclude from guild"     
   << "\n5. Manage reputation"     
   << "\n6. Edit member data"       
   << "\n0. Exit\n";
  std::cout << "\nChoose option: ";
};

void registerAdventurer(GuildBase& database) {
  std::string name, surname, role;
  int level, reputation;

  std::cout << "\n=== Register new member ===\n";
  std::cout << "Name: ";
  std::cin >> name;
  std::cout << "Surname: ";
  std::cin >> surname;
  std::cout << "Role: ";
  std::cin >> role;
  std::cout << "Level: ";
  level = readInt();
  std::cout << "Reputation: ";
  reputation = readInt();
  database.addAdventurer(name, surname, role, level, reputation);
  
}

void printAdventurer(const Adventurer& adventurer) {
  std::cout << "| ID: " << adventurer.getId() 
          << " | Name: " << adventurer.name
          << " | Surname: " << adventurer.surname
          << " | Role: " << adventurer.role
          << " | Level: " << adventurer.level
          << " | Reputation: " << adventurer.getReputation() << " |" << std::endl
          << " | Rank: " << adventurer.getRank() << " |" << std::endl;
}

void printAll(const GuildBase& guild) {
  std::cout << "\n=== All adventurers ===\n";
  const auto& adventurers = guild.getAllAdventurers();
  for (const auto& adventurer : adventurers) {
    printAdventurer(adventurer);
  }
}

void searchMenu(const GuildBase& database) {
  int input = 0;
  std::vector<Adventurer> found;

  std::cout << "\n=== Search Avanturers ===\n"
            << "\n1. by ID"
            << "\n2. by Name"
            << "\n3. by Surname"
            << "\n4. by Role"
            << "\n5. by Level"
            << "\n6. by Reputation"
            << "\n7. by Rank"
            << "\nEnter: ";
  std::cin >> input;

  switch (input) {
    case 1:{
      int id = 0;
      std::cout << "Enter ID: ";
      id=readInt();
      found = database.findById(id);
      for (const auto& adventurer : found) {
        printAdventurer(adventurer);
      }

      break;
    }
    case 2:{
      std::string name;
      std::cout << "Enter name: ";
      std::cin >> name;
      found = database.findByName(name);
      for (const auto& adventurer : found) {
        printAdventurer(adventurer);
      }

      break;
    }
    case 3:{
      std::string surname;
      std::cout << "Enter surname: ";
      std::cin >> surname;
      found = database.findBySurname(surname);
      for (const auto& adventurer : found) {
        printAdventurer(adventurer);
      }
      break;
    }
    case 4:{
      std::string role;
      std::cout << "Enter role: ";
      std::cin >> role;
      found = database.findByRole(role);
      for (const auto& adventurer : found) {
        printAdventurer(adventurer);
      }
      break;
    }
    case 5:{
      int level = 0;
      std::cout << "Enter level: ";
      level = readInt();
      found = database.findByLevel(level);
      for (const auto& adventurer : found) {
        printAdventurer(adventurer);
      }
      break;
    }
    case 6:{
      int reputation = 0;
      std::cout << "Enter reputation: ";
      reputation = readInt();
      found = database.findByReputation(reputation);
      for (const auto& adventurer : found) {
        printAdventurer(adventurer);
      }
      break;
    }
    case 7:{
      std::string rank;
      std::cout << "Enter rank: ";
      std::cin >> rank;
      found = database.findByRank(rank);
      for (const auto& adventurer : found) {
        printAdventurer(adventurer);
      }
      break;
    }
    default:
      break;
  }
}

void removeAdventurer(GuildBase& database) {
  int id;
  std::cout << "\nEnter ID of adventurer to remove: ";
  std::cin >> id;
  if (database.removeAdventurer(id)) {
    std::cout << "Adventurer with ID " << id << " removed successfully.\n";
  } else {
    std::cout << "Adventurer with ID " << id << " not found.\n";
  }
}

void manageReputation(GuildBase& database) {
  int id, rep;
  std::cout << "\nEnter ID of adventurer to manage reputation: ";
  id= readInt();

  std::cout << "Enter reputation points to add: ";
  rep = readInt();
  if (database.addReputation(id, rep)) {
    std::cout << "Reputation updated successfully.\n";
  } else {
    std::cout << "Adventurer with ID " << id << " not found.\n";
  }




}

void editAdventurerData(GuildBase& database) {
  int id;
  std::cout << "\nEnter ID of adventurer to edit: ";
  id = readInt();

  auto adventurers = database.findById(id);
  if (!adventurers.empty()) {
    Adventurer adventurer = adventurers[0];
    std::cout << "Editing adventurer with ID " << id << ":\n";
    std::cout << "Current name: " << adventurer.name << "\nNew name: ";
    std::cin >> adventurer.name;
    std::cout << "Current surname: " << adventurer.surname << "\nNew surname: ";
    std::cin >> adventurer.surname;
    std::cout << "Current role: " << adventurer.role << "\nNew role: ";
    std::cin >> adventurer.role;
    std::cout << "Current level: " << adventurer.level << "\n";
    std::cout << "New level: ";
    adventurer.level = readInt();
    std::cout << "Current reputation: " << adventurer.getReputation() << "\n";
    std::cout << "New reputation: ";
    int new_rep = readInt();
    adventurer.setReputation(new_rep);

    if (database.updateAdventurer(id, adventurer.name, adventurer.surname,
                                  adventurer.role, adventurer.level,
                                  adventurer.getReputation())) {
      std::cout << "Adventurer data updated successfully.\n";
    } else {
      std::cout << "Failed to update adventurer data.\n";
    }
  } else {
    std::cout << "Adventurer with ID " << id << " not found.\n";
  }
}

void game() {
  GuildBase database;
  database.readData();

  bool exit_flag = false;

  int input = 0;

  while (!exit_flag) {
    mainMenuScreen();

    while (true) {
      std::cin >> input;
      if (input >= MAIN_MENU_FIRST_POSSIBLE_CHOICE &&
          input <= MAIN_MENU_LAST_POSSIBLE_CHOICE) {
        break;
      } else {
        std::cin.clear();
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "|Invalid input, try again\n|";
      }
    }
    system("cls");

    switch (input) {
      case 0:
      if(database.saveData()) {
          std::cout << "Data saved successfully.\n";
        } else {
          std::cout << "Failed to save data.\n";
        }
        exit_flag = true;
        break;
      case 1:
        registerAdventurer(database);
        break;
      case 2:
        printAll(database);
        break;
      case 3:
        searchMenu(database);
        break;
      case 4:
        removeAdventurer(database);
        break;
      case 5:
        manageReputation(database);
        break;
      case 6:
        editAdventurerData(database);
        break;
      default:
        break;
    }

    system("pause");
    system("cls");
  }
};