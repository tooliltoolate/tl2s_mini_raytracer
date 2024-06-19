![image](https://github.com/tooliltoolate/tl2s_mini_raytracer/assets/2312684/62d3de03-fa9f-4c05-b6d0-a132e6810a90)# Camera

A renderer is a computer program that takes a virtual photography. For this, we need to model the camera.

Starting from the result, we have the image: a 2D array of pixels. It is recommended that images are not square - will help debugging when inverting the axes.

We plan to model the photographic process by tracing light rays - raytracing. In physics, we think that a light source emits light rays. The light rays interact with the materials in different ways:

- air is transparent - does not affect the light rays
- mirrors are reflective - the light ray changes direction
- most objects are diffuse - the light rays get deflected in a variety of angles, and some colors might be absorbed

![image](https://github.com/tooliltoolate/tl2s_mini_raytracer/assets/2312684/0f1e3569-624b-4237-9730-4376276e369c)

The light rays keep bouncing in the scene, and some of them might hit an observer: an eye or a camera. Note that in this process extremely many rays end up not hitting the observer, so simulating this process would be very wasteful. Instead, we trace the rays backwards, from the camera. We shall discuss more about this process. For now, our goal is to trace one ray from each pixel. So we need somehow to abstract the image in 3D space.

The abstraction of the pixels/image in 3D space is known as the viewport - think of it as the photographic film of an analogic camera.

![image](https://github.com/tooliltoolate/tl2s_mini_raytracer/assets/2312684/30f16945-1db2-4a31-895c-6dee5aaecd2a)

Just as the photographic film, the viewport is a continuous space of a certain dimension. This dimension is a parameter of the camera, but it must have the same aspect ratio as the image. So if you go with a 1920x1080 (full HD) camera, you can choose the height of the viewport to be 2, and set its width to 2*1080/1920 to keep the aspect ratio. Due to this requirement, **let's make the convention to always use height and aspect ratio rather than height and width**.

We now need to shoot rays through pixel centers

![image](https://github.com/tooliltoolate/tl2s_mini_raytracer/assets/2312684/7d2a115e-a47f-4644-b900-d40829ed0cb5)

so we need to compute delta u and delta v as viewport width (or height) divided by the number of pixels in the image. We also need to compute the absolute position of a pixel center in 3D space. We introduce another camera parameter: **the focal distance**. This is the distance between the camera center and the viewport (usually the viewport center). Based on this geometry, you can determine the viewport top left corner, and then compute pixel centers by applying offsets. Once the absolute position of the pixel center in 3D is computed, you can shoot a ray using the functionality in the Ray class.




