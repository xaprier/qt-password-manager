# Get the directory where the PowerShell script is located
$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition

# Define the path to the original Inno Setup script
$innoSetupScript = Join-Path -Path $scriptDir -ChildPath "installer_script.iss"

# Define the path for the updated Inno Setup script
$updatedInnoSetupScript = Join-Path -Path $scriptDir -ChildPath "installer_script_updated.iss"

# Read the original Inno Setup script
$innoSetupContent = Get-Content -Path $innoSetupScript

# Update the paths in the Inno Setup script
$updatedContent = $innoSetupContent `
    -replace '\$CHANGEMEWITHPATH\\LICENSE', "$scriptDir\LICENSE" `
    -replace '\$CHANGEMEWITHPATH\\build\\install\\Output', "$scriptDir\build\install\Output" `
    -replace '\$CHANGEMEWITHPATH\\build\\install\\\{#MyAppExeName\}', "$scriptDir\build\install\{#MyAppExeName}" `
    -replace '\$CHANGEMEWITHPATH\\build\\install\\\*', "$scriptDir\build\install\*"

# Write the updated content to a new Inno Setup script file
Set-Content -Path $updatedInnoSetupScript -Value $updatedContent

# Output confirmation
Write-Host "Paths in the Inno Setup script have been updated and saved to 'installer_script_updated.iss'."
