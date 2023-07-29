## Instalation

1. Install Qt
On Ubuntu 22.04
```bash
sudo apt install build-essential
sudo apt install qtbase5-dev qt5-qmake
sudo apt install qtmultimedia5-dev
```

2. Install boost
On Ubuntu 22.04
```bash
sudo apt install libboost-all-dev
```

3. Install font
```bash
sudo apt install fonts-dseg
```

## Build 
```bash
cmake CMakeLists.txt 
cmake --build .
```

## Run
```bash
./AoK -i pytania.que
```

## Help
```bash
./AoK -h
```