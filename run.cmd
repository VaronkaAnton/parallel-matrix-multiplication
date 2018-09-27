@echo off
for %%n in (100, 200, 500, 1000) do (
	@echo %%n >> output.txt
	for %%r in (1, 5, 10, 20, 50) do (
		@echo %%r >> output.txt
		"Debug/lab1.exe" -n %%n -r %%r -t 4 -o output.txt
	)
)