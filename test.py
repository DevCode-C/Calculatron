import serial
from serial.serialwin32 import Serial
import serial.tools.list_ports
import random
import sys


def sum(iteraciones, port):
    print("Test SUM ...",end="\t", flush=True)
    for _ in range(iteraciones):   

        varA = random.randint(-1000,1000)
        varB = random.randint(-1000,1000)
        Resultado = varA + varB
        comando =  "SUM " + str(varA) + " " + str(varB) + "\r"
        port.write(comando.encode('utf8'))
        byteNumber = port.in_waiting
        stringInput = port.readline().decode('utf8')
        if (stringInput == str(" ERROR\r\n")) or (stringInput == str("ERROR\r\n")):
            print("Test FAIL")
            sys.exit()
        stringInput = stringInput.split('=')
        # print (stringInput[1])clear
        resultInput = int(stringInput[1])
        # print(f"Entrada: {stringInput[0]}, Resultado: {stringInput[1]}\t ResultadoInput: {resultInput}, Resultado P: {Resultado}")
        if resultInput != Resultado:
            print("Test FAIL")
            sys.exit()

    print("OK")

def sub(iteraciones,port):
    print("Test SUB ...",end="\t", flush=True)
    for _ in range(iteraciones):   

        varA = random.randint(-1000,1000)
        varB = random.randint(-1000,1000)
        Resultado = varA - varB
        comando =  "SUB " + str(varA) + " " + str(varB) + "\r"
        port.write(comando.encode('utf8'))
        byteNumber = port.in_waiting
        stringInput = port.readline().decode('utf8')
        if (stringInput == str(" ERROR\r\n")) or (stringInput == str("ERROR\r\n")):
            print("Test FAIL")
            sys.exit()
        stringInput = stringInput.split('=')
        # print (stringInput[1])clear
        resultInput = int(stringInput[1])
        # print(f"Entrada: {stringInput[0]}, Resultado: {stringInput[1]}\t ResultadoInput: {resultInput}, Resultado P: {Resultado}")
        if resultInput != Resultado:
            print("Test FAIL")
            sys.exit()

    print("OK")

def mul(iteraciones,port):
    print("Test MUL ...",end="\t", flush=True)
    for _ in range(iteraciones):   

        varA = random.randint(-1000,1000)
        varB = random.randint(-1000,1000)
        Resultado = varA * varB
        comando =  "MUL " + str(varA) + " " + str(varB) + "\r"
        port.write(comando.encode('utf8'))
        byteNumber = port.in_waiting
        stringInput = port.readline().decode('utf8')
        if (stringInput == str(" ERROR\r\n")) or (stringInput == str("ERROR\r\n")):
            print("Test FAIL")
            sys.exit()
        stringInput = stringInput.split('=')
        # print (stringInput[1])clear
        resultInput = int(stringInput[1])
        # print(f"Entrada: {stringInput[0]}, Resultado: {stringInput[1]}\t ResultadoInput: {resultInput}, Resultado P: {Resultado}")
        if resultInput != Resultado:
            print("Test FAIL")
            sys.exit()

    print("OK")

def div(iteraciones,port):
    print("Test DIV ...",end="\t", flush=True)
    for _ in range(iteraciones):   

        varA = random.randint(-1000,1000)
        varB = random.randint(-1000,1000)
        if varB == 0:
            Resultado = 0
        else:
            Resultado = int(varA / varB)
        comando =  "DIV " + str(varA) + " " + str(varB) + "\r"
        port.write(comando.encode('utf8'))
        byteNumber = port.in_waiting
        stringInput = port.readline().decode('utf8')
        # print(comando)
        # print(Resultado, end= '\t',flush= True)
        # print(stringInput)

        if varB == 0:
            if (stringInput == str(" ERROR\r\n")) or (stringInput == str("ERROR\r\n")):
                pass
            else:
                print("Test FAIL")
                sys.exit()

        else:
            if (stringInput == str(" ERROR\r\n")) or (stringInput == str("ERROR\r\n")):
                print("Test FAIL")
                sys.exit()
            stringInput = stringInput.split('=')
            resultInput = int(stringInput[1])
            # print(f"Entrada: {stringInput[0]}, Resultado: {stringInput[1]}\t ResultadoInput: {resultInput}, Resultado P: {Resultado}")
            if resultInput != Resultado:
                print("Test FAIL")
                sys.exit()
    print("OK")    

