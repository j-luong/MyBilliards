#include "GameObjects.h"

//---------------------------------------------------------------------------------------------------------------
// Name: GameObjects()
// Desc: default constructor
//
GameObjects::GameObjects() {

	m_fForceCue = 0.5f;
	m_fRads = 20.0;
	m_fAngle = 270.0f;
	m_fCOFr = 0.0002f;	//laptop
	//m_fCOFr = 0.0003f;	//pc

} //GameObjects()

//---------------------------------------------------------------------------------------------------------------
// Name: ~GameObjects()
// Desc: default destructor
//
GameObjects::~GameObjects() {

} //~GameObjects()

//---------------------------------------------------------------------------------------------------------------
// Name: SpawnBalls()
// Desc: spawns all the balls using the CreateBall method from the Balls class
//
void GameObjects::SpawnBalls() {

	m_colour.Set(1.0f,1.0f,1.0f);											//set the colour of the ball
	m_CBalls[WHITE].CreateBall(m_colour);									//create the ball
	if(m_CBalls[WHITE].m_bPocketed) {										//what to do when the ball has been potted
		if(!BallStationary()){
			m_CBalls[WHITE].m_vecPosition = Vector3(-12.0f,-1.0f,21.0f);	//move the ball off the table is ball are still moving
			m_CBalls[WHITE].m_vecVelocity = Vector3(0.0f,0.0f,0.0f);
		}
		else {
			m_CBalls[WHITE].m_vecPosition = Vector3(10.0f,-1.0f,0.0f);		//move it back onto the table when all balls have stopped
			m_CBalls[WHITE].m_bPocketed = false;	
		}
	}

	m_colour.Set(1.0f,0.0f,0.0f);											//set the colour of the ball
	m_CBalls[RED].CreateBall(m_colour);										//create the ball
	if(m_CBalls[RED].m_bPocketed) {											//what to do when the ball has been potted
		m_CBalls[RED].m_vecPosition = Vector3(-10.0f,-1.0f,21.0f);
		m_CBalls[RED].m_vecVelocity = Vector3(0.0f,0.0f,0.0f);
		m_CBalls[RED].m_bOutOfPlay = true;									//once the ball has been potted, it is out of play for good
	}

	m_colour.Set(0.0f,0.0f,1.0f);
	m_CBalls[BLUE].CreateBall(m_colour);
	if(m_CBalls[BLUE].m_bPocketed) {
		m_CBalls[BLUE].m_vecPosition = Vector3(-8.0f,-1.0f,21.0f);
		m_CBalls[BLUE].m_vecVelocity = Vector3(0.0f,0.0f,0.0f);
		m_CBalls[BLUE].m_bOutOfPlay = true;
	}

	m_colour.Set(1.0f,1.0f,0.0f);
	m_CBalls[YELLOW].CreateBall(m_colour);
	if(m_CBalls[YELLOW].m_bPocketed) {
		m_CBalls[YELLOW].m_vecPosition = Vector3(-6.0f,-1.0f,21.0f);
		m_CBalls[YELLOW].m_vecVelocity = Vector3(0.0f,0.0f,0.0f);
		m_CBalls[YELLOW].m_bOutOfPlay = true;
	}

	m_colour.Set(0.0f,0.5f,0.0f);
	m_CBalls[GREEN].CreateBall(m_colour);
	if(m_CBalls[GREEN].m_bPocketed) {
		m_CBalls[GREEN].m_vecPosition = Vector3(-4.0f,-1.0f,21.0f);
		m_CBalls[GREEN].m_vecVelocity = Vector3(0.0f,0.0f,0.0f);
		m_CBalls[GREEN].m_bOutOfPlay = true;
	}

	m_colour.Set(1.0f,0.50f,0.0f);
	m_CBalls[ORANGE].CreateBall(m_colour);
	if(m_CBalls[ORANGE].m_bPocketed) {
		m_CBalls[ORANGE].m_vecPosition = Vector3(-2.0f,-1.0f,21.0f);
		m_CBalls[ORANGE].m_vecVelocity = Vector3(0.0f,0.0f,0.0f);
		m_CBalls[ORANGE].m_bOutOfPlay = true;
	}

	m_colour.Set(0.63f,0.13f,0.94f);
	m_CBalls[PURPLE].CreateBall(m_colour);
	if(m_CBalls[PURPLE].m_bPocketed) {
		m_CBalls[PURPLE].m_vecPosition = Vector3(0.0f,-1.0f,21.0f);
		m_CBalls[PURPLE].m_vecVelocity = Vector3(0.0f,0.0f,0.0f);
		m_CBalls[PURPLE].m_bOutOfPlay = true;
	}

	m_colour.Set(0.55f,0.27f,0.07f);
	m_CBalls[BROWN].CreateBall(m_colour);
	if(m_CBalls[BROWN].m_bPocketed) {
		m_CBalls[BROWN].m_vecPosition = Vector3(2.0f,-1.0f,21.0f);
		m_CBalls[BROWN].m_vecVelocity = Vector3(0.0f,0.0f,0.0f);
		m_CBalls[BROWN].m_bOutOfPlay = true;
	}

	m_colour.Set(1.0f,0.75f,0.79f);
	m_CBalls[PINK].CreateBall(m_colour);
	if(m_CBalls[PINK].m_bPocketed) {
		m_CBalls[PINK].m_vecPosition = Vector3(4.0f,-1.0f,21.0f);
		m_CBalls[PINK].m_vecVelocity = Vector3(0.0f,0.0f,0.0f);
		m_CBalls[PINK].m_bOutOfPlay = true;
	}

	m_colour.Set(0.0f,0.0f,0.0f);
	m_CBalls[BLACK].CreateBall(m_colour);
	if(m_CBalls[BLACK].m_bPocketed) {
		m_CBalls[BLACK].m_vecPosition = Vector3(6.0f,-1.0f,21.0f);
		m_CBalls[BLACK].m_vecVelocity = Vector3(0.0f,0.0f,0.0f);
		m_CBalls[BLACK].m_bOutOfPlay = true;
	}

} //SpawnBalls()

