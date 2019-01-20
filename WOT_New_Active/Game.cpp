#include "Game.h"

Game::Game() {
	initListOfTanks();
}

// fills up the list of tanks array
void Game::initListOfTanks() {
	listOfTanks[0] = "1: Tiger II";
	listOfTanks[1] = "2: T32";
}

int Game::getPlayerTankChoiceNumber() { return this->playerTankChoiceNumber; }
std::string* Game::getArrayOfTanks() { return this->listOfTanks; }
int Game::getNumberOfTanks() { return this->numberOfTanks; }

/* End of getters and setters */

// prints out all available tanks
void Game::listAllTanks() {
	for (int i = 0; i < 2; i++) {
		std::cout << listOfTanks[i] << std::endl;
	}
}

// shows all tanks and takes in a user tank choice number called playerTankChoiceNumber
void Game::promptTankChoice() {

	std::string playerChoiceString;
	std::cout << "Hello! Pick your tank!" << std::endl;

	try {
		listAllTanks();
		std::cout << std::endl;
		std::cout << "Enter the number of the tank you want: ";
		std::cin >> playerChoiceString;
		std::system("cls");

		playerTankChoiceNumber = util::stringToInt(playerChoiceString);

		if (util::thisStringHasThisRegex(playerChoiceString, R"([a-z]+)")) {
			throw "Tank choice must be a number, no letter allowed";
		}
		else if (playerTankChoiceNumber > 2 || playerTankChoiceNumber < 1) {
			throw "Tank choice must be a valid number";
		}
	}
	catch (const char* e) {
		std::cout << "Error: " << e << std::endl;
		promptTankChoice();
	}

}

// assigns the player or ai's tank from their choice number
Tank Game::assignTankFromChoice(int choiceNumber, bool isPlayerTank) {
	if (choiceNumber == 1) {
		Tiger_II t(isPlayerTank);
		return t;
	}
	else if (choiceNumber == 2) {
		T32 t(isPlayerTank);
		return t;
	}
	else {
		Tiger_II t(isPlayerTank);
		return t;
	}
}


// shows stats of a tank given a pointer to the tank
void Game::showCurrentTankStats(Tank& t) {
	std::cout << t.getTankName() << std::endl;
	std::cout << "Health Points: " << t.getHealthPoints() << std::endl;
	std::cout << "Ammo Count: " << t.getAmmoCount() << std::endl;
	std::cout << "Current Heading: " << t.getHeadingAngle() << std::endl;
	std::cout << "Current speed: " << t.getCurrentSpeed() << std::endl;

}


// big part of the menu, shows possible user commands and what kind of format they need to use
void Game::showPossibleCommands(Tank& playerT) {
	std::cout << std::endl;
	std::cout << "What are your orders?" << std::endl;
	std::cout << "==================================" << std::endl;
	std::cout << std::endl;
	std::cout << "move [forward, backward] / hold position" << std::endl;
	std::cout << "turn [degrees] [left/right]" << std::endl;
	std::cout << "fire at [ ";

	std::vector<std::string> currentPossibleTargets = playerT.getPossibleTargets();

	for (int i = 0; i < currentPossibleTargets.size(); i++) {
		std::cout << currentPossibleTargets[i];
		if (i != currentPossibleTargets.size() - 1) {
			std::cout << ", ";
		}
		if (i == currentPossibleTargets.size() - 1) {
			std::cout << " ]";
		}
	}
	std::cout << std::endl;

}

