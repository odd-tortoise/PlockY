$benchmarksDir = ".\build\benchmarks"
$executables = @("test0.exe", "test1.exe")  # Custom list of executables

# Check if the benchmarks directory exists
if (-Not (Test-Path $benchmarksDir)) {
    Write-Host "Benchmarks directory does not exist: $benchmarksDir"
    exit
}

# Change to the benchmarks directory
Set-Location $benchmarksDir

foreach ($executableName in $executables) {
    $executablePath = $executableName

    # Check if the executable file exists
    if (-Not (Test-Path $executablePath)) {
        Write-Host "Executable does not exist: $executablePath"
        continue
    }

    # Create a directory for the executable if it doesn't exist
    $outputDir = $executableName.TrimEnd('.exe')
    if (-Not (Test-Path $outputDir)) {
        New-Item -ItemType Directory -Path $outputDir | Out-Null
    }

    # Execute the executable and redirect output to a file within its directory
    & $executablePath > "$outputDir\output.txt" 2>&1

    Write-Host "Executed benchmark: $executableName"
}

Write-Host "All specified benchmarks executed."
cd ..
cd ..