//---------------------------------------------------------------------------------------------------------------
// Name: CreatePockets()
// Desc: creates all the pockets on the table
//
void GameObjects::CreatePockets() {
	
	//glPushMatrix();
	m_colour.Set(0.6f,0.6f,0.6f);
	for(int i = 0; i < NUMPOCKETS; i++)
		m_CPockets[i].CreateBall(m_colour);
	//glPopMatrix();

} //CreatePockets()

//---------------------------------------------------------------------------------------------------------------
// Name: Table()
// Desc: creates the table
//
void GameObjects::Table() {

	glPushMatrix();
	glColor3f(0.0,1.0,0.5);				//set the table colour to green
	glScaled(1.0,0.01,0.9);				//scale the table
	glutSolidCube(40.0);				//create the cube for the table
	glPopMatrix();

	//top rail
	glBegin(GL_QUADS);					//create the rails using GL_QUADS
		glColor3f(0.55,0.27,0.07);
		glVertex3f(-18.80,0.0,18.0);	//bottom left of quad
		glVertex3f(-1.18,0.0,18.0);		//bottom right of quad
		glVertex3f(-0.75,0.0,19.5);		//top right of quad
		glVertex3f(-19.20,0.0,19.5);	//top left of quad

		glColor3f(0.55,0.27,0.07);
		glVertex3f(1.18,0.0,18.0);		//bottom left of quad
		glVertex3f(18.80,0.0,18.0);		//bottom right of quad
		glVertex3f(19.20,0.0,19.5);		//top right of quad
		glVertex3f(0.75,0.0,19.5);		//top left of quad
	glEnd();

	//bottom rail
	glBegin(GL_QUADS);
		glColor3f(0.55,0.27,0.07);
		glVertex3f(-1.18,0.0,-18.0);	//top right of quad
		glVertex3f(-18.80,0.0,-18.0);	//top left of quad
		glVertex3f(-19.20,0.0,-19.5);	//bottom left of quad
		glVertex3f(-0.75,0.0,-19.5);	//bottom right of quad

		glColor3f(0.55,0.27,0.07);
		glVertex3f(18.80,0.0,-18.0);	//top right of quad
		glVertex3f(1.18,0.0,-18.0);		//top left of quad
		glVertex3f(0.75,0.0,-19.5);		//bottom left of quad
		glVertex3f(19.20,0.0,-19.5);	//bottom right of quad
	glEnd();

	//left rail
	glBegin(GL_QUADS);
		glColor3f(0.55,0.27,0.07);
		glVertex3f(-20.0,0.0,17.10);	//top right of quad
		glVertex3f(-21.3,0.0,18.40);	//top left of quad
		glVertex3f(-21.3,0.0,-18.40);	//bottom left of quad
		glVertex3f(-20.0,0.0,-17.10);	//bottom right of quad
	glEnd();

	//right rail
	glBegin(GL_QUADS);
		glColor3f(0.55,0.27,0.07);
		glVertex3f(21.3,0.0,18.40);		//top right of quad
		glVertex3f(20.0,0.0,17.10);		//top left of quad
		glVertex3f(20.0,0.0,-17.10);	//bottom left of quad
		glVertex3f(21.3,0.0,-18.40);	//bottom right of quad
	glEnd();

} //Table()

