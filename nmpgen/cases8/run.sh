#!/bin/bash

for i in {0..8}
do
	python3 case$i.py case$i.shf case$i.out
done
