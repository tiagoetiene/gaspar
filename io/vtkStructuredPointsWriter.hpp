/*
 * vtkStructuredPointsWriter.hpp
 *
 *  Created on: Oct 12, 2008
 *      Author: etiene
 */

#ifndef VTKSTRUCTUREDPOINTSWRITER_HPP_
#define VTKSTRUCTUREDPOINTSWRITER_HPP_

#include <fstream>
#include <string>

#include "structuredGrid.hpp"
#include "writerUtils.hpp"

namespace vnv
{

template <class T>
class vtkWriter
{
public:

	//! @brief Writes a VTK Structured Points file
    //!
    //! This static function is responsible to a VTK Structured Points file
    //!
    //! @param mesh The mesh already allocated. Note that this function will
    //! fail case the mesh is not preallocated;
    //!
    //! @param fileName Name of the file to be written
    //!
    //! @return Returns the status of the writing process: 0 means success and
	//! any other value otherwise
	template<typename _real>
    static int Write(const vnv::structuredGrid<_real>& grid,
    		const std::string fileName)
    {
    	std::string vtkFileName = fileName + ".vtk";

    	unsigned pos;
	    if((pos = fileName.rfind(".vtk")) != std::string::npos &&
	    	fileName.size() - pos == 4)
	    	vtkFileName = fileName;

	    std::ofstream fileVTK(vtkFileName.c_str(), std::ios::out);

	    if(!fileVTK.is_open())
	    {
	        std::cout << std::endl;
	        std::cout << "\tCouldn't create specified file '" << vtkFileName;
	        std::cout << "'." << std::endl;
	        return 1;
	    }


		_real delta;

		delta = grid.getDelta();
		std::vector<_real> mn(3), mx(3);
		unsigned N;

		grid.getLimits(mn[0], mn[1], mn[2], mx[0], mx[1], mx[2]);
	    grid.get(N);

	    fileVTK << "# vtk DataFile Version 3.0" << std::endl;
	    fileVTK << "Generated with Meshchk for Vistrails" << std::endl;
	    fileVTK << "ASCII" << std::endl;
	    fileVTK << "DATASET STRUCTURED_POINTS" << std::endl;
	    fileVTK << "DIMENSIONS " << N << " " << N << " " << N << std::endl;
	    fileVTK << "SPACING " << delta  << " " << delta  << " " << delta  << std::endl;
	    fileVTK << "ORIGIN " << mn[0] << " " << mn[1] << " " << mn[2] << std::endl;
	    fileVTK << "POINT_DATA " << N * N * N << std::endl;
	    fileVTK << "SCALARS " << "ImageFile " << getTypeAsString(T()) << std::endl;
	    fileVTK << "LOOKUP_TABLE " << "default" << std::endl;

    	unsigned i, j, k;
    	for(k = 0; k < N; ++k)
			for(i = 0; i < N; ++i)
				for(j = 0; j < N; ++j)
    			{
    				T value = grid.get(i, j, k);
    				fileVTK << value << " ";
    				if((j+1) % 9 == 0)
    					fileVTK << std::endl;
    			}

	    fileVTK.close();

	    return 0;
    }
};

};

#endif /* VTKSTRUCTUREDPOINTSWRITER_HPP_ */
