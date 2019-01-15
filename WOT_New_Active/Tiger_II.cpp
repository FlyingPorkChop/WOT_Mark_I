#include "Tank.h"
#include "Tiger_II.h"


Tiger_II::Tiger_II(bool isPlayerTank)
	:Tank(isPlayerTank, "Tiger II", 320, 225, 240)

{

	reloadTime = 9.97;
	aimTime = 2.4;
	ammoCount = 42;
	topSpeed = 38;
	traverseAnglesPerSec = 28.66;
	eUpperHullArmor = 205;
	eLowerPlateArmor = 160;
	eSideArmor = 84;
	eRearArmor = 88;
	eTurretArmor = 185;
	healthPoints = 1600;
	trackHealth = 200;
	viewRange = 390;
	stillDispersion = 0.30;
	movingDispersion = 0.47;

	// I want to see if I can retrieve the headingAngle and the sideFacingAngle from a Tiger_II without defining it within it's own cpp file
	// To answer your question, you indeed can! 

	xPos = 0;
	yPos = 0;
}

