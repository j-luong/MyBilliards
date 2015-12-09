#include "FSM.h"

//---------------------------------------------------------------------------------------------------------------
// Name: FSM()
// Desc: default constructor
//
FSM::FSM() {

	m_bFoul			= false;
	m_bInstaLose	= false;
	m_bBallPocketed = false;
	m_bGameOver		= false;
	m_bHitFirstBall = false;
	m_bBallMoving	= false;
	m_bHitWrongBall = false;

	m_iPlayer		= 2;
	m_iNextBall		= 1;
	m_iGameState	= P1SHOOT;
	m_iBallsLeft	= 9;
	m_iCurrentBalls = 9;

} //FSM

//---------------------------------------------------------------------------------------------------------------
// Name: ~FSM()
// Desc: default destructor
//
FSM::~FSM() {

} //~FSM

//---------------------------------------------------------------------------------------------------------------
// Name: CheckState()
// Desc: Checks the current gamestate
//
void FSM::CheckState() {

	switch(m_iGameState) {

		case P1SHOOT:	//output whose turn it is to shoot
			RenderBitmapString(-10.5,0.0,-23.0,GLUT_BITMAP_TIMES_ROMAN_24,"Player 1 must hit: ");
			RenderBitmapString(10.0,0.0,-23.0,GLUT_BITMAP_TIMES_ROMAN_24,"Press H for help");
			m_bFoul = false;
			break;

		case P2SHOOT:
			RenderBitmapString(-10.5,0.0,-23.0,GLUT_BITMAP_TIMES_ROMAN_24,"Player 2 must hit: ");
			RenderBitmapString(10.0,0.0,-23.0,GLUT_BITMAP_TIMES_ROMAN_24,"Press H for help");
			m_bFoul = false;
			break;

		case POCKETWHITEFOUL:	//if a foul is incurred then change the player turns and set the foul flag to true
			if(m_iPlayer == 1)
				m_iPlayer = 2;
			else
				m_iPlayer = 1;
			m_bFoul = true;
			break;

		case HITWRONGBALLFOUL:
			if(m_iPlayer == 1)
				m_iPlayer = 2;
			else
				m_iPlayer = 1;
			m_bFoul = true;
			break;

		case NOBALLHITFOUL:
			if(m_iPlayer == 1)
				m_iPlayer = 2;
			else
				m_iPlayer = 1;
			m_bFoul = true;
			break;

		case GAMEOVER:
			if(m_bInstaLose) {			//this bool returns true when a foul has been committed, it resets to false when all balls have stopped

				if(m_iPlayer == 1) {	//if a foul has been committed when in this state then the player has potted the black illegally, thus they must forfeit the match

					RenderBitmapString(-10.0,-5.0,0.0,GLUT_BITMAP_TIMES_ROMAN_24,"BLACK POTTED ILLEGALLY P2 WINS");
					RenderBitmapString(-10.0,-5.0,-2.0,GLUT_BITMAP_TIMES_ROMAN_24,"PRESS ESC TO QUIT");
				}
				else {

					RenderBitmapString(-10.0,-5.0,0.0,GLUT_BITMAP_TIMES_ROMAN_24,"BLACK POTTED ILLEGALLY P1 WINS");
					RenderBitmapString(-10.0,-5.0,-2.0,GLUT_BITMAP_TIMES_ROMAN_24,"PRESS ESC TO QUIT");
				}
			}
			else if(m_iPlayer == 1) {	//if the player has potted the black legally then that player wins

				RenderBitmapString(-5.0,-5.0,0.0,GLUT_BITMAP_TIMES_ROMAN_24,"GAME OVER P1 WINS");
				RenderBitmapString(-5.0,-5.0,-2.0,GLUT_BITMAP_TIMES_ROMAN_24,"PRESS ESC TO QUIT");
			}
			else {

				RenderBitmapString(-5.0,-5.0,0.0,GLUT_BITMAP_TIMES_ROMAN_24,"GAME OVER P2 WINS");
				RenderBitmapString(-5.0,-5.0,-2.0,GLUT_BITMAP_TIMES_ROMAN_24,"PRESS ESC TO QUIT");
			}
			break;

		case HELP:	//display help text when help is the current game state
			RenderBitmapString(-15.0,-5.0,16.0,GLUT_BITMAP_HELVETICA_18,"ARROW KEYS: Aim/Power");
			RenderBitmapString(-15.0,-5.0,14.0,GLUT_BITMAP_HELVETICA_18,"T/B: Topspin/Backspin");
			RenderBitmapString(-15.0,-5.0,12.0,GLUT_BITMAP_HELVETICA_18,"SPACEBAR: Shoot");
			RenderBitmapString(-15.0,-5.0,10.0,GLUT_BITMAP_HELVETICA_18,"H: Toggle Help");
			RenderBitmapString(-15.0,-5.0,8.0,GLUT_BITMAP_HELVETICA_18,"F1: Toggle Fullscreen");
			RenderBitmapString(-15.0,-5.0,6.0,GLUT_BITMAP_HELVETICA_18,"ESC: Quit");
			RenderBitmapString(2.0,-5.0,16.0,GLUT_BITMAP_HELVETICA_18,"RULES:");
			RenderBitmapString(2.0,-5.0,15.0,GLUT_BITMAP_HELVETICA_12,"Players take turns to pot balls.");
			RenderBitmapString(2.0,-5.0,13.5,GLUT_BITMAP_HELVETICA_12,"The first ball to be hit MUST be the ball shown at");
			RenderBitmapString(2.0,-5.0,12.5,GLUT_BITMAP_HELVETICA_12,"the bottom of the screen otherwise a foul is incurred.");
			RenderBitmapString(2.0,-5.0,11.0,GLUT_BITMAP_HELVETICA_12,"As long as the correct ball is hit first, balls may be");
			RenderBitmapString(2.0,-5.0,10.0,GLUT_BITMAP_HELVETICA_12,"potted in any order.");
			RenderBitmapString(2.0,-5.0,8.5,GLUT_BITMAP_HELVETICA_12,"The player who pots the black in a legal manner, wins.");
			RenderBitmapString(2.0,-5.0,7.0,GLUT_BITMAP_HELVETICA_12,"If the black is potted in an illegal manner (through a foul)");
			RenderBitmapString(2.0,-5.0,6.0,GLUT_BITMAP_HELVETICA_12,"the player who potted the black illegally, loses.");

			RenderBitmapString(2.0,-1.0,-22.6,GLUT_BITMAP_HELVETICA_18,"NEXT BALL");
			RenderBitmapString(-24.5,-1.0,-4.0,GLUT_BITMAP_HELVETICA_18,"AIM BALL");
			RenderBitmapString(20.0,-5.0,-20.0,GLUT_BITMAP_HELVETICA_18,"POW BAR");
						
			break;

	} //end switch

} //CheckState

