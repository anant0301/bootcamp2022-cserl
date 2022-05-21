#/bin/bash

arr=( "man" "bear" "pig" "dog" "cat" "sheep" )

for string in ${arr[@]}; do
    echo $string
done