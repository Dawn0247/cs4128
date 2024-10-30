# Problem Diary
Problem diaries for cs4128 programming challenges.
## Week 1
Week 1 problems: Programming Paradigms.
### Baby bites
This was quite a simple question, read through the input word by word. If the word was 'mumble' treat it as if it were the correct next number in the sequence. If a number didn't match the running counter then output "something is fishy". If we reach the end of the input, then output "makes sense".

### Alternating Subsequence
Iterate through the input and keep track of the largest number before the sign changes. Add this number to a running sum. Output this sum for each set of numbers in the input.

### Jumbled String
The first few things to notice is the conditions in which the formation of the string is impossible. The number of 11's and 00's must be a triangle number, and the number of 01's and 10's should be closely related to the number of 11's and 00's. 

By considering a string only composed of $n$ 0's, by inserting a 1 between position $i$ and $i+1$, indexed from 0, we create ceate $i$ 01's and $n-i$ 10's. This means for every inserted 1, we create $n$ 01's and 10's. This implies that if we work out the number of 1's and 0's (from the triangle number). We can form the relationship to check for validity: $n_{0}\times n_{1} = n_{10} + n_{01}$, where $n_i$ denote the number of occurances of the pattern $i$.

Knowing this, we can construct out string by first placing the required number of 0's and then placing 1's at the end greedily until the number of 01's exceed the number we'll get per insert, then we'll decide on a position in the middle to place the last few.

### Riverside Curio
This question can be done greedily with 2 iterations of the input array. On the first iteration we determine the minimum amount of marks naively required per day based on the previous day and the number of marks above the water by the following condition $\mathrm{max}(m_{i}+1, t_{i-1})$, where $m_i$ denotes the number of marks above water on day $i$ and $t_i$ denotes the marks on day $i$.

Since Arkady can only place one mark a day, you can then iterate backwards through the array $t$ and increment numbers as required to ensure the number of marks per day is consecutive.

From by summing the differences, we can work out the total amount of marks stricly below water.

### The Fair Nut and Strings
when i wrote the code only god and i knew what was going on, now only god knows.

### Inversion Swapsort
Considering bubble sort, each swap reduces the number of inversions by one. Thus, by running bubble sort an tracking the indexes being swapped, we can track the inversion swaps required to sort the array.

## Week 2
Week 2 problems: Data Structures.

### Classrooms
We start by sorting the activities by end time using a min-heap. We keep another min-heap of the each classroom's respective current activity end time intialised to 0.

Iterating through our acitvities, if we any of the new activities can start in any classroom. Say, classroom 2 ends at time 2, and activity 3 starts at time 3, activity 3 can be started in classroom 2. We update that value in the min-heap to the new end time. If no activity can be started, move onto the next activity.

Keep a running count of the number of activities started and output that at the end.

### Minimal String
This can be done greedily using by grabbing next most lexographically minimal character in the string and adding that to our output sting. The other characters before that character goes into array $t$ in reverse. When we reach the end of the string we can append $t$ onto the end of the string.

### Preparing for the Contest
This question had an intial thought of solving it greedily by assigning the best student the hardest questions. The time complexity of this was too high and wouldn't be able to solve the question.

Instead by considering if the set of bugs could be solved in $n$ amount of days, by preprocessing sorting our bugs in descending difficulty and students in descending skill we can simply assign the first $n$ most difficult questions to the most skilled student. Continue assigning these and if we run out of students, this means the problem cannot be solved in $n$ days. Otherwise it can.

By running a binary search on the possibility of the bugs being solved in n days, we can find the minimal amount of days. This is fast enough in $n\mathrm{log}n$ time.

### The Problem Set
This question is a implementation of a range tree tracking maximal, sum and a standardised way. However, for increasing, the query can be implemented by checking if both the left and right ranges are increasing, then checking that the maximal value on the left is less than the mininmal value on the right. A similar idea can be implemented for the descending query.

## Week 3
Week 3 problems: Dynamic Programming

### Basketball Exercise
In this problem, the key idea to note is that there is no reason to skip more than 2 players in a team. As you should be able to simply take both. With this in mind we can set up the recurrance:
$$\mathrm{dp}(i, r) = \mathrm{max}(\mathrm{dp}(i-1, 1-r),\ \mathrm{d}(i-2, 1-r)) + \mathrm{cost}[i][r]$$
With $r$ representing either team 0 or 1 to take from, and $i$ being the index. $\mathrm{dp}(i, r)$ represents the maximal total height up to index $i$ ending at team $r$.

### Kefa and Dishes
Due to the small input size, we can immediately deduce this is a bitset dp question. We can setup the base case for this question as Kefa starting by eating any of the dishes. Doing a bottom-up approach we have the recurrance:
$$\mathrm{dp}(\mathrm{mask}\ | \ (1 << j), \ j) = \mathrm{dp}(\mathrm{mask}, \ i) + s_i + b_{ij}$$
Where $j$ is the next dish to eat, $i$ is the current dish, $\mathrm{mask}$ is the current bitset, $s_i$ is the satisfaction from dish $i$, $b_{ij}$ is the satisfation gained from eating $j$ after $i$ if it exists.

We can output the maximum value of dp table which the number of 1's in the bitset is equal to $m$.

### Colouring Trees
Due to the relatively small input size, the question is most likely going to be a multidimensional dp question with complexity $O(n^4)$.

We can define the dp state as the min cost to first i trees beauty j, with the previous colour k.

$$\mathrm{dp}(i, j, k)$$

We can setup the base case as the cost to paint the first tree (if uncoloured) all of its colours.

$$ \mathrm{dp}(0, 1, k) = c_{0,k}$$

Where $c_{i,k}$ is the cost to paint tree $i$ colour $k$.

Following this we can setup the following recurrance relations.

$$ 
\text{dp}(i,j,k)= \begin{cases}
   \min(\ \text{dp}(i-1, j, k), \ \text{dp}(i-1, j-1, \forall k'\neq k)\ ) + p_{i,k} &\text{if } t_i \text{ is uncoloured}, \\
   \min(\ \text{dp}(i-1, j, k), \ \text{dp}(i-1, j-1, \forall k'\neq k) \ ) &\text{if } t_i \text{ has colour } k.
\end{cases}
$$

We can interpret the result as the minimum of the values in the dp table with beauty $k$ and tree $n-1$.

### Wifi
This question is identical to the segment cover question within the lecture slides. We can just generate the segments from the input as $[i, i]$ with cost $i$, if there isn't a router. $[\max(1, i-k), \min(n, i+k)]$ with cost $i$ if there is a router.

After this, we follow the exact same steps as the solution within th lecture slides.

## Week 4
Week 4 problems: Graphs.
### Heirarchy
This question was quite a simple idea and could be solved without any graph knowledge. By using a greedy method