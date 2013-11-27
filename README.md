![Isolevel 0 for a randomly generated grid][ex-00-low]
![Isolevel 0 for a randomly generated grid][ex-00-high]

gaspar
======

Gaspar is a simple tool for generating random scalar fields with known topology. The main purpose of the tool is to help users verify isosurface extraction algorithms. In addition to the scalar field, the tool also provides the *expected topology* of the isosurface at the level-set 0. Randomly generated scalar fields can generate many interesting isosurfaces with lots of holes and connected components, which makes them interesting test cases.

Example
-------
The above two images show an isosurface of a scalar field generated with the following command:
```
gaspar --filename="grid" --N=9 --max-ref=5 --invariant="inv.txt" --refined
``` 
The left image is the low resolution grid (`--N=9` means a 9x9x9 grid) that will fed into an isosurface extraction algorithm (e.g., Marching Cubes). The image on the right shows the expected, correct implicit trilinear surface. This image is the golden standard, so that the user knows what to expect. By visual inspection, the user can determine that the two isosurfaces are very different. Nevertheless, the topological information is saved in the `inv.txt` file so that no visual inspection is needed. In this case, the expected topology is:
```
components: 4
genus: 16 0 0 0 
euler: -24
```
The isosurface contains four components, three of them contain no handles (genus 0) while one contains 16. The Euler characteristic of the whole isoruface is -24. Equipped with this information one can compare the expected (right image) againsts the topology computed using Marching Cubes (left):
```
components: 2
genus: 19 0
euler: -34
```
The number of components, genus and euler vary. Thus, the isosurface extraction technique used do not correctly reproduces the topology of the trilinear interpolant. This is not to say that the result shown in the left is wrong, but only that it does not uses the trilienar interpolant a guide for filling up the space.

Both images were generated with VTKs Marching Cubes implementation and visualized using [Paraview](http://paraview.org).

How to
------

Type `gaspar --help` for all the available options.


[ex-00-low]: https://raw.github.com/tiagoetiene/gaspar/master/pic/ex-00-low.png "Isolevel 0 for a randomly generated grid"
[ex-00-high]: https://raw.github.com/tiagoetiene/gaspar/master/pic/ex-00-high.png "Isolevel 0 for a randomly generated grid"


---

Let me know what you think! I'm good with emails :) tiago.etiene@gmail.com
