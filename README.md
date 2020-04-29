## 1 Usage

### 1.1 Compiling & Running part1 on CSE
```text
You can run the following four commands to compile and run on cse.unl.edu:

cd sshrestha11_pa5/part1
make
./part1 BACKING_STORE.bin addresses.txt
```

### 1.2 Compiling & Running part2 on CSE
```text
You can run the following four commands to compile and run on cse.unl.edu:

cd sshrestha11_pa5/part2
make
./part2 BACKING_STORE.bin addresses1.txt fifo
./part2 BACKING_STORE.bin addresses1.txt lru
./part2 BACKING_STORE.bin addresses2.txt fifo
./part2 BACKING_STORE.bin addresses2.txt lru
```

### 1.3 Cleaning the folder(removes the current binary file and .out files)
```text
cd sshrestha11_pa5/part1
make clean

cd sshrestha11_pa5/part2
make clean
```