import sys
import time
import pickle
from socket import *
from PyQt5 import uic
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *

BUFF = 1024  #socket receive buffer size
form_class = uic.loadUiType('bingo.ui')[0]  #load GUI form

class WindowClass(QMainWindow, form_class):  #class for control GUI
	sig_get_uid = pyqtSignal(str)
	sig_get_numbers = pyqtSignal(list)

	def __init__(self):
		super().__init__()
		self.setupUi(self)

	@pyqtSlot()
	def login(self):  #get the user id and disable the login button
		self.button_1.setEnabled(False)
		self.textEdit.setEnabled(False)
		self.sig_get_uid.emit(self.textEdit.toPlainText())

	@pyqtSlot(list)
	def display_bingo(self, bingo_mat):  #display the bingo matrix (removed numbers are colored with black)
		label_list = [self.label_1, self.label_2, self.label_3, self.label_4, self.label_5, self.label_6, self.label_7, self.label_8, self.label_9, self.label_10, self.label_11, self.label_12, self.label_13, self.label_14, self.label_15, self.label_16, self.label_17, self.label_18, self.label_19, self.label_20, self.label_21, self.label_22, self.label_23, self.label_24, self.label_25]
		for i, row in enumerate(bingo_mat):
			for j, v in enumerate(row):
				if v == 0:
					label_list[i*5+j].setText('')
					label_list[i*5+j].setStyleSheet('background-color:black;')
				else:
					label_list[i*5+j].setText(str(v))

	@pyqtSlot(list)
	def display_player_list(self, player_list):  #display the playing order
		label_list = [self.label_27, self.label_28, self.label_29, self.label_30, self.label_31]
		for i, player in enumerate(player_list):
			label_list[i].setText(player)

	@pyqtSlot(str)
	def open_input(self, role):  #enable the input button
		self.button_2.setEnabled(True)
		self.textEdit_2.setEnabled(True)
		if role == 'main':
			self.textEdit_3.setEnabled(True)  #open another input for main culprit sending the number to copartner

	@pyqtSlot()
	def get_input(self):  #get the numbers and disable the input button
		tmp = self.textEdit_2.toPlainText()
		number = int(tmp) if tmp != '' else 0
		tmp = self.textEdit_3.toPlainText()
		number2 = int(tmp) if tmp != '' else 0
		self.sig_get_numbers.emit([number, number2])
		self.textEdit_2.clear()
		self.textEdit_3.clear()
		self.button_2.setEnabled(False)
		self.textEdit_2.setEnabled(False)
		self.textEdit_3.setEnabled(False)

	@pyqtSlot(str)
	def print_msg(self, msg):  #show the game message
		self.label_33.setText(msg)

	@pyqtSlot(str)
	def title(self, role):  #change the window title
		if role == 'main':
			self.setWindowTitle('BINGO - main culprit')  #for main culprit
		else:
			self.setWindowTitle('BINGO - copartner')  #for copartner

	@pyqtSlot(int)
	def color_player(self, curr):  #color the current player with blue
		label_list = [self.label_27, self.label_28, self.label_29, self.label_30, self.label_31]
		label_list[(curr+4)%5].setStyleSheet('background-color:white;')
		label_list[curr].setStyleSheet('background-color:#6EE3F7;')
	
	@pyqtSlot(list)
	def color_winner(self, winner_list):  #color the winner with green and the others with grey
		label_list = [self.label_27, self.label_28, self.label_29, self.label_30, self.label_31]
		for i in label_list:
			if i.text() in winner_list:
				i.setStyleSheet('background-color:#86E57F;')
			else:
				i.setStyleSheet('background-color:#4C4C4C;')

