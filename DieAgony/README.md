# Die Agony

Approach:


We can only tip the dice in one of the cardinal directions if the following equation holds:
$$c = s + t \times n,$$

where
- the number on the cell in that cardinal direction is $c$
- the score before going to that square is $s$
- the next turn is the $t$-th turn 
- the number on the die-face that would be facing upwards is $n$ 

If there is already a number assigned to the die-face that would be facing upwards, 
we just check that the equation is satisfied. Otherwise, we have to check if there is an integer that would work as the value $n$, and remember that that die-face now has that number if there is one.

This is the grid. You start from the yellow and go to the blue:

<p align="center">
    <img src=img/die-agony.png>
</p>