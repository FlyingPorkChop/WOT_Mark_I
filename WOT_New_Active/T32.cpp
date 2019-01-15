#include "Tank.h"
#include "T32.h"
#include <iostream>
#include <string>
using namespace std;

T32::T32(bool isPlayerTank)
	: Tank(isPlayerTank, "T32", 320, 198, 220)


{

	reloadTime = 10.16;
	aimTime = 2.21;
	ammoCount = 43;
	topSpeed = 35;
	traverseAnglesPerSec = 26.06;
	eUpperHullArmor = 182;
	eLowerPlateArmor = 187;
	eSideArmor = 76;
	eRearArmor = 51;
	eTurretArmor = 300;
	healthPoints = 1550;
	trackHealth = 220;
	viewRange = 400;
	stillDispersion = 0.39;
	movingDispersion = 0.59;

	xPos = 0;
	yPos = 0;
}
