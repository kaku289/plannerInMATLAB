%% Problem SS-1 Q =3 Exact

Found incumbent of value 3041.838564 after 0.08 sec. (36.70 ticks)
Tried aggregator 1 time.
MIP Presolve eliminated 0 rows and 169656 columns.
MIP Presolve added 38456 rows and 38456 columns.
Reduced MIP has 38505 rows, 131365 columns, and 537848 nonzeros.
Reduced MIP has 92908 binaries, 38456 generals, 0 SOSs, and 0 indicators.
Presolve time = 3.42 sec. (2664.71 ticks)
Elapsed time = 100.06 sec. (10000.46 ticks) for 19% of probing
Elapsed time = 202.80 sec. (20002.00 ticks) for 39% of probing
Probing time = 246.30 sec. (24094.72 ticks)
Tried aggregator 2 times.
Aggregator did 38456 substitutions.
Reduced MIP has 49 rows, 92909 columns, and 460936 nonzeros.
Reduced MIP has 92908 binaries, 0 generals, 0 SOSs, and 0 indicators.
Presolve time = 2.97 sec. (3310.06 ticks)
Tried aggregator 1 time.
Reduced MIP has 49 rows, 92909 columns, and 460936 nonzeros.
Reduced MIP has 92908 binaries, 0 generals, 0 SOSs, and 0 indicators.
Presolve time = 0.39 sec. (153.52 ticks)
Probing time = 0.56 sec. (66.59 ticks)
Clique table members: 41.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 4 threads.
Root relaxation solution time = 2.80 sec. (898.44 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                         3041.8386        0.0000      378  100.00%
      0     0      573.8646    42     3041.8386      573.8646      378   81.13%
*     0+    0                          740.9829      573.8646      378   22.55%
      0     0      577.0737     6      740.9829       Cuts: 3      385   22.12%
*     0+    0                          634.8644      577.0737      385    9.10%
*     0+    0                          615.0918      577.0737      385    6.18%
*     0+    0                          603.9758      577.0737      385    4.45%
Clique cuts applied:  2
Gomory fractional cuts applied:  1

Root node processing (before b&c):
  Real time             =  262.44 sec. (33575.58 ticks)
Parallel b&c, 4 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =  262.44 sec. (33575.58 ticks)
Time taken for computation (s)

ans =

  262.8466

Warning: Ignoring extra legend entries. 
> In legend>set_children_and_strings (line 629)
  In legend>make_legend (line 321)
  In legend (line 250)
  In runMTVRP (line 132) 
---- Vehicle1 ----
  Columns 1 through 12

     0    20    19     0     1     2     3     0    23    22    21     0

  Columns 13 through 16

    27    28    31     0

---- Vehicle2 ----
  Columns 1 through 12

     0     6     5     4     0     7     8     9     0    13    14    15

  Column 13

     0

---- Vehicle3 ----
  Columns 1 through 12

     0    12    11    10     0    18    17    16     0    26    25    24

  Columns 13 through 17

     0    32    34    35     0

---- Vehicle4 ----
  Columns 1 through 12

     0    29    30    33     0    38    37    36     0    39    40    41

  Column 13

     0

---- Maximum Journey Time (s) ----
  603.9758
 
size(aa) = [          41       65641];




%%