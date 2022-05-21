#/bin/bash

sum=0
for (( i = $1; i > 0 ; i = i/10 )); do
    sum=$(( $sum + $i%10))
done
echo $sum