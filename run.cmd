@echo off
for %%n in (750, 1000, 1500, 2000) do (
	@echo %%n 6 >> output.txt
	for %%r in (1, 5, 10, 25, 50, 125) do (
		"Debug/lab1.exe" -n %%n -r %%r -t 2 -o output.txt
		@echo %%r >> output.txt
	)
)