## Ford-Johnson merge insertion sort

This exercise is one of the more fun ways to learn to use a couple STL containers. Most of the meat here is implementing this very specific algorithm which optimizes for number of comparisons. Key concepts are element pairing, recursion, Jacobstahl sequence, and binary search. Here is the description:

![Algorithm](./img/ford-johnson_merge_insertion.png)



## Testing

to test with high coverage, run `make` and then the following command with any positive integers:

```./test.sh 1 2 3 4 5 6 | grep "comparisons:" | awk '{print $2}' | sort -n | uniq -c | awk '{print $1 " results with " $2 " comparisons"}'```

The output might take a while depending how many numbers are given. Comparison count should never exceed F(n) values from the table. 


![Screenshot](./img/screenshot.png)




## Step by step

To better understand the steps of the sorting, run `make trace`.
The program works with positive numbers only, and '-1' in the trace screenshot means there is no pairless number in B.

![Trace](./img/trace.png)



## Notes

I understood from [leske42's great guide](https://github.com/leske42/CPP09) that the best use case for this algorithm would be for sorting elements which are expensive to compare, not simple integers. 
