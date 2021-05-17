import os

if __name__ == '__main__':
    files = os.listdir(os.path.join(os.getcwd(), "db"))

    db  = ""
    db += "version: 2\n"
    db += "firmware: 3.60\n"
    db += "modules:\n"

    for i in range (0, len(files)):

        cache_char = ""

        f = open(os.path.join(os.getcwd(), "db", files[i]), 'r')
        for line in f:
            if line[:2] == "  ":
                db += line
                cache_char = line[-1]

        if cache_char != "\n":
            db += "\n"
        f.close()

    f = open(os.path.join(os.getcwd(), "db.yml"), 'w')
    f.write(db)
    f.close()