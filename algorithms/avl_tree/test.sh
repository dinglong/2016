#!/bin/sh

echo "=== left route ==="
./avl datas/l.dat

echo "=== right route ==="
./avl datas/r.dat

echo "=== left-right route ==="
./avl datas/lr.dat

echo "=== right-left route ==="
./avl datas/rl.dat

