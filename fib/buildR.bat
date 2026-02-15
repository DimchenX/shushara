@dotnet build --configuration Release
@pause
@busybox64u time "./bin/Release/net10.0/fib.exe"
@pause