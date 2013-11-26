#ifndef STRUCTUREDGRID_HPP_
#define STRUCTUREDGRID_HPP_

#include <vector>
#include <algorithm>

#include <boost/noncopyable.hpp>

namespace vnv
{

template<class T>
class structuredGrid : public boost::noncopyable
{
public:
    structuredGrid(const unsigned _nPoints) :
        nPoints(_nPoints),
        nPointsSquared(nPoints*nPoints),
        m_grid(nPoints*nPoints*nPoints)
    {
    }

    inline
    void set(const T value)
    {
        std::fill(m_grid.begin(), m_grid.end(), value);
    }

    inline
    void set(const unsigned i, const unsigned j, const unsigned k, const T& value)
    {
        m_grid[i + j * nPoints + k * nPointsSquared] = value;
    }

    inline
    const T& get(const unsigned i, const unsigned j, const unsigned k) const
    {
        return m_grid[i + j * nPoints + k * nPointsSquared];
    }

    inline
    void get(unsigned& n) const
    {
        n = nPoints;
    }

    inline
    unsigned get() const
    {
        return nPoints;
    }

    inline
    T getDelta() const
    {
        return (max[0] - min[0]) / (T)(nPoints - 1);
    }

    inline
    void setLimits(const T xmin, const T ymin, const T zmin,
                   const T xmax, const T ymax, const T zmax)
    {
        min[0] = xmin; min[1] = ymin; min[2] = zmin;
        max[0] = xmax; max[1] = ymax; max[2] = zmax;
    }

    void getLimits(T& xmin, T& ymin, T& zmin,
                   T& xmax, T& ymax, T& zmax) const
    {
        xmin = min[0]; ymin = min[1]; zmin = min[2];
        xmax = max[0]; ymax = max[1]; zmax = max[2];
    }

    //! Position of the lower-left-back point on a 3D box
    T min[3];

    //! Position of the upper-right-front point on a 3D box
    T max[3];

protected:
    const unsigned nPoints;
    const unsigned nPointsSquared;

    std::vector<T> m_grid;
};

}

#endif /*STRUCTUREDGRID_HPP_*/
