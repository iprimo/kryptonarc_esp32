# Find the process using COM8 and kill it
$port = 'COM8'
$processes = Get-WmiObject Win32_SerialPort | Where-Object { $_.DeviceID -eq $port } | ForEach-Object {
    Get-Process | Where-Object { $_.Id -eq $_.ProcessId }
}
if ($processes) {
    $processes | ForEach-Object { Stop-Process -Id $_.Id -Force }
    Write-Host "Killed process using $port"
} else {
    Write-Host "No process found using $port"
}