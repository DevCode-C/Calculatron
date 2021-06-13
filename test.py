import serial
from serial.serialwin32 import Serial
import serial.tools.list_ports
import random
import sys

def main():
    iteraciones = int(sys.argv[1])
    # print(iteraciones)
    # portList = list(serial.tools.list_ports.comports())
    # for i in range(0,10):
    #     try:
    #         print(portList[i])
    #     except:
    #         break
    # port = Serial()
    port = serial.Serial()
    # portSeleted = input("Selecciona el puerto:\t")
    port.port = "COM9"
    # print(portSeleted)

    # portBaud = input("Selecciona el BaudRate:\t")
    port.baudrate = 115200
    # print(int(portBaud))
    port.open()

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

    print("Test DIV ...",end="\t", flush=True)
    for _ in range(iteraciones):   

        varA = random.randint(-1000,1000)
        varB = random.randint(0,1)
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
            # print (stringInput[1])clear
            resultInput = int(stringInput[1])
            # print(f"Entrada: {stringInput[0]}, Resultado: {stringInput[1]}\t ResultadoInput: {resultInput}, Resultado P: {Resultado}")
            if resultInput != Resultado:
                print("Test FAIL")
                sys.exit()

    print("OK")        
    port.close()

if __name__ == "__main__":
    
    main()
