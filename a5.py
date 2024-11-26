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
# Import random for random turn order every round
# Import time so that each print is not instant
#
import random
import time

#
# Define a function to add the score of a roll
#
def add_score(roll):
    roll_vals = [100, 2, 3, 4, 5, 60] # Index for number's value is number-1
    return sum([roll_vals[i-1] for i in roll])

#
# Define a function to compare two rolls
#
def compare(roll1,roll2):
    #
    # 1 means roll1 was better, 2 means roll2 was better, t means they're tied
    #


    if roll1==roll2: # If they are tied (456 and 123 included)
        return 't'

    elif roll1.count(roll1[0])==3 and roll2.count(roll2[0])==3: # Both rolls are three in a row
        #
        # Any tied three in a rows are caught by the tied condition
        #
        if roll1[0]>roll2[0]:
            return '1'
        else:
            return '2'
    else: # If both highest rank and current rank==1
        dice_sum1 = add_score(roll1)
        dice_sum2 = add_score(roll2)
        if dice_sum1==dice_sum2:
            return 't'
        elif dice_sum1>dice_sum2:
            return '1'
        elif dice_sum2>dice_sum1:
            return '2'
        
#
# Define a function to sort a list of rolls
#
def sort_rolls(dict):
    players = list(dict.keys())
    left = [players[0],players[1]]
    right = [players[2],players[3]]
    result = []
    #
    # Compare rolls on the left and on the right, then merge the sorted lists
    # The only case in which we must switch the order is if the second player
    # had a higher roll
    #
    if dict[left[0]][1] == dict[left[1]][1]:
        if compare(dict[left[0]][0],dict[left[1]][0]) == '2':
            left = left[::-1]
    elif dict[left[0]][1] < dict[left[1]][1]:
        left = left[::-1]
    
    if dict[right[0]][1] == dict[right[1]][1]:
        if compare(dict[right[0]][0],dict[right[1]][0]) == '2':
            right = right[::-1]
    elif dict[right[0]][1] < dict[right[1]][1]:
        right = right[::-1]
    
    while left and right:
        if dict[left[0]][1] == dict[right[0]][1]:
            if compare(dict[left[0]][0],dict[right[0]][0]) in '1t':
                result.append(left.pop(0))
            else:
                result.append(right.pop(0))
        elif dict[left[0]][1] > dict[right[0]][1]:
            result.append(left.pop(0))
        elif dict[left[0]][1] == dict[right[0]][1]:
            winner = random.choice([left,right])
            result.append(random.choice(winner.pop(0)))
        else:
            result.append(right.pop(0))

    if left:
        result.extend(left)
    elif right:
        result.extend(right)
    
    return result

#
# Define a function for the human turn
# Perform rolls and return a list containing the rolls, and the number of rolls used
#
def humanturn(max_rolls,prev_rolls):
    rolls_used = 0
    #
    # Only need to print out the dice for humanturn, so make them here
    # Since dice rolls will be numbers make it a list, and index would be
    # roll-1
    #
    dice = '''
+-----+   +-----+   +-----+
|     |   |     |   |     |
|     |   |     |   |     |
|     |   |     |   |     |
+-----+   +-----+   +-----+
   #         #         #'''.strip() # Just add the o characters to each dice
    #
    # Make the dice easier to edit by making it a list
    #
    dice = [list(i) for i in dice.split('\n')]
    #
    # For the coordinates of o, define a list and the index for the correct dice is roll-1
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

        #
        # Copy the empty die
        #
        cur_dice = [[] for i in dice]
        for c,i in enumerate(dice):
            cur_dice[c] = i[:]

        for count in range(3):
            #get coordinates of o relative to which dice the loop is on
            coords = [[i[0],i[1] + count*10] for i in dice_coords[rolls[count]-1]]
            for item in coords:
                cur_dice[item[0]][item[1]] = 'o'

        #
        # Replace '#'s in the dice with the number that dice rolled
        #
        for num in rolls:
            ind = cur_dice[-1].index('#')
            cur_dice[-1][ind] = str(num)

        print('\n'.join([''.join(i) for i in cur_dice]))
        print(f'Rolls left: {max_rolls-rolls_used}.',end=' ')
        
        #
        # Make prev_rolls nicer to look at for the user
        #
        if prev_rolls:
            prev_rolls_as_str = []
            for lst in prev_rolls:
                string = ''
                for number in lst:
                    string += str(number)

                prev_rolls_as_str.append(string)

            prev_rolls_as_str = ', '.join(prev_rolls_as_str)
            print(f'Previous rolls during this round: {prev_rolls_as_str}')
        
        else:
            print('There were no previous rolls during this round.')

        yesorno = ' '
        if max_rolls-rolls_used > 0:
            yesorno = input('Roll again? y/n: ')
            print()
            while not yesorno in 'yn':
                print("Invalid input. Try again. Enter y for yes and n for no.")
                yesorno = input('Roll again? y/n: ')

            if yesorno=='n':
                roll_again==False 
                break

    time.sleep(1.0)
    print()
    rolls.sort() # Return sorted rolls because it's easier to work with
    return [rolls,rolls_used]

