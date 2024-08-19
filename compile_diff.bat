set PATH=%cd%\lsic86ws\bin;%cd%\dmc;%PATH%
set TZ=JST-9
set MAKEDEFAULT=%cd%\lsic86ws\bin\makedef
kmmake
code -d %1.cod match/%1.cod
pause