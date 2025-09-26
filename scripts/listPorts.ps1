# List likely serial port users
Get-Process | Where-Object { $_.ProcessName -match 'python|platformio|putty|screen|arduino|code' }

# To kill a process (replace <PID> with the actual process ID)
# Stop-Process -Id <PID> -Force