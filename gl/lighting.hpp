/*
 * lighting.hpp
 *
 *  Created on: Nov 5, 2009
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

#ifndef LIGHTING_HPP_
#define LIGHTING_HPP_

#include "common.hpp"

inline void initLighting()
{
	GLfloat ambientColor[] = {0.1, 0.1, 0.1, 1.0};
	GLfloat light0Diffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light0Specular[] = {0.5, 0.5, 1.0, 1.0};

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light0Specular);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light0Diffuse);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_RESCALE_NORMAL);
}

#endif /* LIGHTING_HPP_ */
