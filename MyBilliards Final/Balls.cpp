#include "Balls.h"

//---------------------------------------------------------------------------------------------------------------
// Name: Balls()
// Desc: default constructor
//
Balls::Balls() {

	m_vecVelocity = Vector3(0.0f,0.0f,0.0f);
	m_vecFriction = Vector3(0.0f,0.0f,0.0f);

	m_fMass		= 0.16f;
	m_fRadius	= 0.70f;

	m_iID		= 0;

	m_fPI		= 3.14159265358979323846264338327950288419716939937510f;
	m_fGrav		= 9.81f;
	m_fCoRest	= 0.90f;

	m_bMoving	= false;
	m_bCollided	= false;
	m_bPocketed = false;
	m_bOutOfPlay= false;

} //Balls()

//---------------------------------------------------------------------------------------------------------------
// Name: ~Balls()
// Desc: default destructor
//
Balls::~Balls() {

} //~Balls()

//---------------------------------------------------------------------------------------------------------------
// Name: CreateBall()
// Desc: creates the ball object
//
void Balls::CreateBall(ColourOGL colour) {

	glPushMatrix();
	glTranslated(m_vecPosition.m_fX, m_vecPosition.m_fY, m_vecPosition.m_fZ);
	m_vecPosition.m_fX += m_vecVelocity.m_fX;
	m_vecPosition.m_fZ += m_vecVelocity.m_fZ;
	glColor3f(colour.fRed, colour.fGreen, colour.fBlue);
	glutSolidSphere(m_fRadius, 20.0,20.0);
	glPopMatrix();

} //CreateBall()

//---------------------------------------------------------------------------------------------------------------
// Name: WorkOutVelocity()
// Desc: calculate velocity of the cue ball using the concept of impulse
//
void Balls::WorkOutVelocity(float fForceCue, float fAngle) {

	//use of the impulse equation to find translational SPEED
	float fVelocity = (fForceCue * 0.2f)/m_fMass;
	float fTheta;

	Vector3 vecVelocity;
	//Vector3 vecForceCue;

	//finding the vector components of the SPEED to find the translational VECLOCITY
	if(fAngle <= 90.0f) {

		vecVelocity = Vector3(fVelocity * sin(fAngle*m_fPI/180), 0.0f, fVelocity * cos(fAngle*m_fPI/180));	//the x (ISin(angle)) and z (ICos(angle)) component of the speed
		//vecForceCue	= Vector3(fVelocity * cos(fAngle*m_fPI/180), 0.0f, fVelocity * sin(fAngle*m_fPI/180));
		m_vecVelocity = vecVelocity;		//assign the cue velocity to the ball

	}
	//if the angle is greater than 90, subtract the correct amount to make it less than 90
	else if(fAngle > 90.0f && fAngle <= 180.0f) {

		fTheta = fAngle - 90.0f;					//subtract the correct amount
		vecVelocity = Vector3(fVelocity * cos(fTheta*m_fPI/180), 0.0f, (fVelocity * sin(fTheta*m_fPI/180)) * -1);
		//vecForceCue = Vector3((fVelocity * sin(fTheta*m_fPI/180))*-1, 0.0f, fVelocity * cos(fTheta*m_fPI/180));
		m_vecVelocity = vecVelocity;

	}
	else if(fAngle > 180.0f && fAngle <= 270.0f) {

		fTheta = fAngle - 180.0f;
		vecVelocity = Vector3((fVelocity * sin(fTheta*m_fPI/180)) * -1, 0.0f, (fVelocity * cos(fTheta*m_fPI/180)) * -1);
		//vecForceCue = Vector3((fVelocity * cos(fTheta*m_fPI/180)) * -1, 0.0f, (fVelocity * sin(fTheta*m_fPI/180)) * -1);
		m_vecVelocity = vecVelocity;

	}
	else {

		fTheta = fAngle - 270.0f;
		vecVelocity = Vector3((fVelocity * cos(fTheta*m_fPI/180)) * -1, 0.0f, fVelocity * sin(fTheta*m_fPI/180));
		//vecForceCue = Vector3((fVelocity * cos(fTheta*m_fPI/180)) * -1, 0.0f, fVelocity * sin(fTheta*m_fPI/180));
		m_vecVelocity = vecVelocity;

	} //end if-else

} //WorkOutVelocity()

//---------------------------------------------------------------------------------------------------------------
// Name: BallMoving()
// Desc: Checks if the ball is moving or not
//
void Balls::BallMoving() {

	if(m_vecVelocity.Magnitude() != 0.0f) {

		m_bMoving = true;

	}
	else {

		m_bMoving = false;

	}

} //BallMoving()

