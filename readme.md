# Cubic Voxel Game (working title)
A work in progress game.

## Libraries
Libraries and the versions I'm using.
* [GLBinding 2.1.4](https://github.com/cginternals/glbinding)
* [GLFW 3.2.1](http://www.glfw.org)
* [GLM 0.9.9.0](http://glm.g-truc.net/0.9.9/index.html) (included)
* [stb image 2.19, stb_image_resize 0.95, stb_rect_pack 0.11](https://github.com/nothings/stb) (included)
* [Open Asset Import Library (assimp) 4.1.0](http://assimp.org/)
* [spdlog 0.17.0](https://github.com/gabime/spdlog) (included)
* [boost 1.66.0](http://www.boost.org/) - System, Container 

## Compiling
I have only tested it under Fedora 28 using X11 as of right now, but there are plans to make sure it builds Windows and MacOS as well.

1. ```cd``` into the downloaded directory
2. ```cmake .```
3. ```make```

In order for it to run you must run it form the current directory in the terminal