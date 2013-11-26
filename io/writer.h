#ifndef WRITER_H
#define WRITER_H

#include <io/isoWriter.hpp>
#include <io/nrrdWriter.hpp>
#include <io/vtkStructuredPointsWriter.hpp>

namespace vnv
{

template<typename _real>
void write(vnv::structuredGrid<_real>& grid,
           const std::string &filename,
           const std::string &filetype)
{
    if(filetype == "vtk")
        vnv::vtkWriter<float>::Write(grid, filename);
    else if(filetype == "nrrd")
    {
        vnv::nrrdWriter<float>::setBigEndianness();
        vnv::nrrdWriter<float>::Write(grid, filename);
    }
    else if(filetype == "iso")
        vnv::isoWriter<float>::Write(grid, filename);
    else
        std::cerr << "Format not recognized!" << std::endl;
}

}

#endif // WRITER_H
