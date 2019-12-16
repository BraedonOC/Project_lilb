g++ -c main.cpp management/src/StageManager.cpp overRealms/src/WakingWorld.cpp;

g++ main.o StageManager.o WakingWorld.o -o lilb -lsfml-graphics -lsfml-window -lsfml-system;

rm main.o;
rm StageManager.o;
rm WakingWorld.o;

./lilb

rm lilb;