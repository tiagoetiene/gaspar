/*
 * criticalPoints.hpp
 *
 *  Created on: Feb 18, 2010
 *      Author: etiene
 */

#ifndef CRITICALPOINTS_HPP_
#define CRITICALPOINTS_HPP_

#include <iomanip>
#include <vector>
#include "trilinear.hpp"
#include "structuredGrid.hpp"

#include <boost/random.hpp>

boost::mt19937 generator(time(0));
boost::uniform_real<> uni_dist(0, 1);
boost::variate_generator<boost::mt19937&, boost::uniform_real<> > rnd(generator, uni_dist);

namespace vnv
{


template<typename Real>
inline
bool random_grid(vnv::structuredGrid<Real>& grid)
{
    unsigned N;
    grid.get(N);

    Real scale = 2.0;
    Real ref = 0.5 * scale * 1.00;

    grid.set(ref);

    for(unsigned i = 1; i < N-1; ++i)
        for(unsigned j = 1; j < N-1; ++j)
            for(unsigned k = 1; k < N-1; ++k)
                grid.set(i, j, k, (Real)(rnd() * scale - 0.5 * scale));
    return true;
}

}

#endif /* COMPUTECRITICALPOINTS_HPP_ */
