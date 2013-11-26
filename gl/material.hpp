/*
 * material.hpp
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

#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include "common.hpp"

void loadMaterialFish()
{
	GLfloat ambient[4]  = {0.1, 0.1, 0.1, 1.0};
	GLfloat diffuse[4]  = {0.5, 0.5, 0.5, 1.0};
	GLfloat specular[4] = {0.5, 0.5, 0.2, 1.0};
	GLfloat emission[4] = {0.0, 0.0, 0.0, 1.0};
	GLfloat shininess = 20.0;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

#endif /* MATERIAL_HPP_ */
