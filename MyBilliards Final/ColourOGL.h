#ifndef COLOUROGL_H
#define COLOUROGL_H

//holds a colour (0.0 - 1.0) used by OpenGL
struct ColourOGL {
	float fRed;
	float fGreen;
	float fBlue;

	void Set(float Red, float Green, float Blue) {
		fRed = Red;
		fGreen = Green;
		fBlue = Blue;
	}

	void Set(int Red, int Green, int Blue) {
		if (Red < 0) {

			fRed = 0.0f;
		}
		else if (Red > 255) {

			fRed = 1.0f;
		}
		else {

			fRed = Red/255.0f;
		}

		if (Green < 0) {

			fGreen = 0.0f;
		}
		else if (Green > 255) {

			fGreen = 1.0f;
		}
		else {

			fGreen = Green/255.0f;
		}
		if (Blue < 0) {

			fBlue = 0.0f;
		}
		else if (Blue > 255) {

			fBlue = 1.0f;
		}
		else {

			fBlue = Blue/255.0f;
		} //end if-else

	} //end Set()

}; //ColourOGL

#endif COLOUROGL_H //COLOUROGL_H