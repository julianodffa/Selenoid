# Definisikan COM port dan baud rate
$portName = "COM8" # Ubah Ke COM port Sebenarnya
$baudRate = 115200 # Ubah Ke Baud Rate Sebenarnya

# Buat Objek Serial Port
$serialPort = New-Object System.IO.Ports.SerialPort $portName, $baudRate

try {
    $serialPort.Open()

    while ($true) {
        if ($serialPort.BytesToRead -gt 0) { # Check if there are bytes to read
            $inputLine = $serialPort.ReadLine().Trim() # Read a line and trim whitespace
            if ($inputLine -eq "SHUTDOWN") {
                # Perintah Shutdown
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
