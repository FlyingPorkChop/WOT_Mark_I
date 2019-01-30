#pragma once

#include "util.h"
#include <map>
#include <chrono>
#include <thread>

class Tank {
protected:

	const bool ISPLAYERTANK;
	const std::string TANK_NAME; //In the Tank() constructor, why can't I just set the values instead of having to pass them into the constructor as a parameter?
	const int DAMAGE;
	const int PENETRATION;

	double reloadTime;
	double aimTime;
	int ammoCount;
	int topSpeed;
	double stillDispersion;
	double movingDispersion;

	double traverseAnglesPerSec;
	int eUpperHullArmor;
	int eLowerPlateArmor;
	int eSideArmor;
	int eRearArmor;
	int eTurretArmor;
	int healthPoints;
	const int MAX_TRACK_HEALTH; // problems here
	int trackHealth;


	int viewRange;
	std::map<std::string, int> armorOf = {
		{ "front", this->eLowerPlateArmor },
	{ "side", this->eSideArmor },
	{ "rear", this->eRearArmor },
	{ "turret", this->eTurretArmor }
	};

	double headingAngle; // if there were a spear going from the ass of the tank to the front, this would be the angle of that line relative to the x, y coordinate plane
	int leftSideFacingAngle;
	int rightSideFacingAngle;

	double xPos;
	double yPos;

	bool isLoaded = true;
	double secondsUntilReloaded = 0;

	bool isMoving;
	bool isSpoted;
	bool trackBroken;
	int secondsUntilMobile = 0;

	std::string moveDirection;
	std::string fireTarget = ""; // the enemy module about to be shot
	std::string directionPrompt;
	double targetTraverseDegree = 0;

	int currentSpeed = 0;
	int xMetersOut;
	std::string movingPrompt;
	std::string turningPrompt;
	std::vector<std::string> possibleTargets{ "turret", "front", "track" }; // you can always shoot their turret
	std::vector<std::string> notifications;

	// if something drastic happens, we need to clarly allert the user
	bool promptNeeded = false;

public:
	Tank(bool isplayerTank, std::string name, int damage, int pen, int mth);
	bool getIsPlayerTank();
	std::string getTankName();
	int getDamage();
	int getPenetration();

	double getReloadTime();
	double getAimTime();
	int getAmmoCount();
	int getTopSpeed();
	double getStillDispersion();
	double getMovingDispersion();
	double getTraverseAnglesPerSec();
	int getEUpperHullArmor();
	int getELowerPlateArmor();
	int getESideArmor();

	int getArmorOf(std::string str);

	int getHealthPoints();
	int getTrackHealth();
	int getMaxTrackHealth();
	int getViewRange();

	double getHeadingAngle();

	double getYPos();
	double getXPos();

	bool getIsLoaded();
	double getSecondsUntilReloaded();

	bool getIsMoving();
	bool getIsSpoted();
	bool getTrackIsBroken();
	int getSecondsUntilMobile();

	std::string getMoveDirection();

	int getCurrentSpeed();
	double getTargetTraverseDegree();
	std::string getDirectionPrompt();
	int getXMetersOut();
	std::string getMovingPrompt();
	std::string getTurningPrompt();
	double getHeadingToEnemy(Tank& enemyTank);
	std::vector<std::string>& getPossibleTargets();
	std::vector<std::string>& getNotifications();
	std::string getFireTarget();

	// START SETTERS

	void setReloadTime(double newReloadTime);
	void setAimTime(double newAimTime);
	void setAmmoCount(int newAmmoCount);
	void setTopSpeed(int newTopSpeed);
	void setStillDispersion(double x);
	void setMovingDispersion(double x);
	void setTraverseAnglesPerSec(double newTAPS);
	void setEUpperHullArmor(int newEUHA);
	void setELowerPlateArmor(int newELPA);
	void setESideArmor(int newESA);
	void setHealthPoints(int newHealthPoints);
	void setTrackHealth(int newHealthPoints);
	void setViewRange(int newViewRange);

	void setHeadingAngle(double newCalculatedHeadingAngle); // the new heading value will need to be caluculated

	void setXYPos(double newX, double newY);

	void setIsLoaded(bool x);
	void setSecondsUntilReloaded(double x);
	void setIsMoving(bool x);
	void setIsSpoted(bool x);
	void setTrackIsBroken(bool x);
	void setSecondsUntilMobile(int x);
	void setMoveDirection(std::string x);
	void setCurrentSpeed(int x);
	void setTargetTraverseDegree(double x);
	void setDirectionPrompt(std::string str);
	void setXMetersOut(int x);
	void setMovingPrompt(std::string str);
	void setTurningPrompt(std::string str);
	void assignPossibleTargets(Tank& enemyTank);
	void addNotification(std::string str);
	void clearNotifications();
	void setFireTarget(std::string str);

	// Here we go with general tank functions

	void oneSecOfMoving(Tank& otherTank);
	double calculateNewDegHeadingGiven(double turnDegree);
	void assignDirectionPromptGiven(double thisHeading, double headingToEnemy);
	void oneSecOfTurning();
	void fireAtTarget(Tank& otherTank);
	void hitEnemy(Tank& otherTank, double impactAngle, std::string tankModule);
	void breakTrack();
	void displayAllNotifications(Tank& playerT);
	void displayAllNotifications();

	bool collisionDetecter(double &deltaX, double &deltaY, Tank& otherTank);
};