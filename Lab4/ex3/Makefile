all:
	cd ~/Documents/Lab4/ex3/toCompile && g++ -c stuff.cpp util.cpp 
	cd ~/Documents/Lab4/ex3/lib && ar rvs libTest.a ../toCompile/stuff.o ../toCompile/util.o
	cd ~/Documents/Lab4/ex3 && g++ -c -o intermediaire.o main.cpp -ItoCompile -Ilib
	cd ~/Documents/Lab4/ex3 && g++ intermediaire.o -o hello-world-3 -Llib -lTest

clean:
	cd ~/Documents/Lab4/ex3 && find . -name '*.o' -type f -delete
	cd ~/Documents/Lab4/ex3 && find . -name '*.a' -type f -delete
	cd ~/Documents/Lab4/ex3 && rm hello-world-3