//---------------------------------------------------------------------------------------------------------------
// Name: UpdateMovingBalls()
// Desc: updates the balls velocities
//
void Balls::UpdateMovingBalls(float fCoFr) {

	if(m_bMoving) {

		//frictional force = umg
		float fFriction = (fCoFr * m_fMass) * m_fGrav;
		Vector3 frDirection, normFrDirection;

		frDirection = -1.0f * m_vecVelocity;			//frictional force acts opposite motion of balls
		normFrDirection = frDirection.Normalise();		//normalising value of force opposite motion
		m_vecFriction = fFriction * normFrDirection;	//applying the frictional force to balls

		//update the velocity
		m_vecVelocity.m_fX += m_vecFriction.m_fX;
		m_vecVelocity.m_fZ += m_vecFriction.m_fZ;

	} //end if

	if(m_vecVelocity.m_fX < 0.001 && m_vecVelocity.m_fX > -0.001 && m_vecVelocity.m_fZ < 0.001 && m_vecVelocity.m_fZ > -0.001) {

		m_vecVelocity = Vector3(0.0f,0.0f,0.0f);
		m_bMoving = false;

	} //end if

} //UpdateMovingBalls()

//---------------------------------------------------------------------------------------------------------------
// Name: RailCollision()
// Desc: checks for collisions between the ball and rail
//
void Balls::RailCollision() {	

	//collsion with right rail
	if(m_vecPosition.m_fZ < 17.10 && m_vecPosition.m_fZ > -17.10) {

		if(m_vecPosition.m_fX + m_fRadius >= 20) {	//ball-rail overlap?

			float fOverlap = 20 - (m_vecPosition.m_fX + m_fRadius);
			if(fOverlap < 0)
				m_vecPosition.m_fX += fOverlap;		//correct overlap

			m_vecVelocity.m_fX *= -1;				//reflect the ball back off the rail
			m_vecVelocity.m_fX *= 0.70f;			//energy loss colliding with the rail. the ball loses 30% of its momentum
			m_fCoRest = 0.90f;
		}
	}
	//safety check
	else if(m_vecPosition.m_fX > 19.0)				//stops the ball continuing on through the rails and ensures that it is pocketed
			m_bPocketed = true;

	//collision with left rail
	if(m_vecPosition.m_fZ < 17.10 && m_vecPosition.m_fZ > -17.10) {

		if(m_vecPosition.m_fX - m_fRadius <= -20) {

			float fOverlap = -20 - (m_vecPosition.m_fX - m_fRadius);
			if(fOverlap > 0)
				m_vecPosition.m_fX += fOverlap;

			m_vecVelocity.m_fX *= -1;
			m_vecVelocity.m_fX *= 0.70f;
			m_fCoRest = 0.90f;
		}
	}
	else if(m_vecPosition.m_fX < -19.0)
			m_bPocketed = true;

	//collision with top rail
	if((m_vecPosition.m_fX > -18.80 && m_vecPosition.m_fX < -1.18) || (m_vecPosition.m_fX > 1.18 && m_vecPosition.m_fX < 18.80)) {

		if(m_vecPosition.m_fZ + m_fRadius >= 18 && !m_bPocketed) { //!m_bPockected ensures the balls are translated to the corrected position once they've been pocketed

			float fOverlap = 18 - (m_vecPosition.m_fZ + m_fRadius);
			if(fOverlap < 0)
				m_vecPosition.m_fZ += fOverlap;

			m_vecVelocity.m_fZ *= -1;
			m_vecVelocity.m_fZ *= 0.70f;
			m_fCoRest = 0.90f;
		}
	}
	else if(m_vecPosition.m_fZ > 18)
		m_bPocketed = true;

	//collision with bottom rail
	if((m_vecPosition.m_fX > -18.80 && m_vecPosition.m_fX < -1.18) || (m_vecPosition.m_fX > 1.18 && m_vecPosition.m_fX < 18.80)) {

		if(m_vecPosition.m_fZ - m_fRadius <= -18) {

			float fOverlap = -18 - (m_vecPosition.m_fZ - m_fRadius);
			if(fOverlap > 0)
				m_vecPosition.m_fZ += fOverlap;

			m_vecVelocity.m_fZ *= -1;
			m_vecVelocity.m_fZ *= 0.70f;
			m_fCoRest = 0.90f;

		}
	}
	else if(m_vecPosition.m_fZ < -18)
		m_bPocketed = true;

} //RailCollisions()

