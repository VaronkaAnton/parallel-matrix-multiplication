set n=600
set r=1
@echo %n% 3 >> output.txt
for %%t in (1, 2, 4) do (
	"Debug/lab1.exe" -n %n% -r %r% -t %%t -o output.txt
	@echo %%t >> output.txt
)