//---------------------------------------------------------------------------------------------------------------
// Name: AimBall()
// Desc: creates the aiming ball used to indicate top/backspin
//
void GameObjects::AimBall() {

	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glTranslated(-22.5,-1.0,0.0);
	glutSolidSphere(2.0, 20.0,20.0);
	glPopMatrix();

} //AimBall()

//---------------------------------------------------------------------------------------------------------------
// Name: NextBall()
// Desc: creates the next ball that must be hit
//
void GameObjects::NextBall() {

	glPushMatrix();
	glColor3f(m_FiniteStateMachine.m_colour.fRed,m_FiniteStateMachine.m_colour.fGreen,m_FiniteStateMachine.m_colour.fBlue); //use the FSM to determine the colour of the next ball
	glTranslated(0.0,-1.0,-22.4);
	glutSolidSphere(1.5, 20.0,20.0);
	glPopMatrix();

} //NextBall()

//---------------------------------------------------------------------------------------------------------------
// Name: AimDot()
// Desc: creates the aiming dot used to indicate top/backspin on the aiming ball
//
void GameObjects::AimDot() {
	
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glColor3f(0.0,0.0,0.0);
	glVertex3f(m_vecPoint.m_fX, m_vecPoint.m_fY, m_vecPoint.m_fZ);	//the position of the dot varies dependant on player input
	glEnd();
	glFlush();

} //AimDot()

//---------------------------------------------------------------------------------------------------------------
// Name: AimLine()
// Desc: creates the aiming line used to indicate top/backspin
//
void GameObjects::AimLine() {

	glLineWidth(1.0);
	glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
	glVertex3f(m_CBalls[WHITE].m_vecPosition.m_fX,-1,m_CBalls[WHITE].m_vecPosition.m_fZ);	//start point is the location of the centre of the cue ball
    glVertex3f(m_vecAimLine.m_fX,m_vecAimLine.m_fY-2,m_vecAimLine.m_fZ);					//end point is determined by using the GetCircumPoints method in DrawGLScene
    glEnd();

} //AimLine()

//---------------------------------------------------------------------------------------------------------------
// Name: PowerGauge()
// Desc: creates the power bar used to indicate how strong you want to hit the cue ball
//
void GameObjects::PowerGauge() {

	glLineWidth(10.0);
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(22.0,0.0,-18.0);							//start of the line
	glVertex3f(22.0,0.0,-18.0 + (m_fForceCue*25));		//end point is determined by the value of m_fForceCue which varies dependant on player input
	glEnd();

} //PowerGauge()

