#Hideous Game Engine

How To Use
==========
1. Add followings to User Header Search Path:

'/Volumes/DrivePlusPlus/Languages/std_lib/he/include/'
'/Volumes/DrivePlusPlus/Languages/std_lib/freetype_2_ios/include/freetype2'


Code Structure
==============

1. All cpp files compile to libhe.a static library.

2. The library libhe.a is located at:
'/Volumes/DrivePlusPlus/Languages/std_lib/he/'

3. The headers files at:
'/Volumes/DrivePlusPlus/Languages/repo/he/HideousGameEngine/HideousGameEngine/include/'
are just a stable copy of:
'/Volumes/DrivePlusPlus/Languages/std_lib/he/include/'
Use the ones located at latter location.

The Philosophy
==============

RenderObject:
At the core there is a fat RenderObject.
The RenderObject contains ALL the basic elements required by any kind of shader possible.
Turns out, they are not as many as you'd expect.

Currently it holds:

- VertexData (required)
- Shader	(required)
- Texture	(optional)
- ModelViewProjection Matrix. (optional)
- Color	(optional)

Shaders:
Then there are these specific shaders. Each shader is capable of rendering the RenderObject in it's own way.

VertexData:
The data is strongly coupled with Shader, but one kind of VertexData could be used my different Shaders.

Demos
=====

RectColorTest
-------------
Demonstrates how to:

1. Run a simple Kalchakra.

2. Encapsulate Core's RectColor within your Entity in this case RunningSquare.

3. Add/remove entities from the Kalchakra.

RectTextureTest
---------------
How to load textures, standalones or using a texture atlas.

RectTextTest
------------
How to load text. How to create texture data for text on the fly.

MultiShadersTest
----------------
How to work with different shaders together.

MultiFontTest
-------------
How to work with differnt text objects.

How stuff works?
================

Texture cycle
--------------
The textures are loaded into memory through RectTexture class objects.

1.	Texture objects get allocated in memory at the RectTexture ctor.
	1.1	That just copies the name/extn for searching purpose (later)
	
2.	RectTexture::init calls the loadShaders, that loads the texture.
	2.1	There is a singletone class TexturePool, that has a list of all the Texture
		in the memory.
	2.3	TexturePool::get method tries to find the requested Texture.
		If found, it returns the instance. Else load the Texture into memory by calling Texture::load()

3.	TexturePool has a inner class SharedTexture. That manages the Textures on retain count basis.
		
4. Each ~RectTexture() does two operations:
	4.1 delete Texture. That releases any string or data collected by Texture.
		The Texture then calls TexturePool::unget() which checks for Texture retain count.
		If retain count is 0. It calls Texture unload(). That releases the texture data from memnory.
