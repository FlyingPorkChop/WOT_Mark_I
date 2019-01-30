
#include "Tank.h"
#include "util.h"

// util was here

Tank::Tank(bool isPlayerTank, std::string name, int damage, int pen, int mth) // my question lingers; is there another way to initialize const variables?
	:
	ISPLAYERTANK(isPlayerTank),
	TANK_NAME(name),
	DAMAGE(damage),
	PENETRATION(pen), // I probably shouldn't have pen as a constant. What if I want to use APCR or HEAT?
	MAX_TRACK_HEALTH(mth)
{

}

// Getters of constant vars
bool Tank::getIsPlayerTank() { return this->ISPLAYERTANK; }
std::string Tank::getTankName() { return this->TANK_NAME; }
int Tank::getDamage() { return this->DAMAGE; }
int Tank::getPenetration() { return this->PENETRATION; }

// Getter of changeable vars
double Tank::getReloadTime() { return this->reloadTime; }
double Tank::getAimTime() { return this->aimTime; }
int Tank::getAmmoCount() { return this->ammoCount; }
int Tank::getTopSpeed() { return this->topSpeed; }
double Tank::getStillDispersion() { return this->stillDispersion; }
double Tank::getMovingDispersion() { return this->movingDispersion; }
double Tank::getTraverseAnglesPerSec() { return this->traverseAnglesPerSec; }
int Tank::getEUpperHullArmor() { return this->eUpperHullArmor; }
int Tank::getELowerPlateArmor() { return this->eLowerPlateArmor; }
int Tank::getESideArmor() { return this->eSideArmor; }

int Tank::getArmorOf(std::string str) { return this->armorOf[str]; }

int Tank::getHealthPoints() { return this->healthPoints; }
int Tank::getTrackHealth() { return this->trackHealth; }
int Tank::getMaxTrackHealth() { return this->MAX_TRACK_HEALTH; }
int Tank::getViewRange() { return this->viewRange; }

double Tank::getHeadingAngle() { return this->headingAngle; }
//int Tank::getSideFacingAngle() { return this->sideFacingAngle; }

double Tank::getXPos() { return this->xPos; }
double Tank::getYPos() { return this->yPos; }

bool Tank::getIsLoaded() { return this->isLoaded; }
double Tank::getSecondsUntilReloaded() { return this->secondsUntilReloaded; }
bool Tank::getIsMoving() { return this->isMoving; }
bool Tank::getIsSpoted() { return this->isSpoted; }
bool Tank::getTrackIsBroken() { return this->trackBroken; }
int Tank::getSecondsUntilMobile() { return this->secondsUntilMobile; }

std::string Tank::getMoveDirection() { return this->moveDirection; }

int Tank::getCurrentSpeed() { return this->currentSpeed; }
double Tank::getTargetTraverseDegree() { return this->targetTraverseDegree; }
std::string Tank::getDirectionPrompt() { return this->directionPrompt; }
int Tank::getXMetersOut() { return this->xMetersOut; }
std::string Tank::getMovingPrompt() { return this->movingPrompt; }
std::string Tank::getTurningPrompt() { return this->turningPrompt; }
std::vector<std::string>& Tank::getPossibleTargets() { return this->possibleTargets; }
std::vector<std::string>& Tank::getNotifications() { return this->notifications; }
std::string Tank::getFireTarget() { return this->fireTarget; }

// Start setters ===========================================================================

void Tank::setReloadTime(double newReloadTime) { this->reloadTime = newReloadTime; }
void Tank::setAimTime(double newAimTime) { this->aimTime = newAimTime; }
void Tank::setAmmoCount(int newAmmoCount) { this->ammoCount = newAmmoCount; }
void Tank::setTopSpeed(int newTopSpeed) { this->topSpeed = newTopSpeed; }
void Tank::setStillDispersion(double x) { this->stillDispersion = x; }
void Tank::setMovingDispersion(double x) { this->movingDispersion = x; }
void Tank::setTraverseAnglesPerSec(double newTAPS) { this->traverseAnglesPerSec = newTAPS; }
void Tank::setEUpperHullArmor(int newEUHA) { this->eUpperHullArmor = newEUHA; }
void Tank::setELowerPlateArmor(int newELPA) { this->eLowerPlateArmor = newELPA; }
void Tank::setESideArmor(int newESA) { this->eSideArmor = newESA; }
void Tank::setHealthPoints(int newHealthPoints) { this->healthPoints = newHealthPoints; }
void Tank::setTrackHealth(int newHealthPoints) { this->trackHealth = newHealthPoints; }
void Tank::setViewRange(int newViewRange) { this->viewRange = newViewRange; }

