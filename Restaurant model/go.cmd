if .%USERDOMAIN% == .DESKTOP-AKLG6PJ goto :savasPC
Rem MIF kompiuteris
path C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%path"
mingw32-make.exe
goto :toliau

:savasPC
make

:toliau
main.exe f