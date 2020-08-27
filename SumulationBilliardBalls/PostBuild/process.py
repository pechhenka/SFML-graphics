import os
import shutil
import argparse

font_file_name = 'Arial.ttf'

def getArgumentsCMD ():
    parser = argparse.ArgumentParser(description='Post build event')
    parser.add_argument ('-a', required=True, help='architecture target platform')
    parser.add_argument ('-p', required=True, help='project directory')
    parser.add_argument ('-b', required=True, help='binaries directory')
    parser.add_argument ('-o', required=True, help='output directory')
    return parser.parse_args()

def main():
    global font_file_name
    args = getArgumentsCMD()
    print('arguments received', args)
    
    print('Copy binaries... ', end='')
    try:
        files = os.listdir(args.b)
        for file_name in files:
            full_file_name = os.path.join(args.b, file_name)
            if os.path.isfile(full_file_name):
                shutil.copy(full_file_name, args.o)
        print('SUCCESS!')
    except Exception:
        print('LOSE :(')
    print('Copy font... ', end='')
    try:
        full_file_name = os.path.join(args.p, font_file_name)
        shutil.copy(full_file_name, args.o)
        print('SUCCESS!')
    except Exception:
        print('LOSE :(')
    
if __name__ == '__main__':
    main()
