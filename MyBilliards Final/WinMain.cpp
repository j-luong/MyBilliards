#include "global.h"

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active=true;		// Window Active Flag Set To true By Default
bool	fullscreen=true;	// Fullscreen Flag Set To Fullscreen Mode By Default

HDC		hDC = NULL;			// Private GDI Device Context

GameObjects GObjects;

LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active=true;						// Program Is Active
			}
			else
			{
				active=false;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = true;					// If So, Mark It As true
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = false;					// If So, Mark It As false
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));	// LoWord=Width, HiWord=Height
			return 0;										// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done=false;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=false;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("Jason Luong:11277565 FINAL YEAR PROJECT",1024,768,16,fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while(!done)									// Loop That Runs While done=false
	{
		static DWORD currentTime = 0;	// time since the system has started
		static DWORD lastTime = 0;		// time since this function was last called
		static DWORD newTime = 0;		// the amount of time it takes between function calls
		static DWORD timeElapsed = 0;	// the amount of time gone by since this program started

		currentTime = GetTickCount();		// get the current system time
		newTime = currentTime - lastTime;	// find out how long its taken since this function was last called
		lastTime = currentTime;				// update the lastTime to currentTime for next cycle
		timeElapsed += newTime;				// increase the amount of time the program started

		if(timeElapsed >= 0.5)			//update the game every x milliseconds
		{
			timeElapsed = 0;
		

			if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
			{
				if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
				{
					done=true;							// If So done=true
				}
				else									// If Not, Deal With Window Messages
				{
					TranslateMessage(&msg);				// Translate The Message
					DispatchMessage(&msg);				// Dispatch The Message
				}
			}
			else										// If There Are No Messages
			{
				// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
				if (active)								// Program Active?
				{
					if (keys[VK_ESCAPE])				// Was ESC Pressed?
					{
						keys[VK_ESCAPE]=false;			// If So Make Key false

						// Ask The User If They Want To Quit
						if(MessageBox(NULL,"Are you sure you want to quit?", "Quit?",MB_YESNO|MB_ICONWARNING)== IDYES)
							done=true;					// ESC Signalled A Quit
						else
							done=false;
					}
					else								// Not Time To Quit, Update Screen
					{
							DrawGLScene();					// Draw The Scene
							SwapBuffers(hDC);				// Swap Buffers (Double Buffering)
					}
				}

				//=================================== GAME CONTROLS ===================================
				if (keys[VK_F1])						// Is F1 Being Pressed?
				{
					keys[VK_F1]=false;					// If So Make Key false
					KillGLWindow();						// Kill Our Current Window
					fullscreen=!fullscreen;				// Toggle Fullscreen / Windowed Mode
					// Recreate Our OpenGL Window
					if (!CreateGLWindow("Jason Luong:11277565 FINAL YEAR PROJECT",1024,768,16,fullscreen))
					{
						return 0;						// Quit If Window Was Not Created
					}
				}

				static bool bPowMax = false;			// Set max/min limits for power bar animation
				static bool bPowMin = false;
				static int iPrevState = 0;				// Holding variable to store the game state, used when help menu displayed

				if (keys[VK_SPACE])						// Is Spacebar Being Pressed?
				{
					keys[VK_SPACE]=false;				// If So Make Key false

					if(GObjects.BallStationary())
						GObjects.WorkoutVel();			// Hit the cue ball if all balls are stationary
				}

				if (keys[VK_LEFT])						// Is Left Arrow Being Pressed?
				{
					if(GObjects.m_fAngle == 0.0f)  		// Rotate aim line to aim the ball
						GObjects.m_fAngle = 360.0f;
					else
						GObjects.m_fAngle-=0.5f;		//laptop
						//GObjects.m_fAngle-=0.5f;		//pc
				}

				if (keys[VK_RIGHT])						// Is Right Arrow Being Pressed?
				{
					if(GObjects.m_fAngle == 360.0f)		// Rotate aim line to aim the ball
						GObjects.m_fAngle = 0.0f;
					else
						GObjects.m_fAngle+=0.5f;		//laptop
						//GObjects.m_fAngle+=0.5f;		//pc
				}

				if (keys[VK_UP])						// Is Up Arrow Being Pressed?
				{

					if(!bPowMax) {						// Increase the force to hit the cue ball

						if(GObjects.m_fForceCue >= 0.75f) {

							GObjects.m_fForceCue = 0.75f;
							bPowMax = true;
						}
						else {

							GObjects.m_fForceCue += 0.009f;	//laptop
							//GObjects.m_fForceCue += 0.02f;	//pc
							bPowMin = false;
						}
					} //end if
				}

				if (keys[VK_DOWN])						// Is Down Arrow Being Pressed?
				{
					
					if(!bPowMin) {						// Decrease the force to hit the cue ball

						if(GObjects.m_fForceCue <= 0.02f) {

							GObjects.m_fForceCue = 0.02f;
							bPowMin = true;
						}
						else {

							GObjects.m_fForceCue -= 0.009f;	//laptop
							//GObjects.m_fForceCue -= 0.02f;	//pc
							bPowMax = false;
						}
					} //end if
				}

				static bool bSpinMax = false;		// Set max/min limits for aiming dot animation
				static bool bSpinMin = false;

				if (keys['T'])						// Is T Being Pressed?
				{
					keys['T']=false;				// If So Make Key false
					if(!bSpinMax) {					// Add Topspin

						if(GObjects.m_CBalls[WHITE].m_fCoRest > 0.30f) {

							GObjects.m_CBalls[WHITE].m_fCoRest -= 0.10f;
							GObjects.m_vecPoint.m_fZ += 0.2f;
							bSpinMin = false;
						}
						else {

							GObjects.m_CBalls[WHITE].m_fCoRest = 0.30f;
							GObjects.m_vecPoint.m_fZ = 1.0f;
							bSpinMax = true;
						}
					} //end if

				}

				if (keys['B'])						// Is B Being Pressed?
				{
					keys['B']=false;				// If So Make Key false
					if(!bSpinMin) {					// Add Backspin

						if(GObjects.m_CBalls[WHITE].m_fCoRest < 1.30f) {

							GObjects.m_CBalls[WHITE].m_fCoRest += 0.10f;
							GObjects.m_vecPoint.m_fZ -= 0.2f;
							bSpinMax = false;
						}
						else {

							GObjects.m_CBalls[WHITE].m_fCoRest = 1.30f;
							GObjects.m_vecPoint.m_fZ = -1.0f;
							bSpinMin = true;
						}
					} //end if

				}

				if (keys['H'])						// Is H Being Pressed?
				{
					keys['H']=false;				// If So Make Key false

					if(GObjects.m_FiniteStateMachine.GetState() != GObjects.m_FiniteStateMachine.HELP)	//if the current state is not HELP
						iPrevState = GObjects.m_FiniteStateMachine.GetState();							//store the previous state

					if(GObjects.BallStationary() && GObjects.m_FiniteStateMachine.GetState() != GObjects.m_FiniteStateMachine.HELP) {

						GObjects.m_FiniteStateMachine.SetState(GObjects.m_FiniteStateMachine.HELP);		//show the help screen if balls are stationary and the current state is not already HELP
					}
					else if(iPrevState != GObjects.m_FiniteStateMachine.HELP) {

						GObjects.m_FiniteStateMachine.SetState(iPrevState);								//return to the previous state if the current state is already HELP
					}
					
				}

				//=================================== END GAME CONTROLS ===================================

			} //end else
		} //end timer
	}//end while 

	// Shutdown
	KillGLWindow();									// Kill The Window
	return ((int)msg.wParam);						// Exit The Program
}