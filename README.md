# CommandGen
Our little CLI tool for generating commands to Celeritas.

## Building
### Linux
First install build-essentials using your favourite package manager.

Then give executing permission to the build script by:
```bash
chmod +x build.sh
```

Finally execute that script. It will generate a CommandGen.exe file,
but don't worry deep inside its a Linux executable.

### Windows (VSCode)
Download [MSYS2](https://www.msys2.org/) by following their tutorial 
(you'll also install mingw on the go).

Then inside of VSCode choose `MSYS UCRT` as your terminal.
Give the `build.sh` script executing permission:
```bash
chmod +x build.sh
```
And finally execute the script.

## Contributing 
As a general guideline everything written in [Celeritas' CONTRIBUTING.md](https://github.com/CeleritasBoard/Celeritas/blob/main/CONTRIBUTING.md) is applied to this repo as well.

## Usage
After starting the program you can choose between generation, timesync or read interpretation.

At generation you can choose which command you're going to execute. Then it will ask
for command params and generate the command.

At timesync you can ask for an OBC emulator timesync command.

At read mode you can analyze the packets that the board generated.
