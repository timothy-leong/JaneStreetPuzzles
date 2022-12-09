# Die Agony

Approach:


We will index the faces of our die as follows 
(although the actual value of the die-face can be different):

<p align="center">
    <img src=img/die.png />
</p>

We can only tip the dice in one of the cardinal directions if the following equation holds:
$$c = s + t \times n,$$

where
- the number on the cell in that cardinal direction is $c$
- the current score is $s$
- the current turn is $t$ 
- the number on the die-face that would be facing upwards is $n$ 

If there is already a number assigned to the die-face that would be facing upwards, 
we just check that the equation is satisfied. Otherwise, we have to check if there is an integer that would work as the value $n$, and remember that that die-face now has that number if there is one.

During our backtracking, if we move to a square, we change its value to 0, to indicate that we have used this number already. If we find a satisfiable assignment of numbers to faces, such that we reach the last cell, we will then sum up all the values in the whole grid which would give us the sum of all unvisited squares from the die's journey.

This is the grid. You start from the yellow and go to the blue:

<p align="center">
    <img src=img/die-agony.png>
</p>