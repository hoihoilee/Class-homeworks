import time
import pickle
import random
from socket import *

SIZE = 5  #bingo size
BUFF = 1024  #socket receive buffer size

class Player:
    def __init__(self, uid):
        self.uid = uid  #user id
        self.bingo_lst, self.bingo_mat = self.__make_bingo()

    def __make_bingo(self):  #make random bingo for player
        bingo_lst = random.sample(list(range(1,100)), SIZE*SIZE)  #list type bingo
        bingo_mat = [bingo_lst[i*SIZE:(i+1)*SIZE] for i in range(SIZE)]  #matrix type bingo
        return (bingo_lst, bingo_mat)
    
    def remove_number(self, number):  #remove the number on the bingo / if one row bingo(win the game), return True
        if number not in self.bingo_lst:
            return False
        self.bingo_lst.remove(number)
        for i, row in enumerate(self.bingo_mat):
            if number not in row:
                continue
            j = row.index(number)
            row[j] = 0
            break
	#removed number position : (i, j)
        if self.bingo_mat[i] == [0]*SIZE:  #row bingo
            return True
        if [row[j] for row in self.bingo_mat] == [0]*SIZE:  #column bingo
            return True
        if i == j:
            if [self.bingo_mat[k][k] for k in range(SIZE)] == [0]*SIZE:  #diagonal bingo
                return True
        if i+j == SIZE-1:
            if [self.bingo_mat[k][SIZE-1-k] for k in range(SIZE)] == [0]*SIZE:  #anti-diagonal bingo
                return True
        return False

    def random_select(self):  #randomly select the number on the bingo (for pseudo player)
        return random.sample(self.bingo_lst, 1)[0]

if __name__ == '__main__' :
    serverSock = socket(AF_INET, SOCK_STREAM)
    serverSock.bind(('', 20653))  #open server socket(port : 20653)
    serverSock.listen(2)  #accept maximum 2 players

    mainSock, mainaddr = serverSock.accept()  #main culprit client
    main_id = mainSock.recv(BUFF).decode('utf-8')  #main culprit's user id
    print('Player \''+main_id+'\' connected')
    partSock, partaddr = serverSock.accept()  #copartner client
    part_id = partSock.recv(BUFF).decode('utf-8')  #copartner's user id
    print('Player \''+part_id+'\' connected')
    mainSock.send('main'.encode('utf-8'))
    partSock.send('part'.encode('utf-8'))
    mainSock.recv(BUFF).decode('utf-8')
    partSock.recv(BUFF).decode('utf-8')
    print('Game start')

    player_list = [Player(uid) for uid in [main_id, part_id, 'com1', 'com2', 'com3']]
    mainSock.send(pickle.dumps(player_list[0].bingo_mat))  #send initial bingo matrix
    partSock.send(pickle.dumps(player_list[1].bingo_mat))  #send initial bingo matrix
    mainSock.recv(BUFF).decode('utf-8')
    partSock.recv(BUFF).decode('utf-8')
    random.shuffle(player_list)  #shuffle the playing order
    mainSock.send(pickle.dumps([player.uid for player in player_list]))  #send playing order
    partSock.send(pickle.dumps([player.uid for player in player_list]))  #send playing order
    mainSock.recv(BUFF).decode('utf-8')
    partSock.recv(BUFF).decode('utf-8')
    
    number2 = 0
    curr = 0  #current player position
    while True:  #playing game
        player = player_list[curr]  #current player
        if player.uid == main_id:  #main culprit's turn
            mainSock.send('Y'.encode('utf-8'))
            partSock.send('N'.encode('utf-8'))
            number, number2 = pickle.loads(mainSock.recv(BUFF))
            partSock.recv(BUFF).decode('utf-8')
        elif player.uid == part_id:  #copartner's turn
            mainSock.send('N'.encode('utf-8'))
            partSock.send(('Y'+str(number2)).encode('utf-8'))
            mainSock.recv(BUFF).decode('utf-8')
            number = pickle.loads(partSock.recv(BUFF))
        else:  #pseudo player's turn
            mainSock.send('N'.encode('utf-8'))
            partSock.send('N'.encode('utf-8'))
            mainSock.recv(BUFF).decode('utf-8')
            partSock.recv(BUFF).decode('utf-8')
            time.sleep(3)  #pseudo player select the number for 3 seconds
            number = player.random_select()
        mainSock.send(('S'+str(number)).encode('utf-8'))  #send the selected number
        partSock.send(('S'+str(number)).encode('utf-8'))  #send the selected number
        mainSock.recv(BUFF).decode('utf-8')
        partSock.recv(BUFF).decode('utf-8')
        print(player.uid+' select : '+str(number))
        winner_list = []
        for player2 in player_list:  #update the all player's bingo matrix
            if player2.remove_number(number):
                winner_list.append(player2.uid)  #if one row bingo made, add the player to winner_list
            if player2.uid == main_id:
                mainSock.send(pickle.dumps(player2.bingo_mat))  #send the updated bingo matrix
            elif player2.uid == part_id:
                partSock.send(pickle.dumps(player2.bingo_mat))  #send the updated bingo matrix
        mainSock.recv(BUFF).decode('utf-8')
        partSock.recv(BUFF).decode('utf-8')
        if (len(winner_list) > 0):  #if there's a winner, the game ends
            break
        curr = (curr+1)%5  #next player position
    
    mainSock.send('W'.encode('utf-8'))  #send game end message
    mainSock.recv(BUFF).decode('utf-8')
    mainSock.send(pickle.dumps(winner_list))  #send winner_list
    partSock.send('W'.encode('utf-8'))  #send game end message
    partSock.recv(BUFF).decode('utf-8')
    partSock.send(pickle.dumps(winner_list))  #send winner_list
    print('Winner : '+str(winner_list))
