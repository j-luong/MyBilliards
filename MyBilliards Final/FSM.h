#ifndef FSM_H
#define FSM_H

#include "Balls.h"
#include "ColourOGL.h"

//================ Includes Above ================|============== Classes Below ========================
class FSM
{
public:
	FSM();
	~FSM();

	void CheckState();
	void SetState(int state);
	int GetState() {return m_iGameState;}	//returns the value of the current state

	void SetNextBallColour(Balls &ball);

	void RenderBitmapString(float x,float y,float z,void *font,char *string);

//============== Class Methods Above ==============|============== Member Variables Below ==============
	bool m_bFoul;			//was the last shot a foul?
	bool m_bInstaLose;		//has the black been potted illegally?

	bool m_bBallPocketed;	//has the ball been potted?
	bool m_bGameOver;		//is the game over?
	bool m_bHitFirstBall;	//has the 1st ball been hit?
	bool m_bAnyBallHit;		//has any ball been hit?
	bool m_bBallMoving;		//are the balls moving?
	bool m_bHitWrongBall;	//has the wrong ball been hit?

	int m_iNextBall;		//the next ball to be hit
	int m_iPlayer;			//who's turn is it
	int m_iGameState;		//the current gamestate

	int m_iBallsLeft;		//how many balls were on the table in the last shot
	int m_iCurrentBalls;	//how many balls are currently on the table

	enum { P1SHOOT = 0, P2SHOOT, GAMEOVER, POCKETWHITEFOUL, HITWRONGBALLFOUL, NOBALLHITFOUL, HELP }; //Gamestates

	ColourOGL m_colour;

};

#endif FSM_H