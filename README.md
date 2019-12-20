# Dijkstra互斥算法实现
用C++实现的[Solution of a Problem in Concurrent Programming Control](https://www.di.ens.fr/~pouzet/cours/systeme/bib/dijkstra.pdf)算法

## 环境要求
Linux

## 编译

```
make
```

## 需要在Linux下运行

```
# 单核
taskset -c 1 ./lock

# 多核, 由于多核缓存不一致，存在冲突，需要利用atomic保护
taskset -c 1,2,3 ./lock
```