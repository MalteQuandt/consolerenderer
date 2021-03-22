#pragma once

#ifndef ANSIMOV_H
#define ANSIMOV_H
// https://tldp.org/HOWTO/Bash-Prompt-HOWTO/x361.html

// Moves the terminal cursor to the position specified
// Important: The col and row need to be character or string constants!
#define MOVETERMTO(col, row) "\033[" row ";" col "f"
#define MOVETERMTOINT "\033[%d;%df"
// Moves the terminal cursor up n rows
#define MOVEUP(n) "\033["n"A"
#endif