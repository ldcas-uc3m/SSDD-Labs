# ---
# Cliente de envio de mensajes básico con sockets TCP
# ---

import socket
import sys
from lines import readString



def main():

    # arguments
    if len(sys.argv) != 3:
        print("Usage: python3", sys.argv[0], "<serverAddress> <serverPort>")
        return
    
    # create socket
    sd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # get server address
    server_addr = (sys.argv[1], int(sys.argv[2]))
    print("Connecting to", server_addr[0], "port", server_addr[1])

    # establish connection
    try:
        sd.connect(server_addr)
    except ConnectionRefusedError:
        print("Error en la conexión")
        return

    # main loop
    while True:
        try:
            msg = input()
            sd.sendall(msg.encode() + b'\0')

            if msg == "EXIT":
                break

            res = readString(sd)
            print("Server:" + res)
        except:
            break
    
    sd.close()



if __name__ == "__main__":
    main()
    
    