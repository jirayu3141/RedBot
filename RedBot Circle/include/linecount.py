import os
import glob

files = glob.glob("*.c")
files.extend(glob.glob("*.h"))
count = len(files)
lines = 0
for path in files:
    file = open(path)
    for line in file:
        if not line.isspace():
            lines += 1
    file.close()
print(str(lines) + " lines of code in " + str(count) + " files.")
print(str(round(lines/count,5)) + " lines average" )
print()
input("Press Enter to close")
