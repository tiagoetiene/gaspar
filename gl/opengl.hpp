/*
 * openGL.hpp
 *
 *  Created on: Feb 28, 2010
 *      Author: etiene
 */

#ifdef RENDERING

#ifndef OPENGL_HPP_
#define OPENGL_HPP_

#include <GL/gl.h>
#include <GL/glut.h>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "vis/common.hpp"
#include "vis/interface.hpp"
#include "vis/keyboard.hpp"
#include "vis/mouse.hpp"
#include "vis/lighting.hpp"
#include "vis/material.hpp"
#include "logging/logging.h"

namespace vnv
{

vnv::structuredGrid<int>* Digitized = 0;
vnv::structuredGrid<int>* Boundary = 0;


template<typename Int>
inline
void drawVoxels(const vnv::structuredGrid<Int>& d)
{
	unsigned N;
	d.getSamples(N);
	double delta = 1.0 / (N - 1.0);

	glPointSize(5);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
		for(unsigned i = 0; i < N ; ++i)
			for(unsigned j = 0; j < N; ++j)
				for(unsigned k = 0; k < N; ++k)
					if(d.getValue(i, j, k) == 1)
						glVertex3f(i*delta, j*delta, k*delta);
	glEnd();


//	glColor3f(0.0, 0.0, 0.0);
//	for(unsigned i = 1; i < N - 1; ++i)
//		for(unsigned j = 1; j < N - 1; ++j)
//			for(unsigned k = 1; k < N - 1; ++k)
//			{
//				if(d.getValue(i,j,k) == 1)
//				{
//					glPushMatrix();
//						glTranslatef(i*delta, j*delta, k*delta);
//						glutWireCube(delta);
//					glPopMatrix();
//				}
//			}
}

template<typename Int>
inline
void drawBoundary(const vnv::structuredGrid<Int>& d, const vnv::structuredGrid<Int>& dd)
{
	unsigned N;
	d.getSamples(N);
	double delta = 1.0 / (N - 2.0);

	glPushMatrix();
	glTranslatef(-0.5*delta,-0.5*delta,-0.5*delta);

	glPointSize(5);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
		for(unsigned i = 1; i < N - 1; ++i)
			for(unsigned j = 1; j < N - 1; ++j)
				for(unsigned k = 1; k < N - 1; ++k)
					if(d.getValue(i, j, k) == 2)
						glVertex3f(i*delta, j*delta, k*delta);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);

	GLenum type;
	if(!ShowWireLive)
	{
		glEnable(GL_LIGHTING);
		type = GL_QUADS;
	}
	else
	{
		glDisable(GL_LIGHTING);
		type = GL_LINE_LOOP;
	}
	for(unsigned i = 1; i < N - 1; ++i)
		for(unsigned j = 1; j < N - 1; ++j)
			for(unsigned k = 1; k < N - 1; ++k)
			{
				if(dd.getValue(i, j, k) == 1)
				{
					if(dd.getValue(i, j, k-1) == 0)
					{
						glBegin(type);
							glNormal3f(0.0, 0.0, -1.0);
							glVertex3f((i+0)*delta, (j+0)*delta, (k+0)*delta);
							glVertex3f((i+1)*delta, (j+0)*delta, (k+0)*delta);
							glVertex3f((i+1)*delta, (j+1)*delta, (k+0)*delta);
							glVertex3f((i+0)*delta, (j+1)*delta, (k+0)*delta);
						glEnd();
					}
					if(dd.getValue(i, j, k+1) == 0)
					{
						glBegin(type);
							glNormal3f(0.0, 0.0, +1.0);
							glVertex3f((i+0)*delta, (j+0)*delta, (k+1)*delta);
							glVertex3f((i+1)*delta, (j+0)*delta, (k+1)*delta);
							glVertex3f((i+1)*delta, (j+1)*delta, (k+1)*delta);
							glVertex3f((i+0)*delta, (j+1)*delta, (k+1)*delta);
						glEnd();
					}
					if(dd.getValue(i, j-1, k) == 0)
					{
						glBegin(type);
							glNormal3f(0.0, -1.0, 0.0);
							glVertex3f((i+0)*delta, (j+0)*delta, (k+0)*delta);
							glVertex3f((i+1)*delta, (j+0)*delta, (k+0)*delta);
							glVertex3f((i+1)*delta, (j+0)*delta, (k+1)*delta);
							glVertex3f((i+0)*delta, (j+0)*delta, (k+1)*delta);
						glEnd();
					}
					if(dd.getValue(i, j+1, k) == 0)
					{
						glBegin(type);
							glNormal3f(0.0, +1.0, 0.0);
							glVertex3f((i+0)*delta, (j+1)*delta, (k+0)*delta);
							glVertex3f((i+1)*delta, (j+1)*delta, (k+0)*delta);
							glVertex3f((i+1)*delta, (j+1)*delta, (k+1)*delta);
							glVertex3f((i+0)*delta, (j+1)*delta, (k+1)*delta);
						glEnd();
					}
					if(dd.getValue(i-1, j, k) == 0)
					{
						glBegin(type);
							glNormal3f(-1.0, 0.0, 0.0);
							glVertex3f((i+0)*delta, (j+0)*delta, (k+0)*delta);
							glVertex3f((i+0)*delta, (j+1)*delta, (k+0)*delta);
							glVertex3f((i+0)*delta, (j+1)*delta, (k+1)*delta);
							glVertex3f((i+0)*delta, (j+0)*delta, (k+1)*delta);
						glEnd();
					}
					if(dd.getValue(i+1, j, k) == 0)
					{
						glBegin(type);
							glNormal3f(+1.0, 0.0, 0.0);
							glVertex3f((i+1)*delta, (j+0)*delta, (k+0)*delta);
							glVertex3f((i+1)*delta, (j+1)*delta, (k+0)*delta);
							glVertex3f((i+1)*delta, (j+1)*delta, (k+1)*delta);
							glVertex3f((i+1)*delta, (j+0)*delta, (k+1)*delta);
						glEnd();
					}

				}
			}
	glPopMatrix();
}


