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

## `*.que` file description
Every question should be in separate line described as
```bash
category; question; correct_answer; incorrect_answer1; incorrect_answer2; incorrect_answer3; name_of_wav_file; is_used; comment
```
`name_of_wav_file` is a path (or part of the path, see option `-P` for common dictionary) to `.wav` file, without extension.

`is_used` is a boolean (`0` or `1`) that indicates if question was used before and will **not** be used again.  