#Jeśli testowany program nazywa się "a", to generatorka musi nazywać się "gen_a", a brute "brute_a".
#Na wejściu podajemy nazwę pliku i liczbę testów, które chcemy wykonać.
#Program kończy działanie jeśli wykona wszystkie testy, bądź jeśli na pewnym teście program i brute dadzą inny wynik.
#W tym drugim przypadku wypisze numer testu na konsolę, plik in będzie zawierał wejście na którym były różne wyniki, a pliki out wyjścia.
#Nie wiem jak działa ten diff, pewnie trzeba uważać na białe znaki, ale to chyba nie jest wielki problem.

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
    ./$GEN $i > $IN;
    ./$PROG < $IN > $OUT;
    ./$BRUTE < $IN > $BOUT;
    if ! diff $BOUT $OUT;
        then
            echo $i
            break
    fi
done