//---------------------------------------------------------------------------------------------------------------
// Name: BallCollision()
// Desc: checks for collisions between the ball and ball
//
bool Balls::BallCollision(Balls &ball) {

	Vector3 vecBallDist;
	float fHypotinuse, fOverlap;

	//calculate the distance between balls
	vecBallDist = m_vecPosition - ball.m_vecPosition;
	fHypotinuse = vecBallDist.Magnitude();

	//check to see if the balls overlap
	fOverlap = fHypotinuse - (m_fRadius + ball.m_fRadius);

	//correct positions of balls if they overlap
	if(fOverlap < 0) {

		Vector3 fNormalisedDist = vecBallDist.Normalise();
		Vector3 vecOverlap = fOverlap * fNormalisedDist;
		m_vecPosition -= vecOverlap;

	}

	//collision check
	if(fHypotinuse <= (m_fRadius + ball.m_fRadius)) {

		m_bCollided	= true;
		ball.m_bCollided = true;
		return true;

	}
	else
		return false;

} //BallCollision()

//---------------------------------------------------------------------------------------------------------------
// Name: BallPocketCollision()
// Desc: checks for collisions between the ball and pocket
//
void Balls::BallPocketCollision(Balls &pocket) {

	Vector3 vecBallDist;
	float fHypotinuse, fOverlap;

	//calculate the distance between ball & pocket
	vecBallDist = m_vecPosition - pocket.m_vecPosition;
	fHypotinuse = vecBallDist.Magnitude();

	//check to see if the balls over the pocket enough
	fOverlap = fHypotinuse - (m_fRadius + pocket.m_fRadius);
	fOverlap *= -1.0f;

	if(fOverlap > m_fRadius)
		m_bPocketed = true;

} //BallPocketCollision()

//---------------------------------------------------------------------------------------------------------------
// Name: BallCollisionResponse()
// Desc: find the resultant velocities of two balls after they have collided
//
void Balls::BallCollisionResponse(Balls &ball) {

	//find the unit normal and unit tangent vectors of the balls that have collided
	Vector3 vecNormalVector		= ball.m_vecPosition - m_vecPosition;
	Vector3 vecUnitNormalVector = vecNormalVector.Normalise();
	Vector3 vecUnitTanVector	= Vector3(-vecUnitNormalVector.m_fZ, 0.0f, vecUnitNormalVector.m_fX);

	//calculate normal and tangential components of velocity
	float fInitVelNormBall1 = vecUnitNormalVector.Dot(m_vecVelocity);
	float fInitVelNormBall2 = vecUnitNormalVector.Dot(ball.m_vecVelocity);
	float fInitVelTanBall1	= vecUnitTanVector.Dot(m_vecVelocity);
	float fInitVelTanBall2	= vecUnitTanVector.Dot(ball.m_vecVelocity);

	//calculate tangential velocity of balls after collision
	float fVelTanBall1 = fInitVelTanBall1;
	float fVelTanBall2 = fInitVelTanBall2;

	//calculate normal velocity of balls after collision	
	//had to correct c++ here because it can't figure out 1D collisions using the equations properly
	//the following code is the implementation of the one-dimensional elastic collisions equations adapted to use coefficient of restitution
	
	float a = m_fMass * fInitVelNormBall1;
	float b = ball.m_fMass * fInitVelNormBall2;

	//final velocity in the normal direction of ball 2
	float c = ball.m_fMass * (m_fCoRest * (fInitVelNormBall2 - fInitVelNormBall1));
	float d = a + b + c;

	//final velocity in the normal direction of ball 1
	float j = m_fMass * (m_fCoRest * (fInitVelNormBall1 - fInitVelNormBall2));
	float k = a + b + j;

	float fTotalMass = m_fMass + ball.m_fMass;
	float fVelNormBall1, fVelNormBall2;

	//avoid division by 0
	if(d == 0.0f)
		fVelNormBall1 = 0.0f;
	else
		fVelNormBall1 = d/fTotalMass;
	if(k == 0.0f)
		fVelNormBall2 = 0.0f;
	else
		fVelNormBall2 = k/fTotalMass;

	//calculate resultant velocity of balls after collision
	Vector3 vecResNormVelBall1	= fVelNormBall1 * vecUnitNormalVector;
	Vector3 vecResTanVelBall1	= fVelTanBall1 * vecUnitTanVector;

	Vector3 vecResNormVelBall2	= fVelNormBall2 * vecUnitNormalVector;
	Vector3 vecResTanVelBall2	= fVelTanBall2 * vecUnitNormalVector;

	m_vecVelocity		= vecResNormVelBall1 + vecResTanVelBall1;
	ball.m_vecVelocity	= vecResNormVelBall2 + vecResTanVelBall2;

	m_bCollided		= false;
	ball.m_bCollided= false;

} //BallCollisionResponse()