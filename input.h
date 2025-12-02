#pragma once

void cleanInputBuffer();
void readString(char *buffer, int size, char *msg);
int readInteger(int min, int max, char *msg);
float readFloat(float min, float max, char *msg);