#!/bin/bash

for i in {0..8}
do
	python3 shuffle.py case$i.json case$i.shf
done