// this is it's own thread. It is CONSTANTLY being checked for truth value
void Game::doCommands(Tank& playerT, Tank& aiT) {
	while (!gameOver) {
		while (gameStarted) {
			while (!commanding) {

				// assigns the direction the tank is moving and the distance to enemy
				playerT.assignDirectionPromptGiven(playerT.getHeadingAngle(), playerT.getHeadingToEnemy(aiT));


				// we also have to make sure they can't turn
				if (playerT.getTrackIsBroken() && playerT.getMoveDirection() != "") {

					playerT.setMoveDirection("");
					playerT.addNotification("TRACK IS BUSTED, CAN'T MOVE FOR" +
						std::to_string(playerT.getSecondsUntilMobile()) + " SECONDS");
				}
				//sets the turning prompts and properly changes the heading angle of the tank
				if (!playerT.getTrackIsBroken())
					playerT.oneSecOfTurning();

				playerT.oneSecOfMoving(aiT); // aiTank is passed so the playerTank can see where he is as to not run into him

				 // if the fireTarget is not nothing
				if (playerT.getFireTarget() != "") {
					playerT.fireAtTarget(aiT);
				}

				if (playerT.getSecondsUntilReloaded() > 0)
					playerT.setSecondsUntilReloaded(playerT.getSecondsUntilReloaded() - 1);
				if (playerT.getSecondsUntilReloaded() <= 0)
					playerT.setIsLoaded(true);

				if (playerT.getSecondsUntilMobile() > 0)
					playerT.setSecondsUntilMobile(playerT.getSecondsUntilMobile() - 1);

				if (playerT.getSecondsUntilMobile() <= 0) {
					playerT.setSecondsUntilMobile(0);
					playerT.setTrackIsBroken(false);
				}


				double x = playerT.getSecondsUntilReloaded();

				playerT.assignPossibleTargets(aiT);


				// This is now the ai tank section
				// =======================================================================================
				// =======================================================================================

				aiT.assignPossibleTargets(playerT);

				//If the track is broken
				bool xy = aiT.getTrackIsBroken();
				std::string movedir = aiT.getMoveDirection();

				if (aiT.getTrackIsBroken() && aiT.getMoveDirection() != "") {

					aiT.setMoveDirection("");
					aiT.addNotification("ENEMY TRACK IS BUSTED, THEY CAN'T MOVE FOR" +
						std::to_string(aiT.getSecondsUntilMobile()) + " SECONDS");
				}

				// every second we should set the aiTank heading to face the playerTank
				int degree = aiT.getHeadingToEnemy(playerT) - aiT.getHeadingAngle();
				if (abs(degree) > 180) {

					if (degree < 0)
						degree = (360 - abs(degree));
					else
						degree = (360 - abs(degree)) * (-1);
				}
				aiT.setTargetTraverseDegree(degree);

				// I also need to give the ai tank a move direction
				if (aiT.getXMetersOut() > 100 && !aiT.getTrackIsBroken()) {
					aiT.setMoveDirection("forward");
					aiT.setIsMoving(true);
				}
				else {
					aiT.setMoveDirection("");
				}

				// if the track isn't broken, move and turn
				if (!aiT.getTrackIsBroken()) {
					aiT.oneSecOfTurning();
					aiT.oneSecOfMoving(playerT);
				}

				// but before we can fire at anything, we have to give the ai tank a fire target

				// possible to make this dry?
				// if the ai tank's possible targets vector contains the rear, shoot the rear, else front, then sides
				if (util::vectorContains(aiT.getPossibleTargets(), "rear")) {
					aiT.setFireTarget("rear");
				}
				else if (util::vectorContains(aiT.getPossibleTargets(), "front")) {
					aiT.setFireTarget("front");
				}
				else if (util::vectorContains(aiT.getPossibleTargets(), "side")) {
					aiT.setFireTarget("side");
				}

				if (secondsIntoGame > 4) {

					int x = 2;
					// comment
				}
				bool z = aiT.getIsLoaded();

				// if the fireTarget is not nothing, then shoot
				if (aiT.getFireTarget() != "" && aiT.getXMetersOut() <= 500 && secondsIntoGame > 4 && aiT.getIsLoaded()) {

					aiT.fireAtTarget(playerT);
				}

				if (aiT.getSecondsUntilReloaded() > 0)
					aiT.setSecondsUntilReloaded(aiT.getSecondsUntilReloaded() - 1);
				if (aiT.getSecondsUntilReloaded() <= 0)
					aiT.setIsLoaded(true);

				// update the broken track every second

				if (aiT.getSecondsUntilMobile() > 0)
					aiT.setSecondsUntilMobile(aiT.getSecondsUntilMobile() - 1);

				if (aiT.getSecondsUntilMobile() <= 0) {
					aiT.setSecondsUntilMobile(0);
					aiT.setTrackIsBroken(false);
				}

				//=======================================================================================

				// prints all the info the user sees every second
				printActiveInfoForUserTank(playerT);
				printMap((int)playerT.getXPos(), (int)playerT.getYPos(), (int)aiT.getXPos(), (int)aiT.getYPos());

				testForNotifications(playerT, aiT);
				testForGameOver(playerT, aiT);

				if (notificationsExist) {

					if (this->gameOver)
						exit(0);
				}

				std::this_thread::sleep_for(std::chrono::seconds{ 1 }); // sleep for one second so the game runs in real time

				secondsIntoGame++;

				if (!commanding) {
					std::system("cls");
				}
			}
		}
	}
}

