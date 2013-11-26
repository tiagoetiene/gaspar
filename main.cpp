#include <boost/program_options.hpp>

#include <omp.h>

#include <cstdlib>
#include <iostream>
#include <cstring>

#include "structuredGrid.hpp"
#include "criticalPoints.hpp"
#include "digitization.hpp"
#include "cases.hpp"

#include <io/writer.h>

#ifdef OPENGL
#include "openGL.hpp"
#endif

int N = 5;
int NN = 17 + 16;

typedef double Real;

vnv::structuredGrid<Real> grid(N);
vnv::structuredGrid<Real>* refined_grid;

template<typename _real>
bool computerInteriorGrid(const vnv::structuredGrid<_real>& grid,
                                vnv::structuredGrid<_real>& ref)
{
    _real x, y, z;
    int ii, jj, kk;
    vnv::Trilinear<_real> t;

    unsigned n;
    unsigned N;

    grid.get(n);
    ref.get(N);

    unsigned NN = ((N - 1) / (n-1)) + 1;
    _real delta = 1.0 / (NN - 1);

    for(unsigned i = 0; i < n-1; ++i)
    {
        ii = i * (NN - 1);
        for(unsigned j = 0; j < n-1; ++j)
        {
            jj = j * (NN - 1);
            for(unsigned k = 0; k < n-1; ++k)
            {
                kk = k * (NN - 1);

                t.setTrilinear(grid.get(i + 0, j + 0, k + 0),
                               grid.get(i + 1, j + 0, k + 0),
                               grid.get(i + 0, j + 1, k + 0),
                               grid.get(i + 1, j + 1, k + 0),
                               grid.get(i + 0, j + 0, k + 1),
                               grid.get(i + 1, j + 0, k + 1),
                               grid.get(i + 0, j + 1, k + 1),
                               grid.get(i + 1, j + 1, k + 1));

                for(unsigned p = 0; p < NN; ++p)
                {
                    x = delta * p;
                    for(unsigned q = 0; q < NN; ++q)
                    {
                        y = delta * q;
                        for(unsigned r = 0; r < NN; ++r)
                        {
                            z = delta * r;
                            ref.set(ii + p, jj + q, kk + r, t.evaluate(x, y, z));
                        }
                    }
                }
            }
        }
    }

    return true;
}

int main(int argc, char* argv[])
{
    using boost::program_options::value;
    boost::program_options::options_description desc("Options");
    boost::program_options::variables_map vm;

    desc.add_options()
            ("help",
             "Gaspar creates random grids with known topology.")
            ("format",
             value<std::string>()->default_value("nrrd"),
             "file format for output grid: iso, vtk, nrrd")
            ("filename",
             value<std::string>()->default_value("/tmp/grid"),
             "output grid filename")
            ("invariant",
             value<std::string>(),
             "file where topological invariants are going to be saved")
            ("refined",
             boost::program_options::bool_switch(),
             "save a high-resolution version of the random grid")
            ;

    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        return 0;
    }

    grid.setLimits(-1.0, -1.0, -1.0, 1.0, 1.0, 1.0);

    if(vm.count("invariant") == 0)
    {
        vnv::random_grid(grid);
        vnv::write(grid, vm["filename"].as<std::string>(), vm["format"].as<std::string>());
    }
    if(vm.count("invariant") != 0)
    {
        refined_grid = new vnv::structuredGrid<Real>(NN);
        refined_grid->setLimits(-1.0, -1.0, -1.0, +1.0, +1.0, +1.0);
        refined_grid->set(std::numeric_limits<Real>::max());

        vnv::TrilinearCases cases;
        bool isThereAmbiguity = false;
        unsigned attempts = 0;
        unsigned refinements = 0;
        do
        {
            if(isThereAmbiguity and ++refinements < 4)
                NN = NN + (NN - 1);
            else
            {
                std::cout << "# of attempts: " << ++attempts << "\r" << std::flush;
                vnv::random_grid(grid);

                NN = N + (N - 1);
                refinements = 0;
            }

            if(refined_grid != 0)
                delete refined_grid;
            refined_grid = new vnv::structuredGrid<Real>(NN);
            refined_grid->setLimits(-1.0, -1.0, -1.0, +1.0, +1.0, +1.0);
            computerInteriorGrid(grid, *refined_grid);
        }
        while((isThereAmbiguity = cases.isThereAnAmbiguousCell(*refined_grid)));
        std::cout << std::endl;


        NN = NN+(NN-1);
        delete refined_grid;
        refined_grid = new vnv::structuredGrid<Real>(NN);
        refined_grid->setLimits(-1.0, -1.0, -1.0, +1.0, +1.0, +1.0);
        computerInteriorGrid(grid, *refined_grid);

        vnv::structuredGrid<int> digitized(NN);
        vnv::structuredGrid<int> bdry(NN+1);
        bdry.set(0);

        vnv::digitize(*refined_grid, digitized);
        vnv::markBoundary(digitized, bdry);
        std::vector<int> genus = vnv::computeGenus(bdry, digitized);
        std::ofstream f(vm["invariant"].as<std::string>(), std::ios::out);

//        f << "components: " << genus.size() << std::endl;
//        f << "genus: ";
        int euler = 0;
        for(const auto g : genus)
        {
//            f << g << " ";
            euler += 2 - 2*g;
        }
//        f << std::endl;
        f << "euler: " << euler << std::endl;
        f.close();

        vnv::write(grid, vm["filename"].as<std::string>(), vm["format"].as<std::string>());
        if(vm["refined"].as<bool>())
            vnv::write(*refined_grid, vm["filename"].as<std::string>()+"-refined", vm["format"].as<std::string>());

        //OpenGL
#ifdef RENDERING
        vnv::Digitized = &digitized;
        vnv::Boundary = &bdry;
        vnv::mainLoop(argc, argv);
#endif
    }

    return 0;
}