void Tank::setHeadingAngle(double newCalculatedHeadingAngle) {

	this->headingAngle = newCalculatedHeadingAngle;
	//this->rightSideFacingAngle = calculatedRightSideFacingAngle;
	//this->leftSideFacingAngle = calculatedLeftSideFacingAngle;
}

void Tank::setXYPos(double newX, double newY) {
	this->xPos = newX;
	this->yPos = newY;
}

void Tank::setIsLoaded(bool x) { this->isLoaded = x; }
void Tank::setSecondsUntilReloaded(double x) { this->secondsUntilReloaded = x; }
void Tank::setIsMoving(bool x) { this->isMoving = x; }
void Tank::setIsSpoted(bool x) { this->isSpoted = x; }
void Tank::setTrackIsBroken(bool x) { this->trackBroken = x; }
void Tank::setSecondsUntilMobile(int x) { this->secondsUntilMobile = x; }
void Tank::setMoveDirection(std::string x) { this->moveDirection = x; }
void Tank::setCurrentSpeed(int x) { this->currentSpeed = x; }
void Tank::setTargetTraverseDegree(double x) { this->targetTraverseDegree = x; }
void Tank::setDirectionPrompt(std::string str) { this->directionPrompt = str; }
void Tank::setXMetersOut(int x) { this->xMetersOut = x; }
void Tank::setMovingPrompt(std::string str) { this->movingPrompt = str; }
void Tank::setTurningPrompt(std::string str) { this->turningPrompt = str; }
void Tank::setFireTarget(std::string str) { this->fireTarget = str; }
void Tank::addNotification(std::string str) { this->notifications.push_back(str); }
void Tank::clearNotifications() { this->notifications.clear(); }

// this will calculate the new headingDegree given a turn degree
double Tank::calculateNewDegHeadingGiven(double turnDegree) {

	double calculated = this->headingAngle + turnDegree;

	if (calculated > 359) {
		calculated -= 360;
	}
	else if (calculated < 0) {
		calculated += 360;
	}

	return calculated;
}

// move a tank one seconds worth of it's speed forward or backward or just keep it sitting still
void Tank::oneSecOfMoving(Tank& otherTank) {
	double metersPerSec = (this->topSpeed) * .27777;
	double travelAngle = this->headingAngle;
	double travelAngleRads;
	double deltaX;
	double deltaY;
	double newXPos;
	double newYPos;

	if (this->moveDirection == "") {
		metersPerSec = 0;
		this->movingPrompt = "Holding Position";
		this->setIsMoving(false);
	}
	else if (this->moveDirection == "backward") {
		travelAngle = calculateNewDegHeadingGiven(180);
	}

	travelAngleRads = travelAngle * (3.1415926535897232 / 180);
	deltaX = metersPerSec * cos(travelAngleRads);
	deltaY = metersPerSec * sin(travelAngleRads);

	newXPos = (this->xPos) + deltaX;
	newYPos = (this->yPos) + deltaY;

	if (newXPos > 1000 || newYPos > 1000 || newXPos < 0 || newYPos < 0) { // if the tank is out of bounds

		this->moveDirection = "";
		this->movingPrompt = "Holding Position";
	}
	else if (collisionDetecter(deltaX, deltaY, otherTank) == true) { // if they will collide
		this->moveDirection = "";
		this->movingPrompt = "Holding Position";
	}
	else { // if everything is fine

		setXYPos(newXPos, newYPos);

		if (this->moveDirection != "") {
			this->movingPrompt = "Moving ";
			this->movingPrompt += this->moveDirection;
			if (!this->getTrackIsBroken())// if the move direction isn't nothing, and the track isn't broke, set is moving to true
				this->setIsMoving(true); // new line newer line
		}
	}
}

