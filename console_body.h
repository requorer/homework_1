#ifndef CONSOLE_BODY_H_
#define CONSOLE_BODY_H_

#include <iostream>
#include <string>

#include "guild_base.h"
#include "adventurer.h"

void mainMenuScreen();

void registerAdventurer(GuildBase& database);

void printAdventurer(const Adventurer& adventurer);

void printAll(const GuildBase& guild);

void searchMenu(const GuildBase& database);

void removeAdventurer(GuildBase& database);

void manageReputation(GuildBase& database);

void editAdventurerData(GuildBase& database);

void game();

#endif  // CONSOLE_BODY_H_