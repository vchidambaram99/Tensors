# Tensors
Tensor class for machine learning, written in c++ (on hold).
The goal of this library is to support fast operations on dynamic rank tensors (cwise operations, contractions, not sure what else yet...). I'm going to try to introduce as few outside libraries as possible (hopefully none) and I'm going to make it as templated as possible to make it portable and easy to use. I may try to support the GPU eventually, but that's a pipe dream at this point (I don't even know how fast I'll be able to get it on the CPU, and I've never done anything with a GPU).

This is on hold until I finish my templated wrappers for simd intrinsics so that I can speed it up.