class Worker(QObject):  #class for client
	sig_login = pyqtSignal()
	sig_display_bingo = pyqtSignal(list)
	sig_display_player_list = pyqtSignal(list)
	sig_open_input = pyqtSignal(str)
	sig_print_msg = pyqtSignal(str)
	sig_end = pyqtSignal()
	sig_got_uid = pyqtSignal()
	sig_play_game = pyqtSignal()
	sig_title = pyqtSignal(str)
	sig_color_player = pyqtSignal(int)
	sig_color_winner = pyqtSignal(list)

	def __init__(self, parent=None):
		super(self.__class__, self).__init__(parent)

	@pyqtSlot(str)
	def get_uid(self, uid):  #remember the user id
		self.uid = uid
		self.sig_got_uid.emit()

	@pyqtSlot(list)
	def get_numbers(self, numbers):  #get the numbers from input and send them to server
		if self.role == 'main':
			self.clientSock.send(pickle.dumps((numbers[0], numbers[1])))
		else:
			self.clientSock.send(pickle.dumps(numbers[0]))
		self.sig_play_game.emit()

	@pyqtSlot()
	def start(self):  #when the login button clicked, start
		self.sig_login.emit()

	@pyqtSlot()
	def got_uid(self):  #after get the user id, connect with server
		self.clientSock = socket(AF_INET, SOCK_STREAM)
		self.clientSock.connect(('147.46.240.95', 20653))  #server IP and Port number
		self.clientSock.send(self.uid.encode('utf-8'))  #send user id
		self.sig_print_msg.emit('Connected')
		self.role = self.clientSock.recv(BUFF).decode('utf-8')  #get the role(main culprit or copartner)
		self.clientSock.send('start'.encode('utf-8'))
		self.sig_title.emit(self.role)  #window title change
		if self.role == 'main':
			self.sig_print_msg.emit('Game start\nYou are main culprit')
		else:
			self.sig_print_msg.emit('Game start\nYou are copartner')
		time.sleep(3)  #show message for 3 seconds
		bingo_mat = pickle.loads(self.clientSock.recv(BUFF))  #get the bingo matrix from server
		self.clientSock.send('get bingo'.encode('utf-8'))
		self.player_list = pickle.loads(self.clientSock.recv(BUFF))  #get the playing order(player list) from server
		self.clientSock.send('get player_list'.encode('utf-8'))
		self.sig_display_player_list.emit(self.player_list)
		self.sig_display_bingo.emit(bingo_mat)
		self.curr = 0  #current player position
		self.sig_play_game.emit()  #play the game

	@pyqtSlot()
	def play_game(self):  #playing game
		msg = self.clientSock.recv(BUFF).decode('utf-8')  #get the message from server
		self.sig_color_player.emit(self.curr)  #color the current player
		if msg[0] == 'Y':  #this player's turn
			if self.role == 'main':
				self.sig_print_msg.emit('Your turn')
			elif int(msg[1:]) != 0:
				self.sig_print_msg.emit('Your turn\nCulprit wants : '+msg[1:])  #show the number which main culprit wants to copartner
			else:
				self.sig_print_msg.emit('Your turn')
			self.sig_open_input.emit(self.role)  #enable the input button
		elif msg[0] == 'N':  #other player's turn
			self.sig_print_msg.emit(self.player_list[self.curr]+'\'s turn')  #show current player
			self.clientSock.send('N'.encode('utf-8'))
			self.sig_play_game.emit()  #next turn
		elif msg[0] == 'S':  #get the selected number from server
			self.sig_print_msg.emit(self.player_list[self.curr]+' select : '+msg[1:])  #show selected number
			time.sleep(1)  #wait 1 second
			self.clientSock.send('S'.encode('utf-8'))
			bingo_mat = pickle.loads(self.clientSock.recv(BUFF))  #get the updated bingo matrix from server
			self.clientSock.send('S'.encode('utf-8'))
			self.sig_display_bingo.emit(bingo_mat)  #display the bingo
			self.curr = (self.curr+1)%5  #next player's position
			self.sig_play_game.emit()  #next turn
		else:  #the game ends
			self.clientSock.send('W'.encode('utf-8'))
			winner_list = pickle.loads(self.clientSock.recv(BUFF))  #get the winner list from server
			self.sig_color_winner.emit(winner_list)  #color the winner
			self.sig_print_msg.emit('Winner')
			self.sig_end.emit()

class Main_class(QObject):  #Thread for GUI and client
	def __init__(self, parent=None):
		super(self.__class__, self).__init__(parent)

		self.gui = WindowClass()
		self.worker = Worker()
		self.worker_thread = QThread()
		self.worker.moveToThread(self.worker_thread)
		self.worker_thread.start()
		self._connectSignals()
		self.gui.show()

	def _connectSignals(self):  #connect slot - signal
		self.gui.button_1.clicked.connect(self.worker.start)
		self.gui.button_2.clicked.connect(self.gui.get_input)
		self.worker.sig_login.connect(self.gui.login)
		self.worker.sig_print_msg.connect(self.gui.print_msg)
		self.worker.sig_display_player_list.connect(self.gui.display_player_list)
		self.worker.sig_display_bingo.connect(self.gui.display_bingo)
		self.worker.sig_open_input.connect(self.gui.open_input)
		self.worker.sig_end.connect(self.end)
		self.worker.sig_got_uid.connect(self.worker.got_uid)
		self.worker.sig_play_game.connect(self.worker.play_game)
		self.worker.sig_title.connect(self.gui.title)
		self.worker.sig_color_player.connect(self.gui.color_player)
		self.worker.sig_color_winner.connect(self.gui.color_winner)
		self.gui.sig_get_uid.connect(self.worker.get_uid)
		self.gui.sig_get_numbers.connect(self.worker.get_numbers)

	def end(self):  #QThread end
		if self.worker_thread.isRunning():
			self.worker_thread.terminate()

if __name__ == '__main__':
	app = QApplication(sys.argv)
	run = Main_class(app)
	app.exec_()
