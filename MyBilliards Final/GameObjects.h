#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <cmath>
#include "glut.h"
#include "ColourOGL.h"
#include "Balls.h"
#include "Vector3.h"
#include "FSM.h"

//================ Includes Above ================|============== Macros Below =======================
#define NUMBALLS 10			//increase this if you add more balls
#define NUMPOCKETS 6
#define PI 3.14159265358979323846264338327950288419716939937510

//=============== Macros Above ===================|============== Enumerators Below ==================
enum { WHITE = 0, RED, BLUE, YELLOW, GREEN, ORANGE, PURPLE, BROWN, PINK, BLACK };	//the balls
enum { UPLEFT = 0, UPMID, UPRIGHT, LOWLEFT, LOWMID, LOWRIGHT };						//the pockets

//============== Enumerators Above ===============|============== Classes Below ======================
class GameObjects
{
public:
	GameObjects();
	virtual ~GameObjects();

	void SpawnBalls();
	void CreatePockets();
	void Table();
	void AimBall();
	void NextBall();
	void AimDot();
	void AimLine();
	void PowerGauge();

	int InitObjects();

//=========== Game Object Methods Above ===========|============ Game Logic Methods Below ============
	Vector3 GetCircumPoints(float radius, Vector3 pos, float radial);
	Vector3 GetSpherePoints(float radius, Vector3 pos, float radial, float elevation);	//this function is now redundant as angular motion is not implemented

	//Ball status
	void WorkoutVel();
	void BallMoving();
	void UpdateMovingBalls();
	bool BallStationary();

	//Collisions
	void RailCollision();
	void PocketCollision();
	bool BallBallCollision();
	void BallBallResponse();

	//FiniteStateMachine
	void UseFSM();

//============= Class Methods Above =============|============== Member Variables Below ==============
	float m_fForceCue;	//initial force of the cue strike
	float m_fRads;		//radius of a imaginary circle, used to determine the length of the aiming line
	float m_fAngle;		//angle used to determine the aiming direction
	float m_fCOFr;		//coefficient of friction converted to program units

	Vector3 m_vecPoint;				//The position of the aiming dot
	Vector3 m_vecAimLine;			//The position of the aiming line
	Balls m_CBalls[NUMBALLS];		//Array of balls
	FSM	m_FiniteStateMachine;

private:
	ColourOGL m_colour;				//Sets the colour of the object	
		
	Balls m_CPockets[NUMPOCKETS];	//Array of pockets

};

#endif