@echo off
if exist %1.obj goto ktcc
goto ktcc1
:ktcc
del %1.obj
:ktcc1
tcc -B -ms -G -Z -O -S -r -c %1.c
@echo off
if exist %1.obj goto link0
goto exit
:link0
if exist %1.exe goto link
goto link1
:link
del %1.exe
:link1
echo on
link ramstart+%1, %1, %1, cs.lib
@echo off
if exist %1.exe goto exe2hex
echo on
echo Link error
goto exit1
:exe2hex
pause
mexe2ABS %1
@echo off
goto exit1
:exit
echo File not found( %1.obj )
:exit1