inline
void drawScene()
{
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);

//	glDisable(GL_LIGHTING);
//	glPointSize(10.0);
//	glBegin(GL_POINTS);
//	glVertex3f(LightPosition[0], LightPosition[1], LightPosition[2]);
//	glEnd();
//	glPointSize(1.0);

	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);

	glPushMatrix();
	glTranslatef(-0.5, -0.5, -0.5);
		if(Digitized)
			drawVoxels(*Digitized);
		if(Boundary)
			drawBoundary(*Boundary, *Digitized);
	glPopMatrix();
}


inline
void redraw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	gluPerspective(Fovy, AspectRatio, Near, Far);
	glOrtho(Left, -Left, Bottom, -Bottom, Near, Far);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Eye[0], Eye[1], Eye[2],
			  Focus[0], Focus[1], Focus[2],
			  Up[0], Up[1], Up[2]);

	glPushMatrix();
		glLoadIdentity();
		glRotatef(RotX, 1.0, 0.0, 0.0);
		glRotatef(RotY, 0.0, 1.0, 0.0);
		glMultMatrixf(CurrentModelview);
		glGetFloatv(GL_MODELVIEW_MATRIX, CurrentModelview);
	glPopMatrix();

	glPushMatrix();
	{
		glMultMatrixf(CurrentModelview);
		drawScene();
	}
	glPopMatrix();
	RotX = RotY = 0.0;

	glutSwapBuffers();
}

inline
void reshape(GLsizei w, GLsizei h)
{
	if(h == 0) h = 1;
	glViewport(0, 0, w, h);

	AspectRatio = (GLdouble) w / (GLdouble) h;
}

inline
void initScene()
{
	glClearColor(0.2, 0.2, 0.2, 1.0);


	// Setting transformations
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, CurrentModelview);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


	// Lighting
	initLighting();



	glEnable(GL_DEPTH_TEST);
}

inline
void idle()
{
	glutSetWindow(MainWindowId);
	glutPostRedisplay();
}

inline
int mainLoop(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
	MainWindowId = glutCreateWindow(WINDOW_NAME);

	GLUI_Master.set_glutDisplayFunc(redraw);
	GLUI_Master.set_glutReshapeFunc(reshape);
	GLUI_Master.set_glutKeyboardFunc(keyboard);
	GLUI_Master.set_glutMouseFunc(mouse);
	GLUI_Master.set_glutIdleFunc(idle);
	glutMotionFunc(mouseMotion);

	initGlui();
	initScene();

	glutMainLoop();

    Time::stop();
    logging::indent.decrease();
    logging::debugf("* See you! Time elapsed: %f\n", Time::elapsedInSeconds());
	return 0;
}



};

#endif /* OPENGL_HPP_ */

#endif
