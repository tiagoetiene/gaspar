#ifndef DIGITIZATION_HPP_
#define DIGITIZATION_HPP_

#include <stack>

#include "structuredGrid.hpp"

namespace vnv
{

enum PointType
{
    UNDEFINED		= 0,
    FACE_POINT		= 1,
    EDGE_POINT		= 2,
    CORNER_POINT	= 4,
    OLD_POINT		= 8
};

inline
void classify(vnv::structuredGrid<PointType>& type)
{
    unsigned N;
    type.get(N);

    for(unsigned k = 0; k < N; ++k)
        for(unsigned j = 0; j < N; ++j)
            for(unsigned i = 0; i < N; ++i)
                if(i%2 == 0 and j%2 == 0 and k%2 == 0)
                    type.set(i, j, k, OLD_POINT);

    bool facePoint;
    for(unsigned k = 0; k < N; ++k)
        for(unsigned j = 0; j < N; ++j)
            for(unsigned i = 0; i < N; ++i)
                if(type.get(i, j, k) == UNDEFINED)
                {
                    facePoint = false;
                    if(i > 0 and i + 1 < N)
                        facePoint = facePoint or
                                    (type.get(i-1, j, k) == OLD_POINT and
                                     type.get(i+1, j, k) == OLD_POINT);
                    if(j > 0 and j + 1 < N)
                        facePoint = facePoint or
                                    (type.get(i, j-1, k) == OLD_POINT and
                                     type.get(i, j+1, k) == OLD_POINT);
                    if(k > 0 and k + 1 < N)
                        facePoint = facePoint or
                                    (type.get(i, j, k-1) == OLD_POINT and
                                     type.get(i, j, k+1) == OLD_POINT);
                    if(facePoint)
                        type.set(i, j, k, FACE_POINT);
                }

    bool edgePoint;
    for(unsigned k = 0; k < N; ++k)
        for(unsigned j = 0; j < N; ++j)
            for(unsigned i = 0; i < N; ++i)
                if(type.get(i, j, k) == UNDEFINED)
                {
                    edgePoint = false;
                    if(i > 0 and i + 1 < N and j > 0 and j + 1 < N)
                        edgePoint = edgePoint or
                            (type.get(i-1, j, k) == FACE_POINT and
                             type.get(i+1, j, k) == FACE_POINT and
                             type.get(i, j-1, k) == FACE_POINT and
                             type.get(i, j+1, k) == FACE_POINT);
                    if(i > 0 and i + 1 < N and k > 0 and k + 1 < N)
                        edgePoint = edgePoint or
                            (type.get(i-1, j, k) == FACE_POINT and
                             type.get(i+1, j, k) == FACE_POINT and
                             type.get(i, j, k-1) == FACE_POINT and
                             type.get(i, j, k+1) == FACE_POINT);
                    if(k > 0 and k + 1 < N and j > 0 and j + 1 < N)
                        edgePoint = edgePoint or
                            (type.get(i, j-1, k) == FACE_POINT and
                             type.get(i, j+1, k) == FACE_POINT and
                             type.get(i, j, k-1) == FACE_POINT and
                             type.get(i, j, k+1) == FACE_POINT);
                    if(edgePoint)
                        type.set(i, j, k, EDGE_POINT);
                }

    for(unsigned k = 0; k < N; ++k)
        for(unsigned j = 0; j < N; ++j)
            for(unsigned i = 0; i < N; ++i)
                if(type.get(i, j, k) == UNDEFINED)
                {
                    type.set(i, j, k, CORNER_POINT);
                    assert(type.get(i-1, j, k) == EDGE_POINT);
                    assert(type.get(i+1, j, k) == EDGE_POINT);
                    assert(type.get(i, j-1, k) == EDGE_POINT);
                    assert(type.get(i, j+1, k) == EDGE_POINT);
                    assert(type.get(i, j, k-1) == EDGE_POINT);
                    assert(type.get(i, j, k+1) == EDGE_POINT);
                }

    int faces = 0;
    int edges = 0;
    int corners=  0;
    int old = 0;
    int undefined = 0;
    for(unsigned k = 0; k < N; ++k)
        for(unsigned j = 0; j < N; ++j)
            for(unsigned i = 0; i < N; ++i)
                if(type.get(i, j, k) == FACE_POINT)
                    ++faces;
                else if(type.get(i, j, k) == EDGE_POINT)
                    ++edges;
                else if(type.get(i, j, k) == CORNER_POINT)
                    ++corners;
                else if(type.get(i, j, k) == OLD_POINT)
                    ++old;
                else if(type.get(i, j, k) == UNDEFINED)
                    ++undefined;

    int n = (N + 1) / 2;
    assert(corners == (n-1) * (n-1) * (n-1));
    assert(undefined == 0);
    assert(old == n * n * n);
}


template<typename Real, typename Int>
void digitize(const vnv::structuredGrid<Real>& grid,
              vnv::structuredGrid<Int>& digitized)
{
    unsigned N;
    grid.get(N);
    vnv::structuredGrid<PointType> types(N);
    types.set(UNDEFINED);
    classify(types);

    digitized.set(0);

    for(unsigned k = 1; k < N-1; ++k)
        for(unsigned j = 1; j < N-1; ++j)
            for(unsigned i = 1; i < N-1; ++i)
                if(types.get(i, j, k) == OLD_POINT)
                    if(grid.get(i, j, k) < 0.0)
                        digitized.set(i, j, k, 1);

    for(unsigned k = 1; k < N-1; ++k)
        for(unsigned j = 1; j < N-1; ++j)
            for(unsigned i = 1; i < N-1; ++i)
                if(types.get(i, j, k) == FACE_POINT)
                {
                    if(types.get(i-1, j, k) == OLD_POINT and
                       types.get(i+1, j, k) == OLD_POINT)
                    {
                        if(grid.get(i-1, j, k) < 0.0 and
                           grid.get(i+1, j, k) < 0.0)
                            digitized.set(i, j, k, 1);
                    }

                    if(types.get(i, j-1, k) == OLD_POINT and
                       types.get(i, j+1, k) == OLD_POINT)
                    {
                        if(grid.get(i, j-1, k) < 0.0 and
                           grid.get(i, j+1, k) < 0.0)
                            digitized.set(i, j, k, 1);
                    }
                    if(types.get(i, j, k-1) == OLD_POINT and
                       types.get(i, j, k+1) == OLD_POINT)
                    {
                        if(grid.get(i, j, k-1) < 0.0 and
                           grid.get(i, j, k+1) < 0.0)
                            digitized.set(i, j, k, 1);
                    }
                }

    for(unsigned k = 1; k < N-1; ++k)
        for(unsigned j = 1; j < N-1; ++j)
            for(unsigned i = 1; i < N-1; ++i)
                if(types.get(i, j, k) == EDGE_POINT)
                {
                    int here = 0;
                    int counter = 0;
                    for(int d1 = -1; d1 <= 1; ++d1)
                        for(int d2 = -1; d2 <= 1; ++d2)
                        {
                            here = 0;
                            if(!d1 and !d2) continue;
                            int a, b, c;
                            if(types.get(i-1, j-1, k) == OLD_POINT)
                            {
                                a = i + d1;
                                b = j + d2;
                                c = k;
                                ++here;
                            }
                            if(types.get(i-1, j, k-1) == OLD_POINT)
                            {
                                a = i + d1;
                                b = j;
                                c = k + d2;
                                ++here;
                            }
                            if(types.get(i, j-1, k-1) == OLD_POINT)
                            {
                                a = i;
                                b = j + d1;
                                c = k + d2;
                                ++here;
                            }
                            assert(here == 1);

                            assert(types.get(a, b, c) == FACE_POINT or
                                   types.get(a, b, c) == OLD_POINT);
                            if(digitized.get(a, b, c) == 1)
                                counter++;
                        }
                    if(counter >= 4)
                        digitized.set(i, j, k, 1);
                }

    for(unsigned k = 1; k < N-1; ++k)
        for(unsigned j = 1; j < N-1; ++j)
            for(unsigned i = 1; i < N-1; ++i)
                if(types.get(i, j, k) == CORNER_POINT)
                {
                    int counter = 0;
                    for(int ii = -1; ii <= 1; ++ii)
                        for(int jj = -1; jj <= 1; ++jj)
                            for(int kk = -1; kk <= 1; ++kk)
                            {
                                if(!ii and !jj and !kk) continue;
                                int a = i + ii;
                                int b = j + jj;
                                int c = k + kk;
                                assert(types.get(a, b, c) != CORNER_POINT);
                                if(digitized.get(a, b, c) == 1)
                                    counter++;
                            }
                    if(counter >= 12)
                        digitized.set(i, j, k, 1);
                }
}

template<typename Int>
bool isBoundaryFace(const vnv::structuredGrid<Int>& d,
        const int i, const int j, const int k, const int dx, int dy, int dz)
{
    if(d.get(i, j, k) == 1 and d.get(i+dx, j+dy, k+dz) != 1)
        return true;

    return false;
}

template<typename Int>
inline
void markBoundary(const vnv::structuredGrid<Int>& digitization,
                  vnv::structuredGrid<Int>& bdry)
{
    unsigned N;
    digitization.get(N);
    bdry.set(0);

    for(unsigned k = 1; k < N - 1; ++k)
        for(unsigned j = 1; j < N - 1; ++j)
            for(unsigned i = 1; i < N - 1; ++i)
            {
                if(isBoundaryFace(digitization, i, j, k, 0, 0, -1))
                {
                    bdry.set(i  , j  , k, 2);
                    bdry.set(i+1, j  , k, 2);
                    bdry.set(i+1, j+1, k, 2);
                    bdry.set(i  , j+1, k, 2);
                }
                if(isBoundaryFace(digitization, i, j, k, 0, 0, +1))
                {
                    bdry.set(i  , j  , k+1, 2);
                    bdry.set(i+1, j  , k+1, 2);
                    bdry.set(i+1, j+1, k+1, 2);
                    bdry.set(i  , j+1, k+1, 2);
                }

                if(isBoundaryFace(digitization, i, j, k, 0, -1, 0))
                {
                    bdry.set(i  , j, k,   2);
                    bdry.set(i+1, j, k,   2);
                    bdry.set(i+1, j, k+1, 2);
                    bdry.set(i  , j, k+1, 2);
                }
                if(isBoundaryFace(digitization, i, j, k, 0, +1, 0))
                {
                    bdry.set(i  , j+1, k,   2);
                    bdry.set(i+1, j+1, k,   2);
                    bdry.set(i+1, j+1, k+1, 2);
                    bdry.set(i  , j+1, k+1, 2);
                }

                if(isBoundaryFace(digitization, i, j , k, -1, 0, 0))
                {
                    bdry.set(i, j  , k  , 2);
                    bdry.set(i, j+1, k  , 2);
                    bdry.set(i, j+1, k+1, 2);
                    bdry.set(i, j  , k+1, 2);
                }
                if(isBoundaryFace(digitization, i, j , k, +1, 0, 0))
                {
                    bdry.set(i+1, j  , k  , 2);
                    bdry.set(i+1, j+1, k  , 2);
                    bdry.set(i+1, j+1, k+1, 2);
                    bdry.set(i+1, j  , k+1, 2);
                }
            }
}

template<typename Int>
bool isBoundaryEdge(const vnv::structuredGrid<Int>& bdry,
                    const vnv::structuredGrid<Int>& d,
                    const int i, const int j, const int k,
                    const int a, const int b, const int c)
{
    if(bdry.get(i, j, k) == 0) return false;
    if(bdry.get(a, b, c) == 0) return false;

    int dx = i - a;
    int dy = j - b;
    int dz = k - c;
    assert((dx and !dy and !dz) or (!dx and dy and !dz) or (!dx and !dy and dz));

    int inside = 0;
    int outside = 0;
    for(int d1 = -1; d1 < 1; ++d1)
        for(int d2 = -1; d2 < 1; ++d2)
        {
            int a = -1, b = -1, c = -1;

            if(dx != 0)
            {
                a = i;
                b = j + d1;
                c = k + d2;
            }else if(dy != 0)
            {
                a = i + d1;
                b = j;
                c = k + d2;
            }
            else if(dz != 0)
            {
                a = i + d1;
                b = j + d2;
                c = k;
            }

            if(d.get(a, b, c) == 0)
                ++outside;
            else if(d.get(a, b, c) != 0)
                ++inside;
        }

    if(!(inside + outside == 4))
    {
        std::cout << inside << std::endl;
        std::cout << outside << std::endl;
    }
    assert(inside + outside == 4);
    return inside != 4 and outside != 4;
}

template<typename Int>
void
markConnectedComponent(vnv::structuredGrid<Int>& bdry, int p, int q, int r,
                            int newValue)
{
#define ADD_TO_STACK(a,b,c)	\
{							\
        visited[0].push(a);	\
        visited[1].push(b);	\
        visited[2].push(c);	\
}
#define RM_FROM_STACK		\
{							\
        visited[0].pop();	\
        visited[1].pop();	\
        visited[2].pop();	\
}

    assert(bdry.get(p, q, r) == 2);
    std::vector< std::stack<int> > visited(3);
    ADD_TO_STACK(p, q, r)

    while(!visited[0].empty())
    {
        int i = visited[0].top();
        int j = visited[1].top();
        int k = visited[2].top();
        RM_FROM_STACK;

        assert(bdry.get(i, j, k) != 0);
        if(bdry.get(i, j, k) != 2)
            continue;
        bdry.set(i, j, k, newValue);

        if(bdry.get(i + 1, j, k) == 2)
            ADD_TO_STACK(i + 1, j, k);
        if(bdry.get(i - 1, j, k) == 2)
            ADD_TO_STACK(i - 1, j, k);

        if(bdry.get(i, j + 1, k) == 2)
            ADD_TO_STACK(i, j + 1, k);
        if(bdry.get(i, j - 1, k) == 2)
            ADD_TO_STACK(i, j - 1, k);

        if(bdry.get(i, j, k + 1) == 2)
            ADD_TO_STACK(i, j, k + 1);
        if(bdry.get(i, j, k - 1) == 2)
            ADD_TO_STACK(i, j, k - 1);
    }
}

template<typename Int>
int
computeConnectedComponents(vnv::structuredGrid<Int>& bdry)
{
    unsigned N;
    int numConnectedComponents = 0;
    bdry.get(N);

    for(unsigned k = 1; k < N - 1; ++k)
        for(unsigned j = 1; j < N - 1; ++j)
            for(unsigned i = 1; i < N - 1; ++i)
            {
                if(bdry.get(i, j, k) == 2)
                {
                    numConnectedComponents++;
                    markConnectedComponent(bdry, i, j, k,
                                        numConnectedComponents + 2);
                }
            }
    return numConnectedComponents;
}

template<typename Int>
std::vector<int>
computeGenus(vnv::structuredGrid<Int>& bdry,
             const vnv::structuredGrid<Int>& digitization)
{
    std::vector<int> M(10);

    int count;
    unsigned N;
    bdry.get(N);

    int numComponents = computeConnectedComponents(bdry);

    if(numComponents == 0)
        return std::vector<int>();

    std::vector<int> genus;
    for(int component = 1+2; component <= numComponents+2; ++component)
    {
        for(unsigned i = 0; i < M.size(); ++i)
            M[i] = 0;

        for(unsigned k = 1; k < N - 1; ++k)
            for(unsigned j = 1; j < N - 1; ++j)
                for(unsigned i = 1; i < N - 1; ++i)
                    if(bdry.get(i, j, k) == component)
                    {
                        count = 0;
                        if(isBoundaryEdge(bdry, digitization,
                                            i, j, k, i+1, j, k))
                            ++count;
                        if(isBoundaryEdge(bdry, digitization,
                                            i-1, j, k, i, j, k))
                            ++count;

                        if(isBoundaryEdge(bdry, digitization,
                                            i, j, k, i, j+1, k))
                            ++count;
                        if(isBoundaryEdge(bdry, digitization,
                                            i, j-1, k, i, j, k))
                            ++count;

                        if(isBoundaryEdge(bdry, digitization,
                                            i, j, k, i, j, k+1))
                            ++count;
                        if(isBoundaryEdge(bdry, digitization,
                                            i, j, k-1, i, j, k))
                            ++count;

                        M[count]++;
                    }
        genus.push_back(1 + (M[5] + 2 * M[6] - M[3]) / 8);
    }
    return genus;
}

}

#endif /* DIGITIZATION_HPP_ */
