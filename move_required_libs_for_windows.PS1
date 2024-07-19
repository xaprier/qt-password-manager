$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition
$sourceFolder = "C:\msys64\mingw64\bin"
$destinationFolder = "C:\Program Files (x86)\xpwm\"
$fileListPath = Join-Path -Path $scriptDir -ChildPath "required_libs_for_windows.txt"

if (!(Test-Path $destinationFolder)) {
    New-Item -ItemType Directory -Force -Path $destinationFolder | Out-Null
}

$fileList = Get-Content -Path $fileListPath

foreach ($file in $fileList) {
    $sourceFile = Join-Path -Path $sourceFolder -ChildPath $file
    $destinationFile = Join-Path -Path $destinationFolder -ChildPath $file
    Copy-Item -Path $sourceFile -Destination $destinationFile -Force
}

$exePath = Join-Path -Path $destinationFolder -ChildPath "xpwm.exe"
Start-Process "windeployqt.exe" -ArgumentList "`"$exePath`" --no-compiler-runtime" -Wait

Write-Host "DLL files successfully moved and application deployed."