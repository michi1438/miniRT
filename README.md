# miniRT

This is a 42 project, a simple raytracer written in C (it comes with a vanilla JS version too).

### Building
Read up on needed dependencies for the minilibx [here](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html).
This project builds on Linux and MacOS alike.
* Run `make`. You can also define the `fast` environment variable to compile using the fast flag.

### Running and controls:
* Run with `RESOLUTION=0.001 ./miniRT [scene.rt]`
* There are example scenes inside `Scenes`
* The `RESOLUTION` variable controls the density of cast rays.
	Different densities yield different quality of result, at a cost.
* Use the wasd, arrow keys, space and tab to control the camera. Press enter to raytrace.

### Web version:
The web version (`web/webrt.html`) is WIP, it has more features, like mapping images onto objects, but needs several UI improvements 
to be practical to use (adding objects is done in the code directly).