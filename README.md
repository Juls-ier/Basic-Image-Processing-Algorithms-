# Basic-Image-Processing-Algorithms-in-C++
Application written in C++ using OpenCV that implements fundamental raster image processing operations from scratch.

# Features
- **Color & Intensity:** Red-channel grayscale (`grayscaleRed`), weighted luminance grayscale (`grayscaleWeighted`), brightness adjustment (`darker_lighter`), and thresholding (`binarization`).
- **Morphological Operations:** Custom square-kernel dilation (`dylate`), erosion (`erode`), opening (`opening`), and closing (`closing`) with configurable radius.
- **2D Spatial Convolution:** Custom `convolution` engine supporting `3x3` kernels:
  - Box blur & Low-pass filter
  - Gaussian smoothing (`sigma` variants)
  - Sharpening & High-pass edge enhancement

