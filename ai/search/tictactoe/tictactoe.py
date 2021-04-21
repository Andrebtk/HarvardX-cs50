"""
Tic Tac Toe Player
"""

import math
import copy


X = "X"
O = "O"
EMPTY = None

board = [[X, O, X],
        [O, EMPTY, X],
        [EMPTY, EMPTY, O]]

print(board[0])
print(board[1])
print(board[2])
print("\n\n")

def initial_state():
    """
    Returns starting state of the board.
    """
    return [[EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY]]


def player(board):
    """
    Returns player who has the next turn on a board.
    """
    x_count = 0
    o_count = 0

    output = []
    """
    print("start player function")
    print(board)
    """
    #transform a 3d list to a simple list
    for temp in board:
        for elem in temp:
            output.append(elem)
         
    #print("output -> " + str(output))
    
    for i in range(len(output)):
        if output[i] == 'X':
            x_count += 1
        elif output[i] == 'O':
            o_count += 1
    """
    print("x -> " + str(x_count))
    print("o -> " + str(o_count))
    """
    if x_count == o_count:
        return 'X'
    else:
        return 'O'

def actions(board):
    """
    Returns set of all possible actions (i, j) available on the board.
    """
    i = -1
    j = -1
    total = 0
    cood = set()


    for x in board:
        """
        print("x -> " + str(x))
        print("i -> " + str(i))
        """
        i+=1
        j=-1
        for z in x:
            """
            print("j -> " + str(j))
            print("z -> " + str(z))
            """
            j+=1

            if z == None:
                total+=1
                cood.add((i,j))
    
    #print("total None: " + str(total))
    #print("cood : " + str(cood))

    return cood
            
    

def result(board, action):
    """
    Returns the board that results from making move (i, j) on the board.
    """
    if action not in actions(board): raise ValueError

    
    result = copy.deepcopy(board)
    result[action[0]][action[1]] = player(board)
    return result


def winner(board):
    """
    Returns the winner of the game, if there is one.
    """


    column0 = []
    column1 = []
    column2 = []

    diag0 = [board[0][0], board[1][1], board[2][2]]
    diag1 = [board[0][2], board[1][1], board[2][0]]
    


    for row in board:
        column0.append(row[0])
        
    for row in board:
        column1.append(row[1])

    for row in board:
        column2.append(row[2])

    """
    print("column0 -> " + str(column0))
    print("column1 -> " + str(column1))
    print("column2 -> " + str(column2))
    """


    if board[0][0]== X and board[0][1]== X and board[0][2] == X:
        return 'X'
    elif board[0][0]== O and board[0][1]== O and board[0][2] == O:
        return 'O'
    
    elif board[1][0]== X and board[1][1]== X and board[1][2] == X:
        return 'X'
    elif board[1][0]== O and board[1][1]== O and board[1][2] == O:
        return 'O'

    elif board[2][0]== X and board[2][1]== X and board[2][2] == X:
        return 'X'
    elif board[2][0]== O and board[2][1]== O and board[2][2] == O:
        return 'O'

    elif column0[0]== X and column0[1]== X and column0[2] == X:
        return 'X'
    elif column0[0]== O and column0[1]== O and column0[2] == O:
        return 'O'
    elif column1[0]== X and column1[1]== X and column1[2] == X:
        return 'X'
    elif column1[0]== O and column1[1]== O and column1[2] == O:
        return 'O'
    elif column2[0]== X and column2[1]== X and column2[2] == X:
        return 'X'
    elif column2[0]== O and column2[1]== O and column2[2] == O:
        return 'O'

    elif diag0[0]== O and diag0[1]== O and diag0[2] ==O:
        return 'O'
    elif diag0[0]== X and diag0[1]== X and diag0[2] ==X:
        return 'X'
    elif diag1[0]== O and diag1[1]== O and diag1[2] ==O:
        return 'O'
    elif diag1[0]== X and diag1[1]== X and diag1[2] ==X:
        return 'X'
    else:
        return None

def terminal(board):
    """
    Returns True if game is over, False otherwise.
    """
    values = []

    if winner(board) == 'X' or winner(board) == 'O': return True
    
    for x in board:
        for data in x:
            values.append(data)

    if None in values: return False
    else: return True 


def utility(board):
    """
    Returns 1 if X has won the game, -1 if O has won, 0 otherwise.
    """
    if winner(board) == 'X': return 1
    elif winner(board) == 'O': return -1
    else: return 0


def minimax(board):

    def maxValue(board):

        print("\nmaxValue\n")

        if terminal(board):
            return utility(board), None

        z = -100
        move = None
        for act in actions(board):
            print("act ->" + str(act))
            value = result(board, act)
            print("value -> " + str(value))

            uti, move = miniValue(value)
            print("uti -> " + str(uti))
            print("move -> " + str(move))

            
            if uti > z:
                z = uti
                move = act
                if z == 1:
                    print("final")
                    print("act ->" + str(move))
                    return z, move

        return z, move
            

        
    def miniValue(board):

        print("\nminiValue\n")

        if terminal(board):
            return utility(board), None

        z = 100
        move = None
        for act in actions(board):
            print("act -> " + str(act))
            value = result(board, act)
            print("value -> " + str(value))
            uti, move = maxValue(value)
            print("uti -> " + str(uti))
            print("move -> " + str(move))

            if uti < z:
                z = uti
                move = act
                if z == -1:
                    print("final")
                    print("act ->" + str(move))
                    return z, move
            

        return z, move
        


        
    CurrentPlayer = player(board)


    if CurrentPlayer == X:
        uti, bestMove = maxValue(board)
        return bestMove
    else:
        uti, bestMove = miniValue(board)    
        return bestMove