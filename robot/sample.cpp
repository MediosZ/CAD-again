// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>
#include <fl/glut.h>
#include "modelerglobals.h"


#define SOLID 1
#define WIRE 2

int moveX, moveY;
int spinX = 0;
int spinY = 0;
int des = 0;

// To make a SampleModel, we inherit off of ModelerView
class SampleModel : public ModelerView 
{
public:
    SampleModel(int x, int y, int w, int h, char *label) 
        : ModelerView(x,y,w,h,label) { }

    virtual void draw();
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createSampleModel(int x, int y, int w, int h, char *label)
{ 
    return new SampleModel(x,y,w,h,label); 
}

//»­Çò
void drawBall(double R, double x, double y, double z, int MODE) {
	glPushMatrix();
	glTranslated(x, y, z);
	if (MODE == SOLID) {
		glutSolidSphere(R, 20, 20);
	}
	else if (MODE == WIRE) {
		glutWireSphere(R, 20, 20);
	}
	glPopMatrix();
}

//»­°ëÇò
void drawHalfBall(double R, double x, double y, double z, int MODE) {
	glPushMatrix();
	glTranslated(x, y, z);
	GLdouble eqn[4] = { 0.0, 1.0, 0.0, 0.0 };
	glClipPlane(GL_CLIP_PLANE0, eqn);
	glEnable(GL_CLIP_PLANE0);
	if (MODE == SOLID) {
		glutSolidSphere(R, 20, 20);
	}
	else if (MODE == WIRE) {
		glutWireSphere(R, 20, 20);
	}
	glDisable(GL_CLIP_PLANE0);
	glPopMatrix();
}

//»­³¤·½Ìå
void drawSkewed(double l, double w, double h, double x, double y, double z, int MODE) {
	glPushMatrix();
	glScaled(l, w, h);
	glTranslated(x, y, z);
	if (MODE == SOLID) {
		glutSolidCube(1);
	}
	else if (MODE == WIRE) {
		glutWireCube(1);
	}
	glPopMatrix();
}

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out SampleModel
void SampleModel::draw()
{
    // This call takes care of a lot of the nasty projection 
    // matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
    ModelerView::draw();
	/*
	// draw the floor
	setAmbientColor(.1f,.1f,.1f);
	setDiffuseColor(COLOR_RED);
	glPushMatrix();
	glTranslated(-5,0,-5);
	drawBox(10,0.01f,10);
	glPopMatrix();

	// draw the sample model
	setAmbientColor(.1f,.1f,.1f);
	setDiffuseColor(COLOR_GREEN);*/
	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));
	
	/*
	glPushMatrix();
	glTranslated(-1.5, 0, -2);
	glScaled(3, 1, 4);
	drawBox(1,1,1);
	glPopMatrix();
	*/
	glPushMatrix();
	glRotated(spinX, 0, 1, 0);
	glRotated(spinY, 1, 0, 0);
	glTranslated(0, 0, des);
	//Í·
	setDiffuseColor(COLOR_RED);
	drawBall(1.5, 0, 0.5, 0, SOLID);
	//
	setDiffuseColor(COLOR_BLUE);
	drawSkewed(5, 4.4, 4, 0, -0.75, 0, SOLID);
	//¼ç°ò
	setDiffuseColor(1.0,0.5,0.2);
	drawHalfBall(1, 3.5, -2.1, 0, SOLID);
	drawHalfBall(1, -3.5, -2.1, 0, SOLID);
	//¸ì²²
	setDiffuseColor(1, 1, 1);
	drawSkewed(1, 3.2, 2, 3.5, -1.2, 0, SOLID);
	drawSkewed(1, 3.2, 2, -3.5, -1.2, 0, SOLID);
	//ÊÖ
	setDiffuseColor(0, 0.5, 0.3);
	drawBall(0.8, 3.5, -6, 0, SOLID);
	drawBall(0.8, -3.5, -6, 0, SOLID);
	//ÍÈ
	setDiffuseColor(1,1,1);
	drawSkewed(1.2, 3, 2, 1, -2.4, 0, SOLID);
	drawSkewed(1.2, 3, 2, -1, -2.4, 0, SOLID);
	//½Å
	setDiffuseColor(0,0.5,0.3);
	drawSkewed(1.5, 1, 3, 0.9, -9.2, 0, SOLID);
	drawSkewed(1.5, 1, 3, -0.9, -9.2, 0, SOLID);
	glPopMatrix();

		// draw cannon
		//glPushMatrix();
		//glRotated(VAL(ROTATE), 0.0, 1.0, 0.0);
		//glRotated(-90, 1.0, 0.0, 0.0);
		//drawCylinder(VAL(HEIGHT), 0.1, 0.1);

		//glTranslated(0.0, 0.0, VAL(HEIGHT));
		//drawCylinder(1, 1.0, 0.9);

		//glTranslated(0.0, 0.0, 0.5);
		//glRotated(90, 1.0, 0.0, 0.0);
		//drawCylinder(4, 0.1, 0.2);
		//glPopMatrix();

	glPopMatrix();
}

int main()
{
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, 
	// stepsize, defaultvalue)
    ModelerControl controls[NUMCONTROLS];
    controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
    controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 2);
    controls[ZPOS] = ModelerControl("Z Position", -10, 5, 0.1f, 0);
    controls[HEIGHT] = ModelerControl("Height", 1, 2.5, 0.1f, 1);
	controls[ROTATE] = ModelerControl("Rotate", -135, 135, 1, 0);
	controls[SOME] = ModelerControl("SOME", 0, 10, 1, 0);

    ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
    return ModelerApplication::Instance()->Run();
}