//---------------------------------------------------------------------------------------------------------------
// Name: InitObjects()
// Desc: initialise game objects at the beggining of the game
//
int GameObjects::InitObjects() {

	//initialise balls
	for(int i = 0; i < NUMBALLS; i++) {									//set the relevant ball statuses

		m_CBalls[i].m_bPocketed		= false;							//intially no balls have been potted
		m_CBalls[i].m_bOutOfPlay	= false;							//all balls are in play
		m_CBalls[i].m_iID			= i;								//assigning the ID's of the balls
		m_CBalls[i].m_vecVelocity	= Vector3(0.0f,0.0f,0.0f);			//all balls are stationary
	}

	m_CBalls[WHITE].m_vecPosition	= Vector3(10.0f,-1.0f,0.0f);		//initialise the positions of the balls
	m_CBalls[RED].m_vecPosition		= Vector3(-10.0f,-1.0f,0.0f);
	m_CBalls[BLUE].m_vecPosition	= Vector3(-11.4f,-1.0f,0.75f);
	m_CBalls[YELLOW].m_vecPosition	= Vector3(-11.4f,-1.0f,-0.75f);
	m_CBalls[GREEN].m_vecPosition	= Vector3(-12.8f,-1.0f,-1.5f);
	m_CBalls[ORANGE].m_vecPosition	= Vector3(-12.8f,-1.0f,1.5f);
	m_CBalls[PURPLE].m_vecPosition	= Vector3(-14.2f,-1.0f,0.75f);
	m_CBalls[BROWN].m_vecPosition	= Vector3(-14.2f,-1.0f,-0.75f);
	m_CBalls[PINK].m_vecPosition	= Vector3(-15.6f,-1.0f,0.0f);
	m_CBalls[BLACK].m_vecPosition	= Vector3(-12.8f,-1.0f,0.0f);

	//pockets
	for(int i = 0; i < NUMPOCKETS; i++)
		m_CPockets[i].m_fRadius	= 1.2f;
		
	m_CPockets[UPLEFT].m_vecPosition	= Vector3(-20.0f,0.0f,18.5f);	//initialise the position of the pockets
	m_CPockets[UPMID].m_vecPosition		= Vector3(0.0f,0.0f,18.5f);
	m_CPockets[UPRIGHT].m_vecPosition	= Vector3(20.0f,0.0f,18.5f);
	m_CPockets[LOWLEFT].m_vecPosition	= Vector3(-20.0f,0.0f,-18.5f);
	m_CPockets[LOWMID].m_vecPosition	= Vector3(0.0f,0.0f,-18.5f);
	m_CPockets[LOWRIGHT].m_vecPosition	= Vector3(20.0f,0.0f,-18.5f);

	//other initialisations
	m_vecPoint = Vector3(-22.5f,-5.0f,0.0f);							//initialise the position of the aiming dot
	m_CBalls[WHITE].m_fCoRest = 0.90f;									//initialise/reset the coefficient of restitution

	return true;

} //InitObjects()

//---------------------------------------------------------------------------------------------------------------
// Name: GetCircumPoints()
// Desc: finds points on the circumference of a circle, given its radius, origin and angle
//
Vector3 GameObjects::GetCircumPoints(float radius, Vector3 pos, float radial) {

	Vector3 a;
	a.m_fX = pos.m_fX + radius * sin(radial*PI/180);
	a.m_fY = pos.m_fY;
	a.m_fZ = pos.m_fZ + radius * cos(radial*PI/180);
	return a;

} //GetCircumPoints()

//---------------------------------------------------------------------------------------------------------------
// Name: GetSpherePoints()
// Desc: finds points on the surface of a sphere, given its radius, origin longtitude and latitude
//
Vector3 GameObjects::GetSpherePoints(float radius, Vector3 pos, float radial, float elevation) {

	float i = (sin(elevation*PI/180) * sin(radial*PI/180));
	float j = cos(elevation*PI/180);
	float k = (sin(elevation*PI/180) * cos(radial*PI/180));
	Vector3 a;
	a.m_fX = pos.m_fX + radius * i;
	a.m_fY = pos.m_fY + radius * j;
	a.m_fZ = pos.m_fZ + radius * k;

	return a;

} //GetSpherePoints()

