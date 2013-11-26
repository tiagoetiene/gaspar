/*
 * common.hpp
 *
 *  Created on: Oct 27, 2009
 *      Author: etiene
 *
 *  This file is part of assignment-3.
 *
 *  assignment-3 is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  assignment-3 is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with assignment-3.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <cmath>
#include <GL/gl.h>
#include <GL/glui.h>


// OpenGL state variables
const GLuint WINDOW_WIDTH  = 1024;
const GLuint WINDOW_HEIGHT = 1024;
const GLuint WINDOW_POS_X  = 1280;
const GLuint WINDOW_POS_Y  = 100;
const char WINDOW_NAME[] = "Randomized grid";

GLint MainWindowId;

GLfloat CurrentModelview[16];
GLfloat LightPosition[4] = {1.0, 0.7, 2.0, 0.0};
GLfloat LightPosition1[4] = {-1.0, -0.7, -2.0, 0.0};
GLdouble RotX = 0.0;
GLdouble RotY = 0.0;

GLdouble Left   = -3.1;
GLdouble Bottom = -3.1;

GLdouble AspectRatio = 1.0;
GLdouble Near = 0.1;
GLdouble Far = 100.0;
GLdouble Fovy = 45.0;
GLdouble Eye[3] = {0.0, 0.0, 4.0};
GLdouble Focus[3] = {0.0, 0.0, 0.0};
GLdouble Up[3] = {0.0, 1.0, 0.0};



//Live variables
int ShowMenuLive = 0;
int ShowWireLive = 0;

GLUI_Checkbox* ShowWireCheckbox;



#endif /* COMMON_HPP_ */

