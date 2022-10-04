from os import getpid
import sys
import signal
from time import sleep


retries = 0

def interrupt(sigNum, stackframe):
    global retries
    print("Ctrl+C")
    retries+=1
    if(retries >= 3):
        sys.exit(0)

def bling(sigNum, stackframe):
    print("Bling!")
    signal.alarm(3)

print("PID = " + str(getpid()))
signal.signal(signal.SIGALRM, bling)
signal.signal(signal.SIGINT, interrupt)
signal.alarm(3)
while(True):
    sleep(1)