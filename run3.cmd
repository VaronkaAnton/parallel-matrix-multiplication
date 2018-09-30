set n=1000
set r=125
@echo %n% 3 >> output.txt
for %%t in (1, 2, 4) do (
	"Debug/lab1.exe" -n %n% -r %r% -t %%t -o output.txt
	@echo %%t >> output.txt
)