//---------------------------------------------------------------------------------------------------------------
// Name: WorkoutVel()
// Desc: calculate velocity of the cue ball using the concept of impulse
//
void GameObjects::WorkoutVel() {

	m_CBalls[WHITE].WorkOutVelocity(m_fForceCue, m_fAngle);

} //WorkoutVel()

//---------------------------------------------------------------------------------------------------------------
// Name: BallMoving()
// Desc: checks if any balls are moving
//
void GameObjects::BallMoving() {

	for(int i = 0 ; i < NUMBALLS; i++)
		m_CBalls[i].BallMoving();

} //BallMoving()

//---------------------------------------------------------------------------------------------------------------
// Name: UpdateMovingBalls()
// Desc: checks if any balls are moving
//
void GameObjects::UpdateMovingBalls() {

	for(int i = 0; i < NUMBALLS; i++)
		m_CBalls[i].UpdateMovingBalls(m_fCOFr);

} //UpdateMovingBalls()

//---------------------------------------------------------------------------------------------------------------
// Name: BallStationary()
// Desc: checks to see when all balls are stationary
//
bool GameObjects::BallStationary() {

	for(int i = 0; i < NUMBALLS; i++) {

		if(m_CBalls[i].m_bMoving)
			return false;
	}
	return true;

} //BallStationary()

//---------------------------------------------------------------------------------------------------------------
// Name: RailCollision()
// Desc: checks to see when a ball collides with the table rails
//
void GameObjects::RailCollision() {

	for(int i = 0; i < NUMBALLS; i++)
		m_CBalls[i].RailCollision();

} //RailCollision()

//---------------------------------------------------------------------------------------------------------------
// Name: PocketCollision()
// Desc: checks to see when a ball collides with the table pockets
//
void GameObjects::PocketCollision() {

	for(int i = 0; i < NUMBALLS; i++) {						//loop through the balls

		for(int j = 0; j < NUMPOCKETS; j++)					//loop through the pockets
			m_CBalls[i].BallPocketCollision(m_CPockets[j]);	//check for collsions between a ball and all pockets, then repeat process with another ball		
	}

} //PocketCollision()

//---------------------------------------------------------------------------------------------------------------
// Name: BallBallCollision()
// Desc: checks to see when a ball collides with another ball
//
bool GameObjects::BallBallCollision() {

	for(int i = 0; i < NUMBALLS; i++) {								//loop through the balls to find the 1st ball to compare

		for(int j = NUMBALLS; j > 0; j--) {							//loop through the balls to find the 2nd ball to compare

			if(i != j) {											//if the two balls are equal skip the check. i.e. you dont want to check if a ball collides with itself

				if(m_CBalls[i].BallCollision(m_CBalls[j])) {		//check for collisions between 2 balls here

					m_FiniteStateMachine.m_bAnyBallHit = true;		//a collision has occurred so this becomes true
					return true;
				}

			} //end if

		} //end nested for

	} //end for

	if(!BallStationary() && !m_FiniteStateMachine.m_bHitFirstBall)	//if the 1st ball has not been hit, then no balls have been hit
		m_FiniteStateMachine.m_bAnyBallHit = false;

	return false;

} //BallBallCollision()

