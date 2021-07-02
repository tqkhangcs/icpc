@echo off
gen >in
sol <in >out
stupid <in >ok
fc out ok
if errorlevel 1 exit
test