def erTest1(iteraciones,port):
    print("Test Erros ...",end="\t", flush=True)
    for _ in range(iteraciones):
        varA = random.randint(-1000,1000)
        varB = random.randint(-1000,1000)
        sel  = random.randint(0,23)
        letters = "abcdeslkadasjlkjkzxcbmawAKJHWUUDASIJDSAOAWMBHASDKOOPKAS"

        inst = [str("SUMl "), str("SaUB "), str("MUdL "), str("DaIV "),str("SUM3 "), str("SUbB "), str("MULt "), str("qDIV ")]
        inst += [str("UMl "), str("SaUx "), str("MUzL "), str("DdIV "),str("MUL "), str("mUbB "), str("M5Lt "), str("qDIV5 ")]
        inst += [str("DIV "), str("SUM "), str("MUzL "), str("Ddc "),str("zUM3 "), str("5UbB "), str("M32t "), str("SUB ")]
        
        comando =  inst[sel] + str(varA) +letters[random.randint(0,54)] + " " + str(varB) + letters[random.randint(0,54)] + "\r"
        port.write(comando.encode('utf8'))
        byteNumber = port.in_waiting
        stringInput = port.readline().decode('utf8')
        if (stringInput == str(" ERROR\r\n")) or (stringInput == str("ERROR\r\n")):
            pass
        else:
            print("Test FAIL")
            sys.exit()

    print("OK")

def erTest2(iteraciones,port):
    print("Test Erros ...",end="\t", flush=True)
    for _ in range(iteraciones):
        varA = random.randint(-1000,1000)
        varB = random.randint(-1000,1000)
        sel  = random.randint(0,3)
        letters = "abcdeslkadasjlkjkzxcbmawAKJHWUUDASIJDSAOAWMBHASDKOOPKAS"
        comandoCorrect = [str("SUM "), str("SUB "), str("MUL "), str("DIV ")]
        
        comando =  comandoCorrect[sel] + letters[random.randint(0,54)] + str(varA) + " " + str(varB) + letters[random.randint(0,54)] + "\r"
        port.write(comando.encode('utf8'))
        byteNumber = port.in_waiting
        stringInput = port.readline().decode('utf8')
        if (stringInput == str(" ERROR\r\n")) or (stringInput == str("ERROR\r\n")):
            pass
        else:
            print("Test FAIL")
            sys.exit()

    print("OK")

def erTest3(iteraciones,port):
    print("Test Erros ...",end="\t", flush=True)
    for _ in range(iteraciones):
        varA = random.randint(-1000,1000)
        varB = random.randint(-1000,1000)
        sel  = random.randint(0,3)
        letters = "abcdeslkadasjlkjkzxcbmawAKJHWUUDASIJDSAOAWMBHASDKOOPKAS"
        comandoCorrect = [str("SUM "), str("SUB "), str("MUL "), str("DIV ")]
        
        comando =  comandoCorrect[sel] + str(varA) + " " + str(varB) + letters[random.randint(0,54)] + "\r"
        port.write(comando.encode('utf8'))
        byteNumber = port.in_waiting
        stringInput = port.readline().decode('utf8')
        if (stringInput == str(" ERROR\r\n")) or (stringInput == str("ERROR\r\n")):
            pass
        else:
            print("Test FAIL")
            sys.exit()

    print("OK")

def main():
    iteraciones = int(sys.argv[1])
    # print(iteraciones)
    portList = list(serial.tools.list_ports.comports())
    for i in range(0,10):
        try:
            print(portList[i])
        except:
            break
    # port = Serial()
    port = serial.Serial()
    portSeleted = input("Selecciona el puerto:\t")
    # port.port = "COM9"
    port.port = str(portSeleted)
    # print(portSeleted)

    portBaud = input("Selecciona el BaudRate:\t")
    # port.baudrate = 115200
    port.baudrate = int(portBaud)
    # print(int(portBaud))
    port.open()

    sum(iteraciones,port)
    sub(iteraciones,port)
    mul(iteraciones,port)
    div(iteraciones,port)
    erTest1(iteraciones,port)
    erTest2(iteraciones,port)
    erTest3(iteraciones,port)
    
    
    
    port.close()

if __name__ == "__main__":
    
    main()
