#ifndef __SNAKE_H
#define __SNAKE_H

int movement(struct SnakeBodySegment *segment, int **GameGrid);

int cleanUpDeadSnek(struct Snake *snek, int **GameGrid);

void freeGameGridMemory(int **GameGrid);

#endif
