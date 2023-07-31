# Main program

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

On Ubuntu 20.04
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

All empty lines in `.que` files are ignored. Program use empty line it output file to separate yet-to-use questions from used or sfiltered out questions. However, for correct conversion to `.json` using `scripts/que2json` `.que` file must be ended by newline.

# Additional scripts

## Dependencies
Install `jq`

On Ubuntu 20.04
```bash
sudo apt install jq
```

## Scripts
Can be faund in `scripts/`
1. `info` - gets information about `.que` question set, i.e. categories, number of questions, etc.
2. `exclude` - transforms `.que` question set into another without specified categories and/or musical questions,
3. `unused` - transforms `.que` question set into another with only unused questions,
4. `set_as_unused` - transforms `.que` question set into another where all questions are set as unused,
5. `que2json` - transforms `.que` questions set into `.json` question set,
6. `json2que` - transforms `.json` questions set into `.que` question set.