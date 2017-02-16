# LenovoKeyFix

Install
Download all the files and extract them to directory.
Run install-interception.exe /install
Reboot
Start inter.exe  it will show console and switch end\insert buttons function for all keyboards.
Press end and insert buttons on the keyboard you want the only to be switched. You will see something like this ACPI\VEN_MSFT&DEV_0001 82
This is a device ID of the keyboard - copy it and run 
inter.exe "device id" 
mind quotes. for example inter.exe "ACPI\VEN_MSFT&DEV_0001"
this will start fixer in hidden mode and fix end button only for the specified keyboard.
