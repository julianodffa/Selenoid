# Adjust COM port and baud rate as necessary
$portName = "COM8" # Change this to your actual COM port
$baudRate = 115200

# Create a SerialPort object
$serialPort = New-Object System.IO.Ports.SerialPort $portName, $baudRate

try {
    # Open the serial port
    $serialPort.Open()

    while ($true) {
        if ($serialPort.BytesToRead -gt 0) { # Check if there are bytes to read
            $inputLine = $serialPort.ReadLine().Trim() # Read a line and trim whitespace
            if ($inputLine -eq "SHUTDOWN") {
                # Show shutdown warning
                Start-Sleep -Seconds 3
                # Implement your shutdown logic here
                Stop-Computer -Force
            } else {
                Write-Host "Power is good." # Informative message when input is not "SHUTDOWN"
            }
        }
        Start-Sleep -Seconds 1 # Optional: sleep for a short duration to reduce CPU usage
    }
}
catch {
    Write-Host "Error: $_"
}
finally {
    if ($serialPort.IsOpen) {
        $serialPort.Close() # Ensure the port is closed when done
    }
}
