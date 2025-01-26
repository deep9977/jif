# JIF
jif is a just in time (JIT) compiler for brainfuck programming language 

## Features:
- **Efficient Execution**: Translates repetitive Brainfuck commands into efficient intermediate representation (e.g., `++++` to `INST_ADD 4`) to reduce execution time.
- **Precalculated Jumps**: All posible jump offsets are precalculated to improve performance.

## Getting Started:

### Building Project:
```bash 
git clone https://github.com/deep9977/jif.git
cd jif 
make 
```

### Usage: 
Some sample programs can be found in example/ directory. To run a sample program run the following cammand:
```bash 
./jif example/hello-world.bf
```