//---------------------------------------------------------------------------------------------------------------
// Name: SetState()
// Desc: Sets the current gamestate
//
void FSM::SetState(int state) {

	m_iGameState = state;

} //SetState

//---------------------------------------------------------------------------------------------------------------
// Name: SetNextBallColour()
// Desc: Sets the colour of the next ball to be hit
//
void FSM::SetNextBallColour(Balls &ball) {

	m_iNextBall = ball.m_iID;

	switch(m_iNextBall) {

		case 1:
			m_colour.Set(1.0f,0.0f,0.0f);
			break;
		case 2:
			m_colour.Set(0.0f,0.0f,1.0f);
			break;
		case 3:
			m_colour.Set(1.0f,1.0f,0.0f);
			break;
		case 4:
			m_colour.Set(0.0f,0.5f,0.0f);
			break;
		case 5:
			m_colour.Set(1.0f,0.50f,0.0f);
			break;
		case 6:
			m_colour.Set(0.63f,0.13f,0.94f);
			break;
		case 7:
			m_colour.Set(0.55f,0.27f,0.07f);
			break;
		case 8:
			m_colour.Set(1.0f,0.75f,0.79f);
			break;
		case 9:
			m_colour.Set(0.0f,0.0f,0.0f);
			break;

	} //end switch

} //SetNextBallColour

//---------------------------------------------------------------------------------------------------------------
// Name: RenderBitmapString()
// Desc: Renders text onto the screen
//
void FSM::RenderBitmapString(float x, float y, float z, void *font, char *string) {

	char *c;
	glRasterPos3f(x,y,z);

	for (c=string; *c != '\0'; c++)
		glutBitmapCharacter(font, *c);

} //RenderBitmapString