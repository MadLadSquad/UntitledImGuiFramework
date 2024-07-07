# About the C API
The C API is a light C wrapper on top of the C++ user-facing API.

The C API should only be used for creating plugins in a language, other than C++, as C's simplicity requires a good
number of heap allocations that are otherwise not done, due to C++'s zero-cost abstractions.