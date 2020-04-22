# Malloc

Malloc is a C pet-project from 42 course (task is available [here](ft_malloc.en.pdf)).

## About

This project was written to build your own allocator using system calls
and learn some allocation algorithms.

[Some info i was inspired by 1.](https://habr.com/ru/post/270009/) \
[Some info i was inspired by 2.](https://habr.com/ru/post/158347/)



## Download

#### If you want to build only libft_malloc

```bash
git clone [ref]
```

#### If you want to build allocation Visualizer

```bash
git clone --recursive [ref]
```

## Build libft_malloc.so

```bash
$> make
#
$> ls -l
lrwxr-xr-x   1 a17641238  staff       29 Apr 22 16:49 libft_malloc.so -> libft_malloc_x86_64_Darwin.so
-rwxr-xr-x   1 a17641238  staff    27680 Apr 22 16:49 libft_malloc_x86_64_Darwin.so
```

## Build allocation visualizer

```bash
$> brew install glfw3 
$> cd Visualizer
$> cmake . && make
```

## Usage

```bash
gcc main.c -L$DIR -lft_malloc.so
```
OR

```bash
./run.sh /usr/bin/time -l ./bin
```




