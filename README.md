# Main program

This is homemade implementation of system used in popular Polish TV show "Awantura o Kasę" ("Cash Battle" in New Zealand).

[Short promo of version aired in New Zealand.](https://www.youtube.com/watch?v=AOx8KhTjwQs)

All episodes aired in Poland can be found [here](https://www.youtube.com/@awanturaokase8867).

## Installation

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

On Ubuntu 22.04
```bash
sudo apt install fonts-dseg
```

## Build 
```bash
cmake CMakeLists.txt 
cmake --build .
```

## Run
In English:
```bash
./CashBattle -i questionsEN.que -l EN
```
In Polish:
```bash
./CashBattle -i questionsPL.que
```

## Help
```bash
./CashBattle -h
```

## `*.que` file description
Every question should be in separate line described as
```bash
category; question; correct_answer; incorrect_answer1; incorrect_answer2; incorrect_answer3; name_of_wav_file; is_used; comment
```
`name_of_wav_file` is a path (or part of the path, see option `-P` for common dictionary) to `.wav` file, without extension.

`is_used` is a boolean (`0` or `1`) that indicates if question was used before and will **not** be used again.

All empty lines in `.que` files are ignored. Program use empty line in output file to separate yet-to-use questions from used or filtered out questions. However, for correct conversion to `.json` using `scripts/que2json` `.que` file must be ended by newline.

# Additional scripts

## Dependencies
Install `jq`

On Ubuntu 22.04
```bash
sudo apt install jq
```

Install `LaTeX` and `pdftk`

On Ubuntu 22.04
```bash
sudo apt install texlive-latex-recommended
sudo apt install pdftk
```

## Scripts
Can be found in `scripts/`
1. `info` - gets information about `.que` question set, i.e. categories, number of questions, etc.
2. `exclude` - transforms `.que` question set into another without specified categories and/or musical questions,
3. `unused` - transforms `.que` question set into another with only unused questions,
4. `set_as_unused` - transforms `.que` question set into another where all questions are set as unused,
5. `que2json` - transforms `.que` questions set into `.json` question set,
6. `json2que` - transforms `.json` questions set into `.que` question set,
7. `flashcards` - create `.pdf` file in flashcards style with questions form `.que` question set.