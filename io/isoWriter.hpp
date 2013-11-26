/*
 * isoWriter.hpp
 *
 *  Created on: Feb 16, 2010
 *      Author: etiene
 */

#ifndef ISOWRITER_HPP_
#define ISOWRITER_HPP_


#include <fstream>
#include <string>

#include "structuredGrid.hpp"

namespace vnv
{

template <class T>
class isoWriter
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
        std::string isoFileName = fileName + ".iso";

        unsigned pos;
        if((pos = fileName.rfind(".iso")) != std::string::npos &&
            fileName.size() - pos == 4)
        {
            isoFileName = fileName;
        }

        std::ofstream fileISO(isoFileName.c_str(), std::ios::out |
                std::ios::binary);


        if(!fileISO.is_open())
        {
            std::cout << std::endl;
            std::cout << "\tCouldn't create specified file '" << isoFileName;
            std::cout << "'." << std::endl;
            return 1;
        }


        _real mnx, mny, mnz, mxx, mxy, mxz;

        grid.getLimits(mnx, mny, mnz, mxx, mxy, mxz);

        unsigned samplesN;
        grid.get(samplesN);

        char* byte = reinterpret_cast<char*>(&samplesN);
        fileISO.write(byte, sizeof(unsigned));
        fileISO.write(byte, sizeof(unsigned));
        fileISO.write(byte, sizeof(unsigned));


        T mnxf = mnx;
        T mnyf = mny;
        T mnzf = mnz;
        T mxxf = mxx;
        T mxyf = mxy;
        T mxzf = mxz;


        byte = reinterpret_cast<char*>(&(mnxf));
        fileISO.write(byte, sizeof(T));
        byte = reinterpret_cast<char*>(&(mxxf));
        fileISO.write(byte, sizeof(T));
        byte = reinterpret_cast<char*>(&(mnyf));
        fileISO.write(byte, sizeof(T));
        byte = reinterpret_cast<char*>(&(mxyf));
        fileISO.write(byte, sizeof(T));
        byte = reinterpret_cast<char*>(&(mnzf));
        fileISO.write(byte, sizeof(T));
        byte = reinterpret_cast<char*>(&(mxzf));
        fileISO.write(byte, sizeof(T));

        unsigned i, j, k;
        for(i = 0; i < samplesN; ++i)
            for(j = 0; j < samplesN; ++j)
                for(k = 0; k < samplesN; ++k)
                {
                    T value = grid.get(i, j, k);
                    char* byte = reinterpret_cast<char*>(&value);
                    fileISO.write(byte, sizeof(T));
                }
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

};

};



#endif /* ISOWRITER_HPP_ */