//---------------------------------------------------------------------------------------------------------------
// Name: BallBallResponse()
// Desc: resolves ball ball collisions using elastic collisions equation
//
void GameObjects::BallBallResponse() {

	//check to see which balls have collided
	int ballRep1 = 0,ballRep2 = 0;
	bool skip = false;

	for(int i = 0; i < NUMBALLS; i++) {	//loop through the balls to find any that have collided

		if(m_CBalls[i].m_bCollided) {	//once a ball has been found, assign it to the appropriate ballRep (ball response) flag

			if(!skip) {

				ballRep1 = i;
				skip = true;			//once the 1st ball has been assigned, skip this step and move on to assign the 2nd ball
			}
			else {						//assign the 2nd ball here

				ballRep2 = i;
				skip = false;			//reset the skip check for the next loop through
				i = NUMBALLS;			//exit the loop once 2 balls have been found, perform the collisions response with the 2 balls
			} //end if-else
		} //end if
	} // end for

	//fixes the bug found in build 3.4.6:
	//-Incorrect collision response when a higher numbered ball collides with a lower numbered ball.
	//CAUSE: occurs when the speed of ballRep1 is less than that of ballRep2
	if(m_CBalls[ballRep1].m_vecVelocity.Magnitude() < m_CBalls[ballRep2].m_vecVelocity.Magnitude()) {	//swap the values of the bellRep if this is true

		int temp = ballRep1;
		ballRep1 = ballRep2;
		ballRep2 = temp;
	}

	//check if the 1st ball hit is the correct ball
	if(!m_FiniteStateMachine.m_bHitFirstBall) {						//the first ball flag is resets everytime the balls are stationary

		if(ballRep1 == 0 || ballRep2 == 0) {						//if the white ball was involved in a collision

			if(ballRep1 == 0) {										//if ballRep1 was the white ball

				if(ballRep2 != m_FiniteStateMachine.m_iNextBall) {	//if ballRep2 is not the next ball that needs to be hit, then a foul has occurred
					
					m_FiniteStateMachine.m_bHitWrongBall = true;	//the wrong ball was hit. this bool will reset when the appropriate gamestate has been set
					m_FiniteStateMachine.m_bHitFirstBall = true;	//the white has hit the 1st ball so this is true. will be false again when all balls are stationary
				}
			}
			else {													//if ballRep1 isn't the white, then ballRep2 is

				if(ballRep1 != m_FiniteStateMachine.m_iNextBall) {	//perform the same checks as above but for ballRep1

					m_FiniteStateMachine.m_bHitWrongBall = true;
					m_FiniteStateMachine.m_bHitFirstBall = true;
				}
			} //end if-else

			m_FiniteStateMachine.m_bHitFirstBall = true;			//the first ball has been hit if this if statement has to execute, so we make sure to set this to true no matter what

		} //end nested if
	} //end if


	//collision response using 2-dimensional inelastic collisions here
	m_CBalls[ballRep1].BallCollisionResponse(m_CBalls[ballRep2]);

	//after the collision no balls are in contact, thus update their status
	for(int i = 0; i < NUMBALLS; i++)
		m_CBalls[i].m_bCollided = false;

} //ballBallResponse()

