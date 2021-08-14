""" Generates simple function names for coal functions."""
import sys
import os
import re
from pathlib import Path

rootdir = Path(sys.path[0]).parent
builddir = rootdir / "build"
outdir   = builddir / "gen"
incdir   = rootdir / "src/include/coal"

if not os.path.exists(builddir):
    os.mkdir(builddir)

if not os.path.exists(outdir):
    os.mkdir(outdir)

headers = os.listdir(incdir)
print(headers)

regex1 = re.compile(r"[\w\d]+ +coal_([A-Z][\w\d]*)\((.*?)\)", re.DOTALL)
regex2 = re.compile(r" *void(?! *\*)")

for h in headers:
    with open(outdir / h, 'w') as outf:
        path = Path(incdir / h)
        with open(path) as f:
            filestr = f.read()
        matches = regex1.findall(filestr)
        for m in matches:
            name = m[0]
            lname = name.lower()[0] + name[1:]
            parms = m[1]
            parmCount = parms.count(',') + 1
            if parmCount == 1 and regex2.match(parms):
                parmCount = 0
            plist = ["p" + str(i) for i in range(parmCount)]
            pliststr = ", ".join(plist)
            outstr = f"#define {lname}({pliststr}) coal_{name}({pliststr})\n"
            outf.write(outstr)

#/START FUNCDECLS.*\n((.*\n)*)\/\/ END/gm
