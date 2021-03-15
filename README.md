# 42_miniRT



## Prerequisite

```
sudo apt install libx11-dev x11proto-core-dev libxt-dev libbsd-dev gcc
```

## Compiles for miniRT

```
make
```



## Compiles step by step

### Clone minilibx-linux from git repository

```
make minilibx-linux
```

### Compiles minilibx-linux library

```
make minirt/libmlx.a
```

### Compiles miniRT

```
make minirt/miniRT
```

