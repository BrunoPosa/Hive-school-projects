#!/usr/bin/env bash
# test.sh
# Usage: ./test.sh 0 1 2 3   # will test all permutations of 0..3

permute() {
    local prefix=$1
    shift
    local items=("$@")

    if [ ${#items[@]} -eq 0 ]; then
        ./PmergeMe $prefix
    else
        for i in "${!items[@]}"; do
            local rest=("${items[@]:0:i}" "${items[@]:i+1}")
            permute "$prefix ${items[i]}" "${rest[@]}"
        done
    fi
}

permute "" "$@"