// this is it's own thread. It is CONSTANTLY being checked for truth value
void Game::takeCommands(Tank& playerT, Tank& aiT) {
	while (!gameOver) {
		while (gameStarted) {
			if (commanding) {

				if (this->gameOver == true) { break; }

				std::cin.get(); // takes in any leftover return charachter not picked up by cin				

								// list all possible commands
				showCurrentTankStats(playerT);
				showPossibleCommands(playerT);

				// take user input

				std::getline(std::cin, userCommandLine);
				std::system("cls"); // clears the screen

									// make sure the userCommandLine is all lowercase right off the bat
				userCommandLine = util::thisToLowerCase(userCommandLine);

				// process user command
				processCommand(userCommandLine, playerT);

				// set commanding to false to get back to the game
				commanding = false;

				// for every command a user wants to do, it will be done every second until ordered to stop or reaches stop point
			}
		}
	}
}

// sets user command strings and calles other methods using those new command strings
void Game::processCommand(std::string userCommandLine, Tank& playerT) {

	// if the userCommand line has the word move or hold
	if (
		util::thisStringHasThisRegex(userCommandLine, R"(move)")
		||
		util::thisStringHasThisRegex(userCommandLine, R"(hold)")

		) {

		userMoveCommand = userCommandLine;
		// then set the userMoveDirection given the userCommandLine
		setUserMoveDirection(userCommandLine, playerT); // not a simple setter

	}
	// if the usercommand line has the word fire
	else if (util::thisStringHasThisRegex(userCommandLine, R"(fire)")) {
		userFireCommand = userCommandLine;
		setUserFireTarget(userFireCommand, playerT);
	}
	// if the usercommand line has the word traverse
	else if (util::thisStringHasThisRegex(userCommandLine, R"(turn)")) {
		userTraverseCommand = userCommandLine;
		setUserTraverseTarget(userCommandLine, playerT);
	}

}

// based move command line, sets the tanks's move direction variable to be used by oneSecOfMoving
void Game::setUserMoveDirection(std::string commandLine, Tank& playerT) {
	// if the command line has the word forward and not the word backward
	if (util::thisStringHasThisRegex(commandLine, R"(forward)")) {
		playerT.setMoveDirection("forward");
		playerT.setCurrentSpeed(playerT.getTopSpeed());
	}
	else if (util::thisStringHasThisRegex(commandLine, R"(backward)")) {
		playerT.setMoveDirection("backward");
		playerT.setCurrentSpeed(playerT.getTopSpeed());

	}
	else if (util::thisStringHasThisRegex(commandLine, R"(hold position)")) {
		playerT.setMoveDirection("");
		playerT.setCurrentSpeed(0);

	}
}

// based on the commandLine, sets the proper target traverse degree stored in the tank class
void Game::setUserTraverseTarget(std::string commandLine, Tank& playerT) {
	std::string degreeSubstring;
	degreeSubstring = util::getRegexFromString(R"(\d+)", commandLine);

	std::string direction;
	direction = util::getRegexFromString(R"(left|right)", commandLine);

	int degree = util::stringToInt(degreeSubstring);

	if (direction == "right") {
		degree = -1 * degree;
	}

	playerT.setTargetTraverseDegree(degree);

}


// this is not dry, could loop through a vector of at all possible targets
// if the user command line has any of the target names, set the tank's fire target to that target
void Game::setUserFireTarget(std::string commandLine, Tank& playerT) {
	if (util::thisStringHasThisRegex(commandLine, R"(turret)"))
		playerT.setFireTarget("turret");
	else if (util::thisStringHasThisRegex(commandLine, R"(front)"))
		playerT.setFireTarget("front");
	else if (util::thisStringHasThisRegex(commandLine, R"(side)"))
		playerT.setFireTarget("side");
	else if (util::thisStringHasThisRegex(commandLine, R"(rear)"))
		playerT.setFireTarget("rear");
	else if (util::thisStringHasThisRegex(commandLine, R"(track)"))
		playerT.setFireTarget("track");

}

