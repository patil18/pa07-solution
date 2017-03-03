#include <stdio.h>
#include <stdlib.h>
#include "path.h"

#ifndef READPATH_OFF
char * readPath(char * pathFilename) {
	//Open input file
	FILE * inPath = fopen(pathFilename, "r");
	if (inPath == NULL) {
		fprintf(stderr, "Error opening path file for reading\n");
		return NULL;
	}
	
	//find out path length
	int length = 0;
	while (!feof(inPath)) {
		fgetc(inPath);
		length++;
	}
	
	//allocate path array
	char * path = malloc(length * sizeof(char));
	
	//return to beginning of file
	if (fseek(inPath, 0L, SEEK_SET) == -1) {
		fprintf(stderr, "Problem seeking to beginning of file\n");
		return NULL;
	}
	
	//read in array
	fscanf(inPath, "%s\n", path);
	
	//close file
	if (fclose(inPath)) {
		fprintf(stderr, "Problem closing path file\n");
		return NULL;
	}
	
	return path;
}
#endif //#ifndef READPATH_OFF

#ifndef CHECKPATH_OFF
bool atEnd(MazePos cur, Maze * m) {
	return (cur.xpos == m->end.xpos) && (cur.ypos == m->end.ypos);
}

bool inBounds(MazePos cur, Maze * m) {
	return ((cur.xpos >= 0) && cur.xpos < m->width) &&
		((cur.ypos >= 0) && cur.ypos < m->height);
}

bool hitWall(MazePos cur, Maze * m) {
	return m->maze[cur.ypos][cur.xpos].type == WALL;
}

bool isVisited(MazePos cur, Maze * m) {
	return m->maze[cur.ypos][cur.xpos].visited;
}

bool squareOK(MazePos cur, Maze * m) {
	return inBounds(cur, m) && !hitWall(cur, m) && !isVisited(cur, m);
}

bool checkPath(Maze * m, char * path) {
	MazePos cur = {.xpos = m->start.xpos, .ypos = m->start.ypos};
	int pathPos = 0;
	
	while (path[pathPos] != '\0') {
		
		printf("At pos %d. Maze pos: (%d, %d), Square type: %c, Next step: %c\n",
			pathPos, cur.xpos, cur.ypos, m->maze[cur.ypos][cur.xpos].type, path[pathPos]);		
		
		//Take a step:
		switch(path[pathPos]) {
			case NORTH: cur.ypos--; break;
			case SOUTH: cur.ypos++; break;
			case EAST: cur.xpos++; break;
			case WEST: cur.xpos--; break;
			default: fprintf(stderr, "Malformed path string\n"); exit(1);
		}
		
		//Bounds check is needed otherwise we will try to read
		//out of bounds while doing the printf statement
		if (!inBounds(cur, m)) return false;
		
		printf("Moved to square: (%d, %d), Square type: %c\n",
			cur.xpos, cur.ypos, m->maze[cur.ypos][cur.xpos].type);		
		
		//Make sure that the new square we're at is OK
		if (!squareOK(cur, m)) return false;
		
		//Set maze square to visited
		m->maze[cur.ypos][cur.xpos].visited = true;
		
		//Check if we're at the end
		if (atEnd(cur, m)) return true;
		
		//Move to the next position in the path
		pathPos++;
	}
	
	//If we made it to the end of the path without exiting the maze,
	//return false
	return false;
}
#endif //#ifndef CHECKPATH_OFF
