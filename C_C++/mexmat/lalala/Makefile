a: main.o tree.o tree_node.o student.o
	g++ main.o tree.o tree_node.o student.o
student.o: student.cpp student.h
	g++ -c student.cpp -g
tree.o: tree.cpp tree.h tree_node.h student.h
	g++ -c tree.cpp -g
tree_node.o: tree_node.cpp tree_node.h
	g++ -c tree_node.cpp -g
main.o: main.cpp tree.h tree_node.h student.h
	g++ -c main.cpp
