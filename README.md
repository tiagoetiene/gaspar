Gaspar
======

Gaspar is a simple tool for generating random scalar fields with known topology. The main purpose of the tool is to help users verify isosurface extraction algorithms. In addition to the scalar field, Gaspar also provides the *expected topology* of the isosurface at the zero level set. 

Randomly generated scalar fields can generate many interesting isosurfaces with lots of holes and connected components, which makes them interesting test cases.

![Isolevel 0 for a randomly generated grid][ex-00-low]
![Isolevel 0 for a randomly generated grid][ex-00-high]

Example
-------
The above two images show an isosurface of a scalar field generated with the following command:
```
gaspar --filename="grid" --N=9 --max-ref=5 --invariant="inv.txt" --refined
``` 
The left image is the low resolution grid (`--N=9` means a 9x9x9 grid) that will be fed into an isosurface extraction algorithm (e.g., [Marching Cubes](http://en.wikipedia.org/wiki/Marching_cubes)). The image on the right is the _expected, correct, implicit trilinear surface_. It is the golden standard. By visual inspection, the user can determine that the two isosurfaces are very different. Alternatively, the user can save the topological information in a file (`inv.txt`) so that no visual inspection is needed. For the case shown in the right image, the expected topology is:
```
components: 4
genus: 16 0 0 0 
euler: -24
```
The isosurface contains four components, three of them contain no handles (genus 0) while one contains 16. The Euler characteristic of the surface is -24. With this information, the expected (right image) andcomputed (left) surfaces can be compared. For example, here's the topological information for the surface shown in the left:
```
components: 2
genus: 19 0
euler: -34
```
The number of components, genus and Euler characteristics are different. Thus, the isosurface extraction technique used does not correctly reproduce the topology of the trilinear interpolant. This is not to say that the result shown in the left is wrong, but only that it does not uses the trilienar interpolant as a guide for building the triangular mesh.

Both images were generated with VTKs Marching Cubes implementation and visualized using [Paraview](http://paraview.org).

How to
------

Type `gaspar --help` for all the available options.

Publication
-----------

Gaspar implementation is based on the paper below. The paper extends the idea of verification to include the topology of isosurface extraction techniques.

T. Etiene,L. G. Nonato,	C. Scheidegger,	J. Tierny, T. J. Peters, V. Pascucci,	R. M. Kirby, C. T. Silva;  
[_Topology Verification for Isosurface Extraction_](http://dx.doi.org/10.1109/TVCG.2011.109);  
IEEE Transactions on Visualization and Computer Graphics. Volume 18 Issue 6 June 2012 Pages 952-965 


[ex-00-low]: https://raw.github.com/tiagoetiene/gaspar/master/pic/ex-00-low.png "Isolevel 0 for a randomly generated grid"
[ex-00-high]: https://raw.github.com/tiagoetiene/gaspar/master/pic/ex-00-high.png "Isolevel 0 for a randomly generated grid"


---

Let me know what you think! I'm good with emails :) tiago.etiene@gmail.com
