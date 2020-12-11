\ENCODING=ISO-8859-1
\Problem name: IloCplex

Maximize
 obj1: 0.11 X(0) + 0.04 X(1) + 0.02 X(2)
Subject To
 c1: 5 X(0) >= 400
 c2: 3.33333333333333 X(1) >= 800
 c3: 2.5 X(2) >= 10000
 c4: 5 X(0) + 3.33333333333333 X(1) + 2.5 X(2) <= 200000
 c5: X(0) + X(1) + X(2) <= 60000
End
