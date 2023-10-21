[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/JPVokznx)
# homework1-integral  

## Compiling the code  
A Makefile is given in the directory, simply use ``make`` to compile the code. If you're compiling the code on a M-series Mac, add the ``MXMAC=1`` option:  
```bash
make MXMAC=1  
```
## Running the code  
You can run the code with:  
```bash
./integral [num_elements] [low] [high] [num_rounds]  
```
If not specified, the default values are ``num_elements=1000000000``, ``low=1``, ``high=2``, and ``num_rounds=3``.  

## Applying parallelism
Parallelize a for-loop:  
```C++
// sequential version  
for(int i = 0; i < n; i++) {
  f(i);
}
// parallel version  
parallel_for(0, n, [&](size_t i) {
  f(i);
});
```

Parallelize two statements:  
```C++
// sequential version
a += b;
c += d;
// parallel version
auto f1 = [&]() { a += b; };
auto f2 = [&]() { c += d; };
par_do(f1, f2);
```