// returns a tank, randomly chosen to be the tank of the AI
Tank Game::createAiTank() {

	// makes a radom number from 1 to however many tanks are available
	int aiTankChoice = util::randomNumXtoY(1, numberOfTanks);

	// if the initial aiTankChoice was already the same as the player's tank choice, reasign it until it's different
	while (aiTankChoice == playerTankChoiceNumber) {
		aiTankChoice = util::randomNumXtoY(1, numberOfTanks);
	}
	// create the actual aiTank itself so we can return it
	Tank aiTank = assignTankFromChoice(aiTankChoice, false);

	return aiTank;
}

// I dont' want to just initialize copies of the tanks, so I need to use pointers
void Game::initialize1v1AiBattle(Tank *playerTank, Tank *aiTank) {

	this->gameStarted = true;

	// In the future, this could also be where I adjust tank stats regarding crew upgrades etc.
	// Set the poistion on the x, y grid for each tank

	// defaults for non-testing
	playerTank->setXYPos(500, 250);
	aiTank->setXYPos(500, 750);

	// Set the headingAngle and sideFacingAngle for each tank
	playerTank->setHeadingAngle(90);
	aiTank->setHeadingAngle(270);
}

void Game::printMap(int playerX, int playerY, int aiX, int aiY) {
	const double chunk = 47.619047619;
	double yLowerBound;
	double yUpperBound;
	double xLowerBound;
	double xUpperBound;
	for (int i = 0; i < 23; i++) {

		if (i == 1) {
			yUpperBound = 1000;
		}
		else {
			yUpperBound = 1000 - (chunk * (i - 1));
		}
		yLowerBound = yUpperBound - chunk;


		for (int j = 0; j < 23; j++) {

			if (j == 1) {
				xLowerBound = 0;
			}
			else {
				xLowerBound = (j - 1) * chunk;
			}
			xUpperBound = j * chunk;


			if (i == 0 || j == 0) {
				std::cout << std::setw(2) << "=";
			}
			else if (i == 22 || j == 22) {
				std::cout << std::setw(2) << "=";
			}

			else if ((aiY >= yLowerBound && aiY < yUpperBound) && (aiX >= xLowerBound && aiX < xUpperBound)) {
				std::cout << std::setw(2) << "!";
			}
			else if ((playerY >= yLowerBound && playerY < yUpperBound) && (playerX >= xLowerBound && playerX < xUpperBound)) {
				std::cout << std::setw(2) << "*";
			}
			else {
				std::cout << std::setw(2) << " ";
			}
		}
		std::cout << std::endl; // needed
	}
}

// continue with the other info displayed that is normally disperced all around my code
// remember when you start to make the ai tank do stuff, the things printed out here will be the updated values
// after the PLAYER TANK methods are ran. So you can't have the ai tank do stuff after you every second. He has to go first
void Game::printActiveInfoForUserTank(Tank& playerT) {

	std::cout << playerT.getDirectionPrompt() << std::endl; // prints direction to enemy tank
	std::cout << playerT.getXMetersOut() << " meters out!" << std::endl;
	std::cout << "We Are " + playerT.getTurningPrompt() << std::endl;
	std::cout << "We Are " + playerT.getMovingPrompt() << std::endl; // prints how userTank is moving
	if (playerT.getSecondsUntilReloaded() > 0) {
		std::cout << "SECONDS UNTIL RELOADED: " + std::to_string((int)ceil(playerT.getSecondsUntilReloaded())) << std::endl;
	}
	else {
		std::cout << std::endl;
	}

}

void Game::testForNotifications(Tank& playerT, Tank& aiT) {
	if (playerT.getNotifications().size() != 0 || aiT.getNotifications().size() != 0) {
		notificationsExist = true;
		//commanding = true;
		//commanding = true;
	}
}



void Game::testForGameOver(Tank& playerT, Tank& aiT) {

	// if any of the tanks are dead, the game is over
	if (playerT.getHealthPoints() <= 0 || aiT.getHealthPoints() <= 0) {

		std::string status;

		if (playerT.getHealthPoints() <= 0)
			status = "LOST";
		else
			status = "WON";

		playerT.addNotification("GAME OVER, YOU " + status);
		this->gameOver = true;
		this->commanding = true;
		this->gameStarted = false;
	}
}