// retuns the heading to an enemy when you pass in an enemy tank reference
double Tank::getHeadingToEnemy(Tank& enemyTank) {
	double rawXDis = enemyTank.getXPos() - this->xPos;
	double rawYDis = enemyTank.getYPos() - this->yPos;

	bool xPositive = rawXDis >= 0;
	bool xNegative = rawXDis < 0;
	bool yPositive = rawYDis >= 0;
	bool yNegative = rawYDis < 0;

	double xDisplacement = abs(this->xPos - enemyTank.getXPos());
	double yDisplacement = abs(this->yPos - enemyTank.getYPos());

	double distanceToEnemy = sqrt(
		pow(xDisplacement, 2) + pow(yDisplacement, 2)
	);

	// this shouldn't cause a bug so long as distance to enemy isn't zero
	double headingToEnemy = util::radsToDegs(
		asin(yDisplacement / distanceToEnemy)
	);

	if (xNegative && yPositive) {
		headingToEnemy = 180 - headingToEnemy;
	}
	else if (xNegative && yNegative) {
		headingToEnemy = 180 + headingToEnemy;
	}
	else if (xPositive && yNegative) {
		headingToEnemy = 360 - headingToEnemy;
	}
	this->xMetersOut = (int)distanceToEnemy;
	return headingToEnemy;
}

// Assigns the direction prompt to something like, "45 deg to our left"
// used to avoid something dumb like "Enemy is 200 degrees to our left", that would be dumb
void Tank::assignDirectionPromptGiven(double thisHeading, double headingToEnemy) {
	int trial = thisHeading - headingToEnemy;
	int degTo;
	std::string direction = "";
	bool positive;

	if (trial >= 0) {
		positive = true;
	}
	else {
		positive = false;
	}

	if (abs(trial) > 180) {
		degTo = 360 - abs(trial);
		positive = !positive;
	}
	else {
		degTo = trial;
	}

	if (positive) {
		direction = "right";
	}
	else {
		direction = "left";
	}

	// for the love of God, keep degTo as an int
	// look out for all those doubles related to angle now... blah
	if (abs(degTo) == 180) {
		this->directionPrompt = "Enemy tank behind us!";
	}
	else if (degTo == 0 || degTo == -0) {
		this->directionPrompt = "Enemy tank straight ahead!";
	}
	else if (degTo > 0 || degTo < 0) {
		std::string str = "Enemy tank ";
		str += std::to_string(abs(degTo));
		str += " degrees to the ";
		str += direction;
		str += "!";
		this->directionPrompt = str;
	}
}

// breaks up the deltaX and deltaY into tiny pieces and tests for a collision ( the two tanks being too close )
bool Tank::collisionDetecter(double &deltaX, double &deltaY, Tank& otherTank) {

	const double twentiethDX = deltaX / 20;
	const double twentiethDY = deltaY / 20;

	double runningX = this->xPos;
	double runningY = this->yPos;

	double otherTankX = otherTank.getXPos();
	double otherTankY = otherTank.getYPos();

	bool collision = false;

	for (int i = 0; i < 20; i++) {

		double distance = sqrt(pow(otherTankX - runningX, 2) + pow(otherTankY - runningY, 2));

		if (distance < 5) {
			collision = true;
			setXYPos(runningX - twentiethDX, runningY - twentiethDY);
			break;
		}
		runningX += twentiethDX;
		runningY += twentiethDY;
	}
	return collision;
}

// some complex logic getting the heading and turning angles correct 
void Tank::oneSecOfTurning() {

	if (targetTraverseDegree < 0) {
		if (abs(this->targetTraverseDegree) >= (this->traverseAnglesPerSec)) {

			double effect = -1 * (this->traverseAnglesPerSec);
			setHeadingAngle(calculateNewDegHeadingGiven(effect));
			targetTraverseDegree += traverseAnglesPerSec;
			this->turningPrompt = "Turning Right";
		}
		else {
			double effect = (this->targetTraverseDegree);
			setHeadingAngle(calculateNewDegHeadingGiven(effect));
			targetTraverseDegree -= targetTraverseDegree;
			this->turningPrompt = "Turning Right";

		}
	}
	else if (targetTraverseDegree > 0) {
		if (targetTraverseDegree >= this->traverseAnglesPerSec) {

			double effect = (this->traverseAnglesPerSec);
			setHeadingAngle(calculateNewDegHeadingGiven(effect));
			targetTraverseDegree -= traverseAnglesPerSec;
			this->turningPrompt = "Turning Left";

		}
		else {
			double effect = (this->targetTraverseDegree);
			setHeadingAngle(calculateNewDegHeadingGiven(effect));
			targetTraverseDegree -= targetTraverseDegree;
			this->turningPrompt = "Turning Left";

		}
	}
	else if (targetTraverseDegree == 0) {
		this->turningPrompt = "Not Turning";

	}
}

