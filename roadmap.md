# Roadmap

## Infrastructure

Before doing any ray-tracing, a few tools are needed.

### File I/O

- [x] Image class
  Make an image class that will be the output of the renderer. The current goal is to store a matrix of `height x width x 3` elements of type `uint8_t` - we might change this in the future. Think of what additional methods could be useful.
- [x] PPM image writer
  We need some way to output images. PPM is a convenient format (although inefficient). See https://en.wikipedia.org/wiki/Netpbm#File_formats
- [x] Validation
  Write a small program that can generate some images of any pattern you wish to test this functionality.

### Math

- [x] Vector class
  A fundamental data type in a renderer is a 2D/3D vector. Think of a class of this type (or two classes). Implement any operations you might think are useful, as well as some test. Use `gtest` to make a test bench.
- [x] Point class
  We also need points. Think how you can handle this data type with as little code duplication as possible. Might not be require to build a class explicitly
- [x] Ray
  In a renderer, we want to be able to track rays through 3D space. A ray is a origin, and a direction. Make a classs for it. Add a method `Point at(double t)` which computes `origin + t * direction`.

### Camera

- [ ] Camera class

### Scene

### Rigid bodies
