/* 
 * File:   Serial.h
 * Author: Asafe
 *
 * Created on 24 de Junho de 2017, 22:00
 */

#ifndef SERIAL_H
#define	SERIAL_H

#include <stdlib.h>
#include <stdbool.h>

void SerialBegin();

void print_string(char word[]);
void println_string(char word[]);

void print_char(char word);
void println_char(char word);

void print_int(int word);
void println_int(int word);

void print_long(long word);
void println_long(long word);

bool SerialRead(char*);

void serialEvent();

void clearString(char*, int size);

#endif	/* SERIAL_H */

