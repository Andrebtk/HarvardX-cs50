from logic import *

AKnight = Symbol("A is a Knight")
AKnave = Symbol("A is a Knave")

BKnight = Symbol("B is a Knight")
BKnave = Symbol("B is a Knave")

CKnight = Symbol("C is a Knight")
CKnave = Symbol("C is a Knave")

# Puzzle 0
# A says "I am both a knight and a knave."


knowledge0 = And(

    Not(And(AKnight, AKnave)),
    Or(AKnight, AKnave),
    Implication(AKnight, And(AKnight, AKnave)),
    Implication(AKnave, Not(And(AKnight, AKnave)))
)

# Puzzle 1
# A says "We are both knaves." -> P
# B says nothing.              -> Q


print(Implication(AKnight, And(AKnave, BKnave)).formula())
print(Implication(AKnave, Not(And(AKnave, BKnave))).formula())

knowledge1 = And(
    Not(And(AKnight, AKnave)),  
    Or(AKnight, AKnave),       
    Not(And(BKnight, BKnave)),  
    Or(BKnight, BKnave),        


    Implication(AKnight, And(AKnave, BKnave)),
    Implication(AKnave, Not(And(AKnave, BKnave)))
)




# Puzzle 2
# A says "We are the same kind."
# B says "We are of different kinds."

knowledge2 = And(
    Not(And(AKnight, AKnave)),  
    Or(AKnight, AKnave),       
    Not(And(BKnight, BKnave)),  
    Or(BKnight, BKnave),

    Implication(AKnight, And(AKnight, BKnight)),
    Implication(AKnave, Not(And(BKnight, AKnight))),
    Implication(BKnight, AKnave),
    Implication(BKnave, Not(AKnave))
)



# Puzzle 3
# A says either "I am a knight." or "I am a knave.", but you don't know which.
# B says "A said 'I am a knave'."
# B says "C is a knave."
# C says "A is a knight."

knowledge3 = And(
    
    Not(And(AKnight, AKnave)),  
    Or(AKnight, AKnave),       
    Not(And(BKnight, BKnave)),  
    Or(BKnight, BKnave),
    Not(And(CKnight, CKnave)),  
    Or(CKnight, CKnave),



    Or(
        #A says 'I am a knight'
        And(Implication(AKnight,AKnight), Implication(AKnave, Not(AKnight))),
        #A says 'I am a knave'
        And(Implication(AKnight,AKnave), Implication(AKnave, Not(AKnave)))
    ),

    #B says "A said 'I am a knave'"
    Implication(BKnight, And(Implication(AKnight, AKnave), Implication(AKnave, Not(AKnave)))),        
    Implication(BKnight, Not(And(Implication(AKnight, AKnave), Implication(AKnave, Not(AKnave))))),

    
    #B says 'C is a knave'
    Implication(BKnight, CKnave),
    Implication(BKnave, CKnight),

    #C says 'A is a knight'

    Implication(CKnight, AKnight),
    Implication(CKnave, AKnave)

)


def main():
    symbols = [AKnight, AKnave, BKnight, BKnave, CKnight, CKnave]
    puzzles = [
        ("Puzzle 0", knowledge0),
        ("Puzzle 1", knowledge1),
        ("Puzzle 2", knowledge2),
        ("Puzzle 3", knowledge3)
    ]
    for puzzle, knowledge in puzzles:
        print(puzzle)
        if len(knowledge.conjuncts) == 0:
            print("    Not yet implemented.")
        else:
            for symbol in symbols:
                if model_check(knowledge, symbol):
                    print(f"    {symbol}")


if __name__ == "__main__":
    main()
