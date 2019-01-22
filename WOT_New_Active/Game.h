#ifndef GAME_H
#define GAME_H
#pragma once

#include "Tank.h"
#include "Tiger_II.h"
#include "T32.h"

#include "util.h"

#include <string>
#include <iostream>
#include <thread>
#include <ctime>
#include <math.h>
#include <regex>
#include <typeinfo>
#include <sstream>

class Game
{

protected:
	bool gameOver = false;
	bool gameStarted = false;
	bool commanding = false;
	bool notificationsExist = false;

	int numberOfTanks = 2;
	std::string listOfTanks[2];
	int playerTankChoiceNumber;
	int secondsIntoGame = 0;

	std::string userCommandLine;

	std::string userMoveCommand;
	std::string userFireCommand;
	std::string userTraverseCommand;

	std::string userMoveDirection;
	std::string userFireTarget;
	int userTraverseDegree;

public:
	Game();
	Tank createAiTank();
	void initialize1v1AiBattle(Tank* playerTank, Tank* aiTank);
	void doCommands(Tank& playerT, Tank& aiT);
	void takeCommands(Tank& playerT, Tank& aiT);

	bool getIsGameOver() { return this->gameOver; }
	bool getIsGameStarted() { return this->gameStarted; }
	bool getIsCommanding() { return this->commanding; }
	int getPlayerTankChoiceNumber();
	std::string* getArrayOfTanks();
	int getNumberOfTanks();

	void setIsGameOver(bool x) { this->gameOver = x; }
	void setIsGameStarted(bool x) { this->gameStarted = x; }
	void setIsCommanding(bool x) { this->commanding = x; }

	void setUserMoveDirection(std::string commandLine, Tank& playerT); // not a simple setter
	void setUserTraverseTarget(std::string commandLine, Tank& playerT);
	void setUserFireTarget(std::string commandLine, Tank& playerT);


	/* End of getters / setters */

	void listAllTanks();
	void initListOfTanks();
	void promptTankChoice();
	Tank assignTankFromChoice(int choiceNumber, bool isPlayerTank);
	void showCurrentTankStats(Tank& t);
	void showPossibleCommands(Tank& t);
	void processCommand(std::string userCommandLine, Tank& playerT);
	void printMap(int playerX, int playerY, int aiX, int aiY);
	void printActiveInfoForUserTank(Tank& playerT);
	void testForNotifications(Tank& playerT, Tank& aiT);
	void testForGameOver(Tank& playerT, Tank& aiT);

	void tutorial();

};
#endif