#
# Define a function for robot turn
# Same as humanturn() but all automatic (won't ask for input)
#
def robotturn(max_rolls,Lowest_roll):
    '''CPU should try to roll until they beat the lowest roll, because the most
    important thing is to not lose. It does not matter if they have the highest rank.
    If it's first then it should try to roll until it gets a Loco, a three-of-a-kind,
    a Poco, or have a 1 or two 6's in the roll'''
    rolls_used = 0

    while rolls_used < max_rolls:
        rolls_used += 1
        rolls = [random.randint(1,6) for i in range(3)]
        rolls.sort() # sort rolls because it's easier to work with
        if rolls==[4,5,6]:
            break
        rank = 1
        if rolls==[1,2,3]:
            rank = 2
        elif rolls.count(rolls[0])==3:
            rank = 3

        if Lowest_roll:
            if Lowest_roll[0]<rank:
                break
            elif Lowest_roll[0]==rank:
                if compare(Lowest_roll[1],rolls) == '2':
                    break

        else:
            if rolls in [[1,2,3],[4,5,6]]: # Poco or Loco
                break
            elif rolls.count(rolls[0])==3: # Three of a kind
                break
            elif 1 in rolls or (6 in rolls and rolls.count(6)>1):
                break

    return [rolls,rolls_used] 

