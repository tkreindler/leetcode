#!/usr/bin/env pwsh

$buildDir = Join-Path $PSScriptRoot "build"

# create if doesn't exist
$null = [System.IO.Directory]::CreateDirectory($buildDir)

# clean contents
Remove-Item -Path "$buildDir\*" -Recurse -Force

Push-Location $buildDir

cmake.exe ..

Pop-Location

$solutionPath = Get-ChildItem "$buildDir\*.sln" | Select-Object -First 1 -ExpandProperty FullName

devenv.exe $solutionPath
