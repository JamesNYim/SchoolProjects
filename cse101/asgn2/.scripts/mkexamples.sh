#!/bin/bash

[[ $# -ne 1 ]] && exit 1

OUTPUT_DIR=$1
SEEDS=(0 5 100 999)
X=(5 10 17 30 50 500)
Y=(5 10 30 37 50 500)

for s in ${SEEDS[@]}; do
    for x in ${X[@]}; do
        for y in ${Y[@]}; do
            FNAME=${s}_${x}x${y}
            ./generator -s $s -x $x -y $y -o ${OUTPUT_DIR}/$FNAME.dat -p ${OUTPUT_DIR}/$FNAME.ppm
        done
    done
done
