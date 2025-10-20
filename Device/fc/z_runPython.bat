@echo off
rem 3 line, 3 column, saved as abc.png

set "PyPath=C:\ProgramInstalled\Python38"

set "PATH=%PyPath%;%PyPath%\Scripts;%PATH%"

rem python parseReg.py C:\_UserPartitions\Projects\Python\LoadRegister\FC100_header.h FC100_header
python Z_AddInclude.py

pause