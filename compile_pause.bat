set PATH=%cd%\lsic86ws\bin;%PATH%
set TZ=JST-9
set MAKEDEFAULT=%cd%\lsic86ws\bin\makedef
lld -Fc -T F0000 -TDATA F0000 -o MAINMAP.obj armoredunit.map
kmmake
pause