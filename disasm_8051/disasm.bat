cd /D "%~dp1"


perl "%~dp0\"mcs51-disasm.pl -M stc8h.h "%~nx1" > "%~n1".asm

pause
