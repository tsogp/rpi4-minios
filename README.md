## Run with CMake

### With shell script
```
sh run.sh
```

### Without shell script
```
mkdir -p build
cmake -B build
cd build
make
make uart0
```

## Run with Make
```
cd build
make
make uart0
```