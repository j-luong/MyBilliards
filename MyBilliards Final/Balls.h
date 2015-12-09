#ifndef BALLS_H
#define BALLS_H

#include "ColourOGL.h"
#include "Vector3.h"
#include "glut.h"

//================== Includes Above ====================|================ Classes Below ================

class Balls
{
public:
	Balls();
	virtual ~Balls();

	void CreateBall(ColourOGL colour);

	void WorkOutVelocity(float fForceCue, float fAngle);
	void UpdateMovingBalls(float fCoFr);
	void BallMoving();

	void RailCollision();
	bool BallCollision(Balls &ball);
	void BallPocketCollision(Balls &pocket);

	void BallCollisionResponse(Balls &ball);

//============== Class Methods Above ==============|============== Member Variables Below ==============

	Vector3	m_vecPosition;
	Vector3	m_vecVelocity;
	Vector3	m_vecFriction;	
	
	float	m_fRadius;	
	float	m_fCoRest;		//coefficient of restitution

	bool	m_bMoving;
	bool	m_bCollided;
	bool	m_bPocketed;
	bool	m_bOutOfPlay;	//is the ball out of play? i.e. it has been potted

	int		m_iID;			//ID of ball
	
private:
	float	m_fMass;
	float	m_fPI;
	float	m_fGrav;		//gravity

};

#endif BALLS_H //BALLS_H