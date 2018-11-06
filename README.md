# FrogScene

# Task 
Using Texture to make any scene from game or movie 

# Solution 
we choose to make a scene from a game that we used to play when we were Young.

![alt text](https://github.com/Wafaaismail/FrogScene/blob/master/hqdefault.jpg)

[GitHub Pages](https://pages.github.com/)

## Texture 

Textures are typically used for images to decorate 3D models, but in reality they can be used to store many different kinds of data.
It's possible to have 1D, 2D and even 3D textures, which can be used to store bulk data on the GPU.
An example of another use for textures is storing terrain information. 


Just like other objects, textures have to be bound to apply operations to them. Since images are 2D arrays of pixels,
it will be bound to the GL_TEXTURE_2D target.
The pixels in the texture will be addressed using texture coordinates during drawing operations. These coordinates range
from 0.0 to 1.0 where (0,0) is conventionally the bottom-left corner and (1,1) is the top-right corner of the texture image.
The operation that uses these texture coordinates to retrieve color information from the pixels is called sampling.
There are different ways to approach this problem, each being appropriate for different scenarios. 
OpenGL offers you many options to control how this sampling is done, of which the common ones will be discussed here.

Filtering
Since texture coordinates are resolution independent, they won't always match a pixel exactly. 
This happens when a texture image is stretched beyond its original size or when it's sized down.
OpenGL offers various methods to decide on the sampled color when this happens. 
This process is called filtering and the following methods are available:

GL_NEAREST: Returns the pixel that is closest to the coordinates.  
GL_LINEAR: Returns the weighted average of the 4 pixels surrounding the given coordinates.
GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR: Sample from mipmaps instead.

to Read the full topic i reccommend this  [Texture](https://open.gl/textures) .


Result of the code is :

![alt text](https://github.com/Wafaaismail/FrogScene/blob/master/frog.png)



