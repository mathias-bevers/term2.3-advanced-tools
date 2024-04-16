# Advanced Tools


## Building

### Linux
```
cmake -S . -B <path/to/build/>
cmake --build <path/to/build/>
path/to/build/at_<array_size>_<iterations>
```

### Windows
```
cmake -DCMAKE_CXX_COMPILER='C:\ProgramData\mingw64\mingw64\bin\g++.exe' -S . -B <path/to/build/> -G "MinGW Makefiles"
cmake --build <path/to/build/>
path/to/build/at_<array_size>_<iterations>.exe
```