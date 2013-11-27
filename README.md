![Isolevel 0 for a randomly generated grid][ex-00-low]
![Isolevel 0 for a randomly generated grid][ex-00-high]

gaspar
======

Gaspar is a simple tool for generating random scalar fields with known topology. The main purpose of the tool is to help users verify isosurface extraction algorithms. In addition to the scalar field, the tool also provides the *expected topology* of the isosurface at the level-set 0. Randomly generated scalar fields can generate many interesting isosurfaces with lots of holes and connected components, which makes them interesting test cases.

Example
-------
The above two images show an isosurface of a scalar field generated with the following command:
```
gaspar --filename="grid" --N=9 --max-ref=5 --invariant="inv.txt" ---refined
``` 
The left image is a low resolution grid (9x9x9) whereas the right image shows its refined version. The two isosurfaces are clearly different: the right image contains more components and holes than the left one. Topological information is saved in the `inv.txt` file. Both images were generated with VTKs Marching Cubes implementation and visualized using [Paraview](http://paraview.org).

How to
------

Type `gaspar --help` for all the available options.


[ex-00-low]: https://raw.github.com/tiagoetiene/gaspar/master/pic/ex-00-low.png "Isolevel 0 for a randomly generated grid"
[ex-00-high]: https://raw.github.com/tiagoetiene/gaspar/master/pic/ex-00-high.png "Isolevel 0 for a randomly generated grid"


---

Let me know what you think! I'm good with emails :) tiago.etiene@gmail.com
