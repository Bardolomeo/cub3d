<h1>Cub3d - a raycasting project for 42SSchool</h1>
<p>This is a project that has the main goal of building a raycaster using only c. It was not possible to use standard C graphic libraries, so it was a bit of a challenge.</p>
<h2>Usage</h2>

```
make && ./cub3D <path-to-ber-file>
```
<p>A .ber file is made like this:</p>

```
  NA <path-to-north-wall-texture> 
  SO <path-to-south-wall-texture>
  WE <path-to-west-wall-texture>
  EA <path-to-east-wall-texture>

  C <hex-color-for-ceiling> (like 0,0,0)
  F <hex-color-for-floor>

  Map made by '0's and '1's, you must write a 'W', 'N', 'S' or 'E' inside the map to specify player position and orientation

  111111111111111111111
111110000000000000001
110000S00001111111111
100000000000001
111000000000011
11110000001111
11111111111111

``` 
