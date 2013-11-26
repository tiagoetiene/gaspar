/*
 * utils.hpp
 *
 *  Created on: Oct 12, 2008
 *      Author: etiene
 */

#ifndef WRITERUTILS_HPP_
#define WRITERUTILS_HPP_

#include <string>

inline
std::string getTypeAsString(int)
{
	return "int";
}
inline
std::string getTypeAsString(char)
{
	return "char";
}
inline
std::string getTypeAsString(unsigned char)
{
	return "uchar";
}
inline
std::string getTypeAsString(float)
{
	return "float";
}
inline
std::string getTypeAsString(double)
{
	return "double";
}

#endif /* WRITERUTILS_HPP_ */
