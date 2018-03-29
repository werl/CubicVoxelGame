# Transport Concept 3D
While working on a Transport simulation game in Unity3D I had to take a hiatus. During this time I decided to take a
stab at writing a version from just some simple libraries and see how far I get

## Included Libraries
Libraries and the versions I'm using.
* [GLBinding 2.1.4](https://github.com/cginternals/glbinding)
* [GLFW 3.2.1](http://www.glfw.org)
* [GLM 0.9.8.5](http://glm.g-truc.net/0.9.8/index.html)
* [stb image 2.19, stb_image_resize 0.95, stb_rect_pack 0.11](https://github.com/nothings/stb)
* [Open Asset Import Library (assimp) 4.1.0](http://assimp.org/)
* [spdlog 0.16.4](https://github.com/gabime/spdlog)
* [boost 1.66.0](http://www.boost.org/) - Filesystem, System, Container 

## Compiling
I have only tested it under Ubuntu 17:10 using X11 as of right now, but there are plans to make sure it builds Windows and MacOS as well.
Boost, Assimp, GLBinding, and GLFW are required on the system as they are dynamically linked

1. ```cd``` into the downloaded directory
2. ```cmake .```
3. ```make```

In order for it to run you must run it form the current directory in the terminal