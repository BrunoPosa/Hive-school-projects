to test with high test coverage, run make and then the following command:

./test.sh 1 2 3 4 5 6 | grep "comparisons:" | awk '{print $2}' | sort -n | uniq -c | awk '{print $1 " results with " $2 " comparisons"}'

