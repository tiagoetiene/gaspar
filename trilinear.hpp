/*
 * trilinear.hpp
 *
 *  Created on: Feb 18, 2010
 *      Author: etiene
 */

#ifndef TRILINEAR_HPP_
#define TRILINEAR_HPP_

#include <cmath>
#include <cassert>

namespace vnv
{

template<typename Real>
struct Trilinear
{
    union
    {
        struct
        {
            Real a, b, c, d, e, f, g, h;
        };
        Real C[8];
    };

    union
    {
        struct
        {
            Real v0, v1, v2, v3, v4, v5, v6, v7;
        };
        Real V[8];
    };


    /*!
     * p(x,y,z) = a * xyz + b * xy + c * xz + d * yz + e * x + f * y + g * z + h
     *
     */
    inline
    void setTrilinear(const Real _v0, const Real _v1,
                      const Real _v2, const Real _v3,
                      const Real _v4, const Real _v5,
                      const Real _v6, const Real _v7)
    {
        v0 = _v0; v1 = _v1; v2 = _v2; v3 = _v3;
        v4 = _v4; v5 = _v5; v6 = _v6; v7 = _v7;

        a = v7 - v3 - v5 - v6 + v1 + v2 + v4 - v0;
        b = v3 - v1 - v2 + v0;
        c = v6 - v2 - v4 + v0;
        d = v5 - v1 - v4 + v0;
        e = v1 - v0;
        f = v2 - v0;
        g = v4 - v0;
        h = v0;

        Real cube[2][2][2];
        cube[0][0][0] = v0;
        cube[1][0][0] = v1;
        cube[0][1][0] = v2;
        cube[1][1][0] = v3;
        cube[0][0][1] = v4;
        cube[1][0][1] = v5;
        cube[0][1][1] = v6;
        cube[1][1][1] = v7;
        for(int z = 0; z < 2; ++z)
            for(int y = 0; y < 2; ++y)
                for(int x = 0; x < 2; ++x)
                {
                    Real f = evaluate((Real)x, (Real)y, (Real)z);
                    if(fabsl(f - cube[x][y][z]) >= 1E-6)
                    {
                        std::cout << "x y z: ";
                        std::cout << x << " " << y << " " << z << std::endl;
                        std::cout << "f: " << f << std::endl;
                        std::cout << "cube: " << cube[x][y][z] << std::endl;
                        std::cout << fabsl(f - cube[x][y][z]) << std::endl;
                    }
                    assert(fabsl(f - cube[x][y][z]) < 1E-6);
                }
    }

    inline
    Real operator() (Real x, Real y, Real z) const
    {
        return evaluate(x, y, z);
    }

    inline
    Real evaluate(Real x, Real y, Real z) const
    {
        return a * x * y * z +
               b * x * y + c * y * z + d * x * z +
               e * x + f * y + g * z + h;
    }
};

}


#endif /* TRILINEAR_HPP_ */
