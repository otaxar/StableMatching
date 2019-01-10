# StableMatching

This program demostrates a Gale-Shapley algorithm used on Stable Matching problem.

There is a group of n men and n women. Each man ranks all women by his preferences. 
                                       Each woman ranks all men by her preferences.

The goal is to find a SET of PERFECT MATCHING (each man and woman has a partner) without instability.
Instability means that:
- there is some man m that prefers other woman his current partner
- there is some woman w prefers m over her current partner
- and they can improve their partner by joint action.
