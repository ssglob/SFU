# a5.py

#
# Write the full name, SFU ID number, and SFU email of each member of your team:
# Edward Li Xuan Luo
# 301628166
# ell13@sfu.ca
#


#
# The TA will run your program by calling the main() function. Inside main() put
# whatever code you need for your program to run. It should only be one or two
# lines of code.
#

#
# import random for random turn order every round
#
import random

#
# Define a function to compare two rolls
#
def compare(roll1,roll2):
    #
    # Conditions: roll1 rank == roll2 rank
    #
    roll_vals = [100, 2, 3, 4, 5, 60]
    if roll1==roll2: # If they are tied (456 and 123 included)
        return 't'

    elif roll1.count(roll1[0]) == 3: # Both rolls are three in a row
        if roll1[0]>roll2[0]:
            return '1'
        else:
            return '2'
    else: # if both highest score and cur_score == 1
        dice_sum1 = sum([roll_vals[i-1] for i in roll1])
        dice_sum2 = sum([roll_vals[i-1] for i in roll2])
        if dice_sum1==dice_sum2:
            return 't'
        elif dice_sum1>dice_sum2:
            return '1'
        elif dice_sum2>dice_sum1:
            return '2'
        
#
# Define a function for the human turn
# Perform rolls and return a list containing the rolls, and the number of rolls used
#
def humanturn(max_rolls,prev_rolls):
    rolls_used = 0
    #
    # Only need to print out the dice for humanturn, so make them here
    # since dice rolls will be numbers can make it a list, and index would be
    # roll-1
    #
    dice = '''
+-----+   +-----+   +-----+
|     |   |     |   |     |
|     |   |     |   |     |
|     |   |     |   |     |
+-----+   +-----+   +-----+'''.strip() #Just add the o character to each dice
    dice = [list(i) for i in dice.split('\n')] # make the dice easier to edit
    #
    # for the coordinates of o, define a list and the index for the correct dice is roll-1
    #
    dice_coords = [
        [[2,3]], [[1,2],[3,4]], [[1,2],[2,3],[3,4]], [[1,2],[1,4],[3,2],[3,4]], 
        [[1,2],[1,4],[2,3],[3,2],[3,4]], [[1,2],[1,4],[2,2],[2,4],[3,2],[3,4]]
        ]

    roll_again = True # Make it false if the user doesn't want to roll again
    rolls = [] # Using a list, we can easily store the result of each roll

    while rolls_used < max_rolls and roll_again:
        rolls_used += 1
        rolls = [random.randint(1,6) for i in range(3)]

        print("Your rolls:")

        #copy the empty die
        cur_dice = [[] for i in dice]
        for c,i in enumerate(dice):
            cur_dice[c] = i[:]

        for count in range(3):
            #get coordinates of o relative to which dice the loop is on 
            coords = [[i[0],i[1] + count*10] for i in dice_coords[rolls[count]-1]]
            for item in coords:
                cur_dice[item[0]][item[1]] = 'o'
        print('\n'.join([''.join(i) for i in cur_dice]))
        print(rolls)
        print(f'Rolls left: {max_rolls-rolls_used}.',end=' ')
        
        #
        # make prev_rolls nicer to look at for the user
        #
        prev_rolls_as_str = []
        for lst in prev_rolls:
            string = ''
            for number in lst:
                string += str(number)
            prev_rolls_as_str.append(string)
        prev_rolls_as_str = ', '.join(prev_rolls_as_str)
        print(f'Previous rolls during this round: {prev_rolls_as_str}')

        yesorno = ' '
        if max_rolls-rolls_used > 0:
            yesorno = input('Roll again? y/n: ')
            print()
            while not yesorno in 'yn':
                print("Invalid input. Try again. Enter y for yes and n for no.")
                yesorno = input('Roll again? y/n: ')
                print()

            if yesorno == 'n':
                roll_again == False 
                break
    rolls.sort() #Return sorted rolls because it's easier to work with
    return [rolls,rolls_used]

#
# Define a function for robot turn
# Same as humanturn() but all automatic (won't ask for input)
#
def robotturn(max_rolls,Lowest_roll):
    '''CPU should try to roll until they beat the lowest roll, because the most
    important thing is to not lose. It does not matter if they have the highest score.'''
    rolls_used = 0
    rolls = [] # Using a list, we can easily store the result of each roll

    while rolls_used < max_rolls:
        rolls_used += 1
        rolls = [random.randint(1,6) for i in range(3)]
        rolls.sort() # sort rolls because it's easier to work with
        if rolls == [4,5,6]:
            break
        score = 1
        if rolls == [1,2,3]:
            score = 2
        elif rolls.count(rolls[0]) == 3:
            score = 3
        if Lowest_roll:
            if Lowest_roll[0]<score:
                break
            elif Lowest_roll[0]==score:
                if compare(Lowest_roll[1],rolls):
                    break

    return [rolls,rolls_used] 

#
# Define a function to print the round
#
def printround(cur_round):
    #
    # border is made up of + and -
    # there are 8 -'s for 3 spaces and 5 letters in round, + # of digits in cur_round
    #
    border = f'+{'-'*(8+len(str(cur_round)))}+'
    return f'{border}\n| Round {cur_round} |\n{border}'

