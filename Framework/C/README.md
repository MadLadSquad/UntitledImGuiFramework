# About me
This folder contains C bindings for the main interfaces in order to allow for C plugins to exist.

As you might already know, interfaces are static member functions that the application calls using the format
```cpp
ClassName::InsertFunctionHere(InsertArgumentsHere argument)
```

Apart from this we also include the 3 Component types, construction methods for them, as well as types, enums and other
symbols needed to be used by plugins.

This is just a user facing API, so this will not include access to lower level components as plugins don't really need
them

Will be filled with code soon!