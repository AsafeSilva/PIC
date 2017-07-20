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

bool SerialRead(char*);

#endif	/* SERIAL_H */