#
# Define a function for the main game (calls the turn functions and keeps track of everything)
#
def game():
    #
    # Miscellaneous tasks (ask for name, print title, instructions)
    #
    username = input("What is your name? ")
    print('PocoLoco\n')
    print('''Instructions: PocoLoco is played in rounds.  
        In each round, players take turns rolling three dice and try to get the 
        highest score possible. After all the players have taken their turn in a round, 
        the lowest-scoring player is given chips from the other players as described below.
        The game ends when a player loses all their chips. 
        The first player with zero chips is the winner.
        
        Lowest-scoring player receives:
        1 chip if the winners score is a points total
        2 chips if the winners score is 1, 2, 3 (Loco!)
        3 chips if the winners score is any three-of-a-kind
        4 chips if the winners score is 4, 5, 6 (PoCo!)\n
          
        If there is a tie, the winner and loser are randomly selected.
        ''')
    #
    # define a dictionary that holds the chips of each player
    # the computers are p# where # is an integer greater than 1
    # player is username
    # define another dictionary for special rolls, another one for roll values
    #
    chips = {username: 10, 'p2': 10, 'p3': 10, 'p4': 10}

    #
    # start rounds
    #
    game_over = False
    cur_round = 1
    while not game_over:
        #
        # print and update current round
        #
        print(printround(cur_round))
        cur_round += 1

        #
        # print player names and their respective chips
        #
        print('Current chips:')
        for item in chips:
            print(f'{item}: {chips[item]} chips, ')

        players = list(chips.keys())
        round_rolls = {}
        max_rolls = 3
        prev_rolls = []
        Highest_roll = [] # [score, hand, player]
        Lowest_roll = [] # [score, hand, player]
        HTied = [] # list of all rolls tied with highest roll, clear after new highest roll
        LTied = [] # lis tall rolls tied with with Lowest roll, clear after new lowest roll

        for n in range(4):
            cur_player = players.pop(random.randint(0,3-n))

            if cur_player == username:
                round_rolls[cur_player],numofrolls = humanturn(max_rolls,list(round_rolls.values()))

            else:
                round_rolls[cur_player],numofrolls = robotturn(max_rolls,Lowest_roll)
            max_rolls = min(max_rolls,numofrolls)
            prev_rolls.append(round_rolls[cur_player])

            #
            # Calculate Player score
            #
            cur_roll = round_rolls[cur_player]

            if cur_roll == [4,5,6]:
                player_score = 4
            elif cur_roll.count(cur_roll[0]):
                player_score = 3
            elif cur_roll == [1,2,3]:
                player_score = 2
            else:
                player_score = 1

            #
            # Update Lowest and highest roll
            #
            if not Highest_roll or not Lowest_roll:
                Lowest_roll = [player_score,cur_roll,cur_player]
                Highest_roll = [player_score,cur_roll,cur_player]
                HTied.append(cur_player)
                LTied.append(cur_player)
            elif player_score>Highest_roll[0]:
                Highest_roll = [player_score,cur_roll,cur_player]
                HTied.clear()
                HTied.append(cur_player)
            elif player_score<Lowest_roll[0]:
                Lowest_roll = [player_score,cur_roll,cur_player]
                LTied.clear()
                LTied.append(cur_player)
            
            #
            # use compare function to compare the rolls
            #
            elif player_score==Highest_roll[0]:
                higher = compare(Highest_roll[1],cur_roll)
                if higher == 't':
                    HTied.append(cur_player)
                elif higher == '1':
                    continue
                elif higher == '2':
                    Highest_roll = [player_score,cur_roll,cur_player]
                    HTied.clear()
                    HTied.append(cur_player)

            elif player_score==Lowest_roll[0]:
                lower = compare(Lowest_roll[1],cur_roll)
                if lower == 't':
                    LTied.append(cur_player)
                elif lower == '1':
                    Lowest_roll = [player_score,cur_roll,cur_player]
                    LTied.clear()
                    LTied.append(cur_player)
                elif lower == '2':
                    continue
            
        #
        # decide winner/loser and calculate chips
        #
        winner = HTied[random.randint(0,len(HTied)-1)] # choose random winner if there is a tie
        loser = LTied[random.randint(0,len(LTied)-1)] # same as choosing winner

        for key in chips:
            if key == loser:
                chips[key] += Highest_roll[0] * 3
            else:   
                chips[key] -= Highest_roll[0]
            if chips[key] <= 0:
                chips[key] = 0
                game_over = True
        
        print(f'The winner of this round was {winner}. The loser of this round was {loser}.')
        print()
    highest_chips = 0 # loser
    winners = []
    losers = []

    for key in chips:
        if chips[key] == 0:
            winners.append(key)
        elif chips[key]>highest_chips:
            highest_chips = chips[key]
            losers.clear()
            losers.append(key)
        elif chips[key]==highest_chips:
            losers.append(key)
        
    print(f'''Winner of the game was {winners[random.randint(0,len(winners)-1)]}
            Loser of the game was {losers[random.randint(0,len(losers)-1)]}''')
    print(f'\nFinal chips of each player:')

    for key in chips:
        print(f'{key}: {chips[key]}')

def main():
    game()
main()