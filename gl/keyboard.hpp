/*
 * keyboard.hpp
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

#ifndef KEYBOARD_HPP_
#define KEYBOARD_HPP_

#include "common.hpp"
#include <cstdlib>
#include <GL/glut.h>

extern GLdouble RotX;
extern GLdouble RotY;


inline void keyboard(unsigned char key, int x, int y)
{
	RotX = RotY = 0;
	switch(key)
	{
	case 'w':
	case 'W':
		ShowWireLive = !ShowWireLive;
		ShowWireCheckbox->set_int_val(ShowWireLive);
				glui->refresh();
		break;
	case 'q':
	case 'Q':
				exit(1);
				break;
	case 'z' :
	case 'Z' :
	{
			ShowMenuLive = (ShowMenuLive) ? 0 : 1;
			if(ShowMenuLive)
				glui->show();
			else
				glui->hide();
			break;
	}
	};
	 glutPostRedisplay();
}


#endif /* KEYBOARD_HPP_ */
