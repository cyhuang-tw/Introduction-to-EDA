#!/bin/bash

for i in {0..8}
do
	python3 verify.py case$i.json case$i.out
done