void Tank::assignPossibleTargets(Tank& enemyTank) {

	double enemyHeading = enemyTank.getHeadingAngle();
	double headingToEnemy = this->getHeadingToEnemy(enemyTank);

	double difference = abs(enemyHeading - headingToEnemy);

	double other = 360 - difference;

	double smaller;

	if (difference >= other) {
		smaller = other;
	}
	else {
		smaller = difference;
	}

	// turret is always in the possibleTargets
	// track is always in the possibleTargets

	if (smaller <= 170 && smaller >= 10) { // adds side

		if (!util::vectorContains(this->possibleTargets, "side")) {
			possibleTargets.push_back("side");
		}
	}
	else if (util::vectorContains(this->possibleTargets, "side")) {
		util::removeThisFromVector(this->possibleTargets, "side");
	}
	if (smaller <= 80 && smaller >= 0) {
		if (!util::vectorContains(this->possibleTargets, "rear")) {
			possibleTargets.push_back("rear");
		}
		if (util::vectorContains(this->possibleTargets, "front")) {
			util::removeThisFromVector(this->possibleTargets, "front");
		}
	}
	if (smaller <= 180 && smaller >= 100) {
		if (!util::vectorContains(this->possibleTargets, "front")) {
			possibleTargets.push_back("front");
		}
		if (util::vectorContains(this->possibleTargets, "rear")) {
			util::removeThisFromVector(this->possibleTargets, "rear");
		}
	}
	else if (util::vectorContains(this->possibleTargets, "front")) {
		util::removeThisFromVector(this->possibleTargets, "front");
	}
}

void Tank::fireAtTarget(Tank& otherTank) {

	// If the tank is not even reloaded
	if (!this->getIsLoaded()) {
		if (this->getIsPlayerTank()) {
			this->addNotification("RELOADED IN " + std::to_string((int)ceil(this->getSecondsUntilReloaded())) + " SECONDS");
			this->displayAllNotifications();
		}
		this->setFireTarget(""); // might have to have this be exclusively for player tank
		return;
	}

	// get the impact angle from our heading and the heading of specific enemy module
	// if the fire target is not even a possible target
	if (!util::vectorContains(this->getPossibleTargets(), this->getFireTarget())) {
		// do an allert that the target module is no longer in sight
		this->setFireTarget("");
		return; // if we aren't reloaded, I want to exit this whole method
	}

	double enemyArmorHeading = otherTank.getHeadingAngle();
	if (this->fireTarget == "front" || this->fireTarget == "rear" || this->fireTarget == "turret") {
		enemyArmorHeading = otherTank.calculateNewDegHeadingGiven(90);
	}

	// lets just say for simplicity that the impact angle of the track will always be 90 degs
	double potentialImpactAngle = util::impactAngleFrom(this->getHeadingToEnemy(otherTank), enemyArmorHeading);
	if (this->getFireTarget() == "track") {
		potentialImpactAngle = 90;
	}

	double distanceToEnemyTank = this->getXMetersOut();
	double chanceToMiss;

	// If the tank is moving, we want to calculate the chance to miss using the moving dispersion
	bool x = this->getIsMoving();
	if (this->getIsMoving())
		chanceToMiss = util::getChanceToMiss(distanceToEnemyTank, this->getMovingDispersion(), potentialImpactAngle);
	else
		chanceToMiss = util::getChanceToMiss(distanceToEnemyTank, this->getStillDispersion(), potentialImpactAngle);

	// do I have to do an srand() here? last time it was 42! // YES! WE NEED an srand i repeat, srand!

	srand(time(0));
	int oneToOnehundred = util::randomNumXtoY(1, 100);

	double finalChance = 100 * chanceToMiss;

	if (oneToOnehundred < finalChance) { // then the shot missed

		if (this->getIsPlayerTank()) {
			this->addNotification("WE MISSED");
			this->displayAllNotifications();
		}
		else {
			otherTank.addNotification("ENEMY SHELL JUST MISSED US");
			otherTank.displayAllNotifications();
		}

		this->setFireTarget("");
	}
	else {
		this->hitEnemy(otherTank, potentialImpactAngle, this->getFireTarget());
		this->setFireTarget("");
	}
	this->setIsLoaded(false);
	this->setSecondsUntilReloaded(this->getReloadTime());
}

