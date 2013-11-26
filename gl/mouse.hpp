/*
 * mouse.hpp
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

#ifndef MOUSE_HPP_
#define MOUSE_HPP_

extern GLdouble RotX;
extern GLdouble RotY;

bool Dragging = false;

static int lastX = 0, lastY = 0;
static int dy = 0;
inline void mouseMotion(int x, int y)
{
	if(Dragging)
	{
		if(dy - y > 0.0)
		{
			Eye[2] += 0.05;
			Left -= 0.05;
			Bottom -= 0.05;
		}
		else
		{
			Eye[2] -= 0.05;
			Left += 0.05;
			Bottom += 0.05;
		}
		dy = y;
	}
	else
	{
		if(lastX == 0)
			lastX = x;
		if(lastY == 0)
			lastY = y;

		RotY = 0.3 * ((GLfloat)x - (GLfloat)lastX);
		RotX = 0.3 * ((GLfloat)y - (GLfloat)lastY);
		lastX = x;
		lastY = y;
	}


	 glutPostRedisplay();
}

inline void mouse(int button, int state, int x, int y)
{
	lastX = 0;
	lastY = 0;

	if (button == GLUT_RIGHT_BUTTON)
	{
		if(state == GLUT_DOWN)
		{
			dy = y;
			Dragging = true;
		}
		else if(state == GLUT_UP)
		{
			dy = 0.0;
			Dragging = false;
		}
	}


	glutPostRedisplay();
}

#endif /* MOUSE_HPP_ */
