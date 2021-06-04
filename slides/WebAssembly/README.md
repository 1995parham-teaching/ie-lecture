# Introduction to WebAssembly
We([Narges](https://github.com/NNargesNN) and I) gave a presentation as *Introduction to WebAssembly* in [Internet Engineering course](https://sbu-ce.github.io/IE-lecture/) at Shahid Beheshti University. Here you can find the slides and some code example of this presentation for better intuition.

Before using the codes, we highly recommend to read the slides. Also you can watch the presentation video [here]().

# Tools

- For converting `.wat` file to `.wasm`, firstly install [wabt](https://github.com/WebAssembly/wabt). Then run the commands below in your terminal.(More detailed help can be found on wabt github page).

## Insllation

To install it on your OS, follow the steps [here](https://github.com/WebAssembly/wabt#cloning) carefully.

## Running wat2wasm

some examples: 
```shell
# parse and typecheck test.wat
$ bin/wat2wasm test.wat

# parse test.wat and write to binary file test.wasm
$ bin/wat2wasm test.wat -o test.wasm

# parse spec-test.wast, and write verbose output to stdout (including the
# meaning of every byte)
$ bin/wat2wasm spec-test.wast -v
```
