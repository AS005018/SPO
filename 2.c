from gpio import *
from time import *

def main():
	pinMode(0, IN)
	pinMode(1,OUT)
	pinMode(2,OUT)
	
	while True:
		a = analogRead(0)
		if a<615:
			#digitalWrite(1, LOW)
			digitalWrite(2, HIGH)
			delay(2000)
		if a>639:
			#digitalWrite(2, LOW)
			digitalWrite(1, HIGH)
			delay(2000)
		if a>620:
			digitalWrite(2, LOW)
		if  a<630:
			digitalWrite(1, LOW)

if __name__ == "__main__":
	main()