//---------------------------------------------------------------------------------------------------------------
// Name: UseFSM()
// Desc: use the finite state machine class to determine the gamestate
//
void GameObjects::UseFSM() {

	for(int i = 1; i < NUMBALLS; i++) {							//find the next ball to be pocketed
		
		if(!m_CBalls[i].m_bPocketed) {

			m_FiniteStateMachine.SetNextBallColour(m_CBalls[i]);
			i = NUMBALLS;										//once the next ball has been found, exit loop
		}
	}

	for(int i = 1; i < NUMBALLS; i++) {							//find out how many balls have been pocketed
		
		if(m_CBalls[i].m_bPocketed && !m_CBalls[i].m_bOutOfPlay)//needs 2 conditions otherwise m_iBallsLeft will always decrement
			m_FiniteStateMachine.m_iCurrentBalls--;
	}

	//Check for fouls first, then player turns, then winning/losing conditions
	//=============================================================== Check for fouls ===============================================================
	if(m_CBalls[WHITE].m_bPocketed) {											//foul if the white is pocketed

		m_FiniteStateMachine.SetState(m_FiniteStateMachine.POCKETWHITEFOUL);
	}
	else if(m_FiniteStateMachine.m_bHitWrongBall) {								//foul if the wrong ball has been hit

		m_FiniteStateMachine.SetState(m_FiniteStateMachine.HITWRONGBALLFOUL);
		m_FiniteStateMachine.m_bHitWrongBall = false;							//update this bool once the gamestate has been set
	}
	else if(!m_FiniteStateMachine.m_bAnyBallHit) {								//foul if no balls were hit

		m_FiniteStateMachine.SetState(m_FiniteStateMachine.NOBALLHITFOUL);
		m_FiniteStateMachine.m_bAnyBallHit = true;								//update this bool once the gamestate has been set
	}

	//============================================================== Check player turns ==============================================================
	if(m_FiniteStateMachine.m_iPlayer == 2 && m_FiniteStateMachine.m_bFoul) {			//update player turns after a foul

		m_FiniteStateMachine.SetState(m_FiniteStateMachine.P2SHOOT);
	}
	else if(m_FiniteStateMachine.m_iPlayer == 1 && m_FiniteStateMachine.m_bFoul) {		//update player turns after a foul

		m_FiniteStateMachine.SetState(m_FiniteStateMachine.P1SHOOT);
	}
	else if(m_FiniteStateMachine.m_iCurrentBalls != m_FiniteStateMachine.m_iBallsLeft) { //players keep their turn as long as they pot a ball legally

		if(m_FiniteStateMachine.m_iPlayer == 1 && !m_FiniteStateMachine.m_bInstaLose) {

			m_FiniteStateMachine.SetState(m_FiniteStateMachine.P1SHOOT);
			m_FiniteStateMachine.m_iBallsLeft = m_FiniteStateMachine.m_iCurrentBalls;
		}
		else if(m_FiniteStateMachine.m_iPlayer == 2 && !m_FiniteStateMachine.m_bInstaLose) {

			m_FiniteStateMachine.SetState(m_FiniteStateMachine.P2SHOOT);
			m_FiniteStateMachine.m_iBallsLeft = m_FiniteStateMachine.m_iCurrentBalls;
		}
	}

	//=========================================================== Check winning conditions ===========================================================
	if(m_FiniteStateMachine.m_iCurrentBalls == 0)						//if all balls are pocketed, gameover
		m_FiniteStateMachine.SetState(m_FiniteStateMachine.GAMEOVER);
	else if(m_CBalls[BLACK].m_bPocketed)								//if the black is potted, gameover
		m_FiniteStateMachine.SetState(m_FiniteStateMachine.GAMEOVER);

	//=============================================================== Update game state ==============================================================
	if(!BallStationary() && m_FiniteStateMachine.GetState() == m_FiniteStateMachine.POCKETWHITEFOUL) {				//Display foul type

		m_FiniteStateMachine.m_bBallMoving = true;
		m_FiniteStateMachine.m_bInstaLose = true;																	//If the black is potted when a foul has occurred then the player who committed the foul loses instantly
		m_FiniteStateMachine.RenderBitmapString(-15.0,0.0,-23.0,GLUT_BITMAP_TIMES_ROMAN_24,"FOUL White Pocketed");
	}
	else if(!BallStationary() && m_FiniteStateMachine.GetState() == m_FiniteStateMachine.HITWRONGBALLFOUL) {		//Display foul type

		m_FiniteStateMachine.m_bBallMoving = true;
		m_FiniteStateMachine.m_bInstaLose = true;
		m_FiniteStateMachine.RenderBitmapString(-15.0,0.0,-23.0,GLUT_BITMAP_TIMES_ROMAN_24,"FOUL Hit Wrong Ball");
	}
	else if(!BallStationary()) {																					//display relevant game state

		m_FiniteStateMachine.m_bBallMoving = true;
		m_FiniteStateMachine.RenderBitmapString(15.0,0.0,-23.0,GLUT_BITMAP_TIMES_ROMAN_24,"Balls Moving");
	}
	else if(BallStationary()) {																						//change the gamestate and reset the bool checks when the balls have stopped moving

		m_FiniteStateMachine.m_bHitFirstBall = false;
		m_FiniteStateMachine.m_bBallMoving = false;

		if(m_FiniteStateMachine.GetState() != m_FiniteStateMachine.GAMEOVER)
			m_FiniteStateMachine.m_bInstaLose = false;

		m_FiniteStateMachine.CheckState();
	}

} //UseFSM()