void Tank::hitEnemy(Tank& otherTank, double impactAngle, std::string tankModule) {

	// if you hit the track, roll chance to break track
	double baseArmorValue;

	if (tankModule == "track") {
		// remove health from track health
		otherTank.setTrackHealth(otherTank.getTrackHealth() - this->getDamage());
		if (otherTank.getTrackHealth() <= 0)
			otherTank.breakTrack();

		if (otherTank.getIsPlayerTank()) {
			otherTank.addNotification("OUR TRACK IS HIT! TRACK HEALTH IS " + std::to_string(otherTank.getTrackHealth()));
			otherTank.displayAllNotifications();

		}
		else {
			
			this->addNotification("ENEMY TRACK IS HIT! ENEMY TRACK HEALTH IS "
				+ std::to_string(otherTank.getTrackHealth()));
			this->displayAllNotifications();
		}
		if (otherTank.getTrackIsBroken())
			otherTank.setTrackHealth(otherTank.getMaxTrackHealth() - 20);

		
	}
	else {
		baseArmorValue = otherTank.getArmorOf(tankModule);
		double effectiveArmor = baseArmorValue / (cos(util::degsToRads(90 - impactAngle)));

		if (this->getPenetration() > effectiveArmor) {
			// damage the enemy tank
			otherTank.setHealthPoints(otherTank.getHealthPoints() - this->getDamage());

			std::string note = "DIRECT HIT! ENEMY HEALTH AT: " + std::to_string(otherTank.getHealthPoints());
			std::string note2 = "THEY HIT OUR " + util::thisToUpperCase(tankModule) + "! " + 
				"OUR HEALTH IS: " + std::to_string(otherTank.getHealthPoints());

			// If it was the player tank that hit their target, notify the first note
			if (otherTank.getIsPlayerTank()) {
				otherTank.addNotification(note2);
				otherTank.displayAllNotifications();
			}
			else {
				this->addNotification(note);
				this->displayAllNotifications();
			}

		}
		else { // the shell bounced
			if (otherTank.getIsPlayerTank()) {
				otherTank.addNotification("ENEMY SHELL JUST GRAZED US!");
				otherTank.displayAllNotifications();
			}
			else {
				this->addNotification("OUR SHELL BOUNCED!");
				this->displayAllNotifications();
			}
		}
	}

}

void Tank::breakTrack() {
	// set tank moving to false
	this->setIsMoving(false);
	// set trackBroken to true
	this->setTrackIsBroken(true);
	// set secondsUntilMobile to 10
	this->setSecondsUntilMobile(10);
	this->setTrackHealth(0);

	if (this->getIsPlayerTank()) {
		this->addNotification("OUR TRACK IS BROKEN! WE CAN'T MOVE FOR 10 SECONDS!");
		this->displayAllNotifications();
	}
	else {
		//addNotification("ENEMY TRACK IS BROKEN! THEY CAN'T MOVE FOR 10 SECONDS!");
	}

}

void Tank::displayAllNotifications(Tank& playerT) {

	std::vector<std::string> playerNotifications = playerT.getNotifications();

	for (int i = 0; i < playerNotifications.size(); i++) {
		system("CLS");
		std::cout << std::endl;
		std::cout << playerNotifications[i] << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds{ 2 });
	}

	system("CLS");
	playerT.clearNotifications();
}

void Tank::displayAllNotifications() {

	std::vector<std::string> playerNotifications = this->getNotifications();

	for (int i = 0; i < playerNotifications.size(); i++) {
		system("CLS");
		std::cout << std::endl;
		std::cout << playerNotifications[i] << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds{ 3 });
	}

	system("CLS");
	this->clearNotifications();
}
