/*
 * cases.hpp
 *
 *  Created on: Feb 21, 2010
 *      Author: etiene
 */

#ifndef CASES_HPP_
#define CASES_HPP_

#include <set>

#include "structuredGrid.hpp"

namespace vnv
{


class TrilinearCases
{
public:
    TrilinearCases()
    {
    }
    ~TrilinearCases()
    {
    }


    template<typename Real>
    void find_positive_components(Real cube[2][2][2], int i, int j, int k)
    {
        cube[i][j][k] = 0.0;

        if(cube[i+(1-2*i)][j][k] > 0.0)
            find_positive_components(cube, i+(1-2*i), j, k);
        if(cube[i][j+(1-2*j)][k] > 0.0)
            find_positive_components(cube, i, j+(1-2*j), k);
        if(cube[i][j][k+(1-2*k)] > 0.0)
            find_positive_components(cube, i, j, k+(1-2*k));
    }

    template<typename Real>
    void find_negative_components(Real cube[2][2][2], int i, int j, int k)
    {
        cube[i][j][k] = 0.0;

        if(cube[i+(1-2*i)][j][k] < 0.0)
            find_negative_components(cube, i+(1-2*i), j, k);
        if(cube[i][j+(1-2*j)][k] < 0.0)
            find_negative_components(cube, i, j+(1-2*j), k);
        if(cube[i][j][k+(1-2*k)] < 0.0)
            find_negative_components(cube, i, j, k+(1-2*k));
    }

    template<typename Real>
    bool isThereAnAmbiguousCell(const vnv::structuredGrid<Real>& grid)
    {
        unsigned N;
        Real cubeP[2][2][2];
        Real cubeN[2][2][2];

        grid.get(N);

        for(unsigned int k = 0; k < N-1; ++k)
            for(unsigned int j = 0; j < N-1; ++j)
                for(unsigned int i = 0; i < N-1; ++i)
                {

                    for(int kk = 0; kk < 2; ++kk)
                        for(int jj = 0; jj < 2; ++jj)
                            for(int ii = 0; ii < 2; ++ii)
                                cubeP[ii][jj][kk] = cubeN[ii][jj][kk] =
                                        grid.get(i + ii, j + jj, k + kk);

                    bool pos = true;
                    bool neg = true;
                    for(int kk = 0; kk < 2; ++kk)
                        for(int jj = 0; jj < 2; ++jj)
                            for(int ii = 0; ii < 2; ++ii)
                            {
                                if(cubeP[ii][jj][kk] > 0.0 and pos)
                                {
                                    find_positive_components(cubeP, ii, jj, kk);
                                    pos = false;
                                }
                                if(cubeN[ii][jj][kk] < 0.0 and neg)
                                {
                                    find_negative_components(cubeN, ii, jj, kk);
                                    neg = false;
                                }
                            }

                    for(int kk = 0; kk < 2; ++kk)
                        for(int jj = 0; jj < 2; ++jj)
                            for(int ii = 0; ii < 2; ++ii)
                            {
                                if(cubeP[ii][jj][kk] > 0.0)
                                    return true;
                                if(cubeN[ii][jj][kk] < 0.0)
                                    return true;
                            }
                }
        return false;
    }


    template<typename Real>
    void assignGrid(vnv::structuredGrid<Real>& grid)
    {
        unsigned N;
        grid.get(N);
        for(unsigned int k = 0; k < N-1; ++k)
            for(unsigned int j = 0; j < N-1; ++j)
                for(unsigned int i = 0; i < N-1; ++i)
                {
                    unsigned char pattern = 0;
                    Real v0 = grid.get(i + 0, j + 0, k + 0);
                    Real v1 = grid.get(i + 1, j + 0, k + 0);
                    Real v2 = grid.get(i + 0, j + 1, k + 0);
                    Real v3 = grid.get(i + 1, j + 1, k + 0);
                    Real v4 = grid.get(i + 0, j + 0, k + 1);
                    Real v5 = grid.get(i + 1, j + 0, k + 1);
                    Real v6 = grid.get(i + 0, j + 1, k + 1);
                    Real v7 = grid.get(i + 1, j + 1, k + 1);

                    if(v0 > 0.0) pattern |=   1;
                    if(v1 > 0.0) pattern |=   2;
                    if(v2 > 0.0) pattern |=   4;
                    if(v3 > 0.0) pattern |=   8;
                    if(v4 > 0.0) pattern |=  16;
                    if(v5 > 0.0) pattern |=  32;
                    if(v6 > 0.0) pattern |=  64;
                    if(v7 > 0.0) pattern |= 128;

                    mStdLUT.insert(pattern);
                }
    }

    bool isLUTFilled()
    {
        assert(mStdLUT.size() <= 256);
        if(mStdLUT.size() == 256)
        {
//			std::set<unsigned char>::iterator it, end;
//			it  = mStdLUT.begin();
//			end = mStdLUT.end();
//			for(; it != end; ++it)
//				std::cout << (int)*it << " ";
//			std::cout << std::endl;
            return true;
        }
        return false;
    }

protected:
    std::set<unsigned char> mStdLUT;

};



};

#endif /* CASES_HPP_ */
