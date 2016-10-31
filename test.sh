#! /bin/bash
PROG=$1
BRUTE="brute_"$1
GEN="gen_"$1
IN=$1".in"
OUT=$1".out"
BOUT="brute_"$1".out"

make $PROG;
make $GEN;
make $BRUTE;

for i in `seq 1 $2`;
do
    # echo $i
    ./$GEN > $IN;
    ./$PROG < $IN > $OUT;
    ./$BRUTE < $IN > $BOUT;
    if ! diff $BOUT $OUT;
        then
            echo $i
            break
    fi
done
