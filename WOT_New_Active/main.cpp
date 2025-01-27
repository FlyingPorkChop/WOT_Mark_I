
#include "util.h"
#include "Game.h"
#include <thread>

/* Goals board

NEXT UP
- Make the targeting system


BACKBURNER
- Implement text to speech


*/

int main() // this has been a close call --> need to look more into that redit post
{
	Game game;
	std::string userInput;

	game.tutorial();

	// show the user all the tanks there are and let them choose a tank
	game.promptTankChoice();

	// create the physical playerTank from their choice
	Tank playerTank = game.assignTankFromChoice(game.getPlayerTankChoiceNumber(), true); // any way to rewrite this?

	// create a random tank ai from the leftover tanks the player did not choose (could also change to let them be the same)
	Tank aiTank = game.createAiTank();

	// initialize the tank battle, don't begin just yet
	game.initialize1v1AiBattle(&playerTank, &aiTank);
	game.setIsCommanding(true); // we want commanding to be true at the very start of the game

								// I need to pass both my tank instances into doCommandsForOneSec thread, otherwise, what is the thread 
								// going to work with?
	std::thread doCommandsForOneSec(&Game::doCommands, std::ref(game), std::ref(playerTank), std::ref(aiTank));

	std::thread takeUserCommads(&Game::takeCommands, std::ref(game), std::ref(playerTank), std::ref(aiTank));


	// while the game isn't over, and the user isn't commanding, we always give the user the possibility to enter "c" and start commanding
	while (!game.getIsGameOver()) {
		while (!game.getIsCommanding()) {
			std::cin >> userInput;
			if (userInput.find("c") != std::string::npos) {
				game.setIsCommanding(true);
			}
		}

	}

	doCommandsForOneSec.join(); // this waits for the joined thread to complete before moving on with main
	takeUserCommads.join(); // same
	system("pause");
	return 0;
}