#
# Define a function to print the round
#
def printround(cur_round):
    #
    # Border is made up of + and -
    # There are 8 -'s for 3 spaces and 5 letters in round, + # of digits in cur_round
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
    chipnum = input("How many chips do you want everyone to start with? ")
    while not chipnum.isdigit():
        print("Please enter a positive integer.")
        chipnum = input("How many chips do you want everyone to start with? ")
    chipnum = int(chipnum)

    print()
    print('PocoLoco\n')
    time.sleep(1.0)
    print('''Instructions: 
PocoLoco is played in rounds.
In each round, players take turns rolling three dice and try to get the
highest score possible. After all the players have taken their turn in
a round, the lowest-scoring player is given chips from the other players
as described below. If a player doesn't have a special hand, (Loco, Poco,
or three-of-a-kind) then the rank is calculated based on the score. The
score is calculated by adding the score from each dice. The value of each
roll is as follows (roll: score):
1: 100   4: 4
2: 2     5: 5
3: 3     6: 60

Lowest-scoring player receives:
1 chip if the winners score is a points total
2 chips if the winners score is 1, 2, 3 (Loco!)
3 chips if the winners score is any three-of-a-kind
4 chips if the winners score is 4, 5, 6 (PoCo!)\n
        
The game ends when a player loses all their chips.
The first player with zero chips is the winner.
    
If there is a tie, the winner and loser are randomly selected.
''')
    #
    # Ask for an input to pause until they finish reading the instructions
    #
    input("Enter any key to continue when you are ready. ")
    print()
    #
    # Define a dictionary that holds the chips of each player
    # The computers are p# where # is an integer greater than 1
    # Player is username
    #
    chips = {username: chipnum, 'Player 2': chipnum, 'Player 3': chipnum, 'Player 4': chipnum}

    #
    # Start rounds
    #
    game_over = False
    cur_round = 1
    while not game_over:
        #
        # Print and update current round
        #
        print(printround(cur_round))
        print()
        cur_round += 1
        time.sleep(1.0)

        #
        # Print player names and their respective chips
        #
        print('Current chips:')
        for item in chips:
            print(f'{item}: {chips[item]} chips, ')
        print()

        #
        # Define game variables
        #
        players = list(chips.keys())
        round_rolls = {}
        round_roll_names = {}
        max_rolls = 3
        prev_rolls = []
        Highest_roll = [] # [rank, hand, player]
        Lowest_roll = [] # [rank, hand, player]
        HTied = [] # List of all rolls tied with highest roll, clear after new highest roll
        LTied = [] # List of all rolls tied with with Lowest roll, clear after new lowest roll

        #
        # Choose order of the players
        #
        order = [players.pop(random.randint(0,3-n)) for n in range(4)]
        print('Order for this round:')
        #
        # Print the order
        #
        for count,item in enumerate(order):
            print(f'{count+1}: {item}')
        print()
        time.sleep(2.0)

        for cur_player in order:
            if cur_player==username:
                player_turn = humanturn(max_rolls,prev_rolls)
                round_rolls[cur_player],numofrolls = player_turn

            else:
                round_rolls[cur_player],numofrolls = robotturn(max_rolls,Lowest_roll)
                
            max_rolls = min(max_rolls,numofrolls)

            #
            # Calculate the roll's rank
            #
            roll = ''
            cur_roll = round_rolls[cur_player][:]

            if cur_roll==[4,5,6]:
                player_rank = 4
                roll = 'PoCo!'
            elif cur_roll.count(cur_roll[0])==3:
                player_rank = 3
                roll = 'Three of a kind'
            elif cur_roll==[1,2,3]:
                player_rank = 2
                roll = 'Loco!'
            else:
                player_rank = 1
                roll = f'score: {str(add_score(cur_roll))}'
            round_roll_names[cur_player] = roll
            round_rolls[cur_player] = [round_rolls[cur_player],player_rank]
            prev_rolls.append(round_rolls[cur_player][0])

            #
            # Update Lowest and highest roll
            #
            if not Highest_roll or not Lowest_roll: # First turn
                Lowest_roll = [player_rank,cur_roll,cur_player]
                Highest_roll = [player_rank,cur_roll,cur_player]
                HTied.append(cur_player)
                LTied.append(cur_player)
            elif player_rank>Highest_roll[0]:
                Highest_roll = [player_rank,cur_roll,cur_player]
                HTied = [cur_player]
            elif player_rank<Lowest_roll[0]:
                Lowest_roll = [player_rank,cur_roll,cur_player]
                LTied = [cur_player]
            
            #
            # Use compare function to compare the rolls
            #
            else:
                if player_rank==Highest_roll[0]:
                    higher = compare(Highest_roll[1],cur_roll)
                    if higher=='t':
                        HTied.append(cur_player)
                    elif higher=='2':
                        Highest_roll = [player_rank,cur_roll,cur_player]
                        HTied = [cur_player]

                if player_rank==Lowest_roll[0]:
                    lower = compare(Lowest_roll[1],cur_roll)
                    if lower=='t':
                        LTied.append(cur_player)
                    elif lower=='1':
                        Lowest_roll = [player_rank,cur_roll,cur_player]
                        LTied = [cur_player]
            
        #
        # decide winner/loser and calculate chips
        # base winner/loser on sorted_rolls to keep it consistent with the rankings
        #
        sorted_rolls = sort_rolls(round_rolls)
        winner = sorted_rolls[0]
        loser = sorted_rolls[-1]
        chip_diff = {}

        for key in chips:
            if key==loser:
                chips[key] += Highest_roll[0] * 3
                chip_diff[key] = '+' + str(Highest_roll[0] * 3)
            else:
                chips[key] -= Highest_roll[0]
                chip_diff[key] = '-' + str(Highest_roll[0])
            if chips[key] <= 0:
                chips[key] = 0
                game_over = True

        print('Rolls from this round (sorted):')
        for count,key in enumerate(sorted_rolls):
            player_roll = ''.join([str(i) for i in round_rolls[key][0]])
            roll_name = round_roll_names[key]
            print(f'{count+1}. {key}: {player_roll} ({roll_name})',end=' ')
            print(f'{chip_diff[key]} chips')
        print()
        
        print(f'The winner of this round was {winner}. The loser of this round was {loser}.')
        print()
        #
        # Ask for input so the user decides when to continue to the next round
        #
        input("Enter any key to continue to the next round. ")
        print()

    highest_chips = 0 # Loser has the highest chips, there must be at least 1 loser
    winners = []
    losers = []

    for key in chips:
        if chips[key]==0:
            winners.append(key)
        elif chips[key]>highest_chips:
            highest_chips = chips[key]
            losers = [key]
        elif chips[key]==highest_chips:
            losers.append(key)
    
    print('Game over.')
    print()
    print(f'''Winner of the game was {winners[random.randint(0,len(winners)-1)]}
Loser of the game was {losers[random.randint(0,len(losers)-1)]}''')
    print(f'\nFinal chips of each player:')

    for key in chips:
        print(f'{key}: {chips[key]}')

def main():
    game()