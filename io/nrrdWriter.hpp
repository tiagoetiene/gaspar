#ifndef NRRDWRITER_HPP_
#define NRRDWRITER_HPP_

#include <fstream>
#include <string>

#include "writerUtils.hpp"
#include "structuredGrid.hpp"

namespace vnv
{

template <class T>
class nrrdWriter
{
public:

	//! @brief Writes a NRRD file
    //!
    //! This static function is responsible to write NRRD files.
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
    	std::string nhdrFileName = fileName + ".nhdr";
    	std::string rawFileName  = fileName + ".raw";

    	unsigned pos;
	    if((pos = fileName.rfind(".nhdr")) != std::string::npos &&
	    	fileName.size() - pos == 5)
	    {
	    	nhdrFileName = fileName;
	    	rawFileName.replace(rawFileName.find(".nhdr"), 5, "");
	    }

	    std::ofstream fileNRRD(nhdrFileName.c_str(), std::ios::out);
	    std::ofstream fileRAW(rawFileName.c_str(), std::ios::out |
	    										   std::ios::binary);


	    if(!fileNRRD.is_open())
	    {
	        std::cout << std::endl;
	        std::cout << "\tCouldn't create specified file '" << nhdrFileName;
	        std::cout << "'." << std::endl;
	        return 1;
	    }

	    if(!fileRAW.is_open())
	    {
	        std::cout << std::endl;
	        std::cout << "\tCouldn't create specified file '" << rawFileName;
	        std::cout << "'." << std::endl;
	        return 1;
	    }

		double di, dj, dk;
		di = grid.getDelta();
		dj = grid.getDelta();
		dk = grid.getDelta();

		std::vector<_real> mn(3), mx(3);

		grid.getLimits(mn[0], mn[1], mn[2], mx[0], mx[1], mx[2]);

		pos = rawFileName.rfind("/");
	    unsigned samples;
	    grid.get(samples);
	    fileNRRD << "NRRD0001" << std::endl;
	    fileNRRD << "dimension: " << 3 << std::endl;
	    fileNRRD << "type: " << getTypeAsString(T()) << std::endl;
	    fileNRRD << "sizes: " << samples << " " << samples << " " << samples;
	    fileNRRD << std::endl;
	    fileNRRD << "spacings: " << dj << " " << di << " " << dk << std::endl;
	    fileNRRD << "endian: " << endianType << std::endl;
	    fileNRRD << "data file: " <<
			((pos != std::string::npos) ? rawFileName.substr(pos+1) : rawFileName)
				<< std::endl;
	    fileNRRD << "encoding: " << encoding << std::endl;
//	    fileNRRD << "# Box min: " << mn.x << " " << mn.y << " " << mn.z
//			<< std::endl;
//	    fileNRRD << "# Box max: " << mx.x << " " << mx.y << " " << mx.z
//			<< std::endl;

	    bool isLittleEndian = endianType == "little";
    	unsigned i, j, k;
    	for(k = 0; k < samples; ++k)
			for(j = 0; j < samples; ++j)
				for(i = 0; i < samples; ++i)
    			{
    				T value = (T)grid.get(i, j, k);
    				char* byte = reinterpret_cast<char*>(&value);
    				byte = (isLittleEndian) ? byte :
    					changeEndianness(byte, sizeof(T));

    				fileRAW.write(byte, sizeof(T));
    			}

	    fileNRRD.close();
	    fileRAW.close();

	    return 0;
    }

    static char* changeEndianness(char* byte, unsigned size)
    {
    	for(int i = 0; i < (int)(size * 0.5); ++i)
    	{
    		char c;
    		c= byte[i];
    		byte[i] = byte[size-1-i];
    		byte[size-1-i] = c;
    	}

    	return byte;
    }

    static void setLittleEndianness()
    {
    	endianType = "little";
    }

    static void setBigEndianness()
    {
    	endianType = "big";
    }

protected:
	static std::string endianType;
	static std::string encoding;
};

template <class T>
std::string
nrrdWriter<T>::endianType = "non-specified";

template <class T>
std::string
nrrdWriter<T>::encoding = "raw";


};

#endif /*NRRDWRITER_HPP_*/


