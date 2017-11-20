# Transport Concept 2D
While working on a Transport simulation game in Unity3D I had to take a hiatus. During this time I decided to take a
stab at writing a 2D version from just some simple libraries and see how far I get

## Included Libraries
Libraries and the versions I'm using.
* [GLBinding 2.1.3](https://github.com/cginternals/glbinding)
* [GLFW 3.2.1](http://www.glfw.org)
* [GLM 0.9.8.5](http://glm.g-truc.net/0.9.8/index.html)
* [stb Image 2.16](https://github.com/nothings/stb)
* [Open Asset Import Library (assimp) 4.0.1](http://assimp.org/)
* [spdlog 0.14.0](https://github.com/gabime/spdlog)

## Compiling
I have only tested it under MacOS as of right now, but there are plans to make sure it builds Windows and Linux as well.

1. ```cd``` into the downloaded directory
2. ```cmake .```
3. ```make```

In order for it to run you must run it form the current directory in the terminal

There is a known bug that may require you to move assimp's config.h file into the standard include directory!
