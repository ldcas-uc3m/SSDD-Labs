# ---
# Servidor de echo básico con sockets TCP
# ---

import socket
import sys
from lines import *


# TODO: Concurrent


def main():
    # arguments
    if len(sys.argv) != 2:
        print("Usage: python3", sys.argv[0], "<serverPort>")
        return
    
    # create socket
    sd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # connect
    server_addr = ("localhost", int(sys.argv[1]))
    sd.bind(server_addr)
    sd.listen(True)


    # main loop
    while True:
        # accept connection
        newsd, client_addr = sd.accept()
        print("Client connected")

        while True:
            msg = newsd.recv(MAX_LINE)
            if msg ==  b"EXIT\0": 
                print("Client disconnected")
                break
            
            print("Client:", msg.decode())

            # echo
            newsd.sendall(msg)
        
        newsd.close()


if __name__ == "__main__":
    main()