#!/bin/bash

for i in {0..8}
do
	./nmpgen case$i.json case$i.py
done
