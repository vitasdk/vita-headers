
import pathlib
import glob
import os

if __name__ == '__main__':

    curr_path = pathlib.Path(os.getcwd())

    files = glob.glob(str(curr_path.joinpath('db', '*.yml')))

    db  = ""
    db += "version: 2\n"
    db += "firmware: 3.60\n"
    db += "modules:\n"

    file_list = []

    for i in range (0, len(files)):
        file_list.append(files[i])

    file_list.sort()

    for i in range (0, len(file_list)):

        cache_char = ""

        f = open(file_list[i], 'r')
        for line in f:
            if line[:2] == "  ":
                db += line
                cache_char = line[-1]

        if cache_char != "\n":
            db += "\n"
        f.close()

    f = open(curr_path.joinpath('db.yml'), 'w')
    f.write(db)
    f.close()