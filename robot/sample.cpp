// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>
#include <fl/glut.h>
#include <FL/Fl.H>
#include "modelerglobals.h"
#include "loader.h"


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
        : ModelerView(x,y,w,h,label) { 
	}

    virtual void draw();
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createSampleModel(int x, int y, int w, int h, char *label)
{ 
    return new SampleModel(x,y,w,h,label); 
}

//画球
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

//画半球
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

//画长方体
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


float Animate(float& curr) {
	float state;
	if (ModelerApplication::Instance()->direction) {
		state = ++curr;
		if (state >= 40) {
			ModelerApplication::Instance()->direction = false;
		}
	}
	else {
		state = --curr;
		if (state <= -40) {
			ModelerApplication::Instance()->direction = true;
		}
	}
	return state;
}

void drawSelf() {
	//身体
	setDiffuseColor(1,1,1);
	//glTranslatef(0, 0, 0);
	//drawSkewed(5, 10, 5, 0, 0, 0, SOLID);
	float state = 0;
	if (ModelerApplication::Instance()->m_animating) {
		//std::cout << "hello it is animating" << std::endl;
		state = Animate(ModelerApplication::Instance()->state);
		//std::cout << state << std::endl;
	}
	else{
		state = VAL(ROTATE);
	}

	
	glRotatef(state / 2, 0, 1, 0);
	drawBox(8, 10, 5);
	//头
	glPushMatrix();
		setDiffuseColor(COLOR_RED);
		glTranslatef(4, 9.0+VAL(SOME), 2.5);
		drawBall(VAL(SOME), 0, 0, 0, SOLID);
	glPopMatrix();

	//arm
	glPushMatrix();
		setDiffuseColor(COLOR_BLUE);
		glTranslatef(8.0, 9.0, 0.5);
		glRotatef(state, 1, 0, 0);
		glRotatef(VAL(ACT), 0, 0, 1);
		drawBox(2, -5, 4);
		glPushMatrix();
			glTranslatef(0, -5, 0);
			glRotated(35, -1, 0, 0);
			glRotatef(VAL(ACT)/1, 0, 0, 1);
			drawBox(2, -5, 4);
		glPopMatrix();
	glPopMatrix();
	glPushMatrix();
		setDiffuseColor(COLOR_BLUE);
		glTranslatef(-2.0, 9.0, 0.5);
		glRotatef(state, -1, 0, 0);
		drawBox(2, -5, 4);
		glPushMatrix();
			glTranslatef(0, -5, 0);
			glRotated(35, -1, 0, 0);
			drawBox(2, -5, 4);
		glPopMatrix();
	glPopMatrix();

	//leg
	glPushMatrix();
		setDiffuseColor(COLOR_BLUE);
		glTranslatef(6, 0, 0.5);
		glRotatef(state, -1, 0, 0);
		drawBox(2, -6, 4);
		glPushMatrix();
			glTranslatef(0, -5, 0);
			glRotated(15, 1, 0, 0);
			drawBox(2, -6, 4);
		glPopMatrix();
	glPopMatrix();
	glPushMatrix();
		setDiffuseColor(COLOR_BLUE);
		glTranslatef(0, 0, 0.5);
		glRotatef(state, 1, 0, 0);
		drawBox(2, -6, 4);
		glPushMatrix();
			glTranslatef(0, -5, 0);
			glRotated(15, 1, 0, 0);
			drawBox(2, -6, 4);
		glPopMatrix();
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
	//std::cout << Fl::event_text() << std::endl;

	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));
	if (!ModelerApplication::Instance()->m_show_ply_model) {
		drawSelf();
	}
	else {
		//ModelerApplication::Instance()->p->PLYdisplay();
		ModelerApplication::Instance()->p->PLYdisplay();
	}

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
    controls[ACT] = ModelerControl("Act", 0, 25, 1.0f, 0);
	controls[ROTATE] = ModelerControl("Rotate", -40, 40, 1, 0);
	controls[SOME] = ModelerControl("SOME", 3, 6, 0.1f, 3);

    ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
    return ModelerApplication::Instance()->Run();
}
