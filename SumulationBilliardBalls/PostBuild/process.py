import os
import shutil
import argparse

def getArgumentsCMD ():
    parser = argparse.ArgumentParser(description='Post build event')
    parser.add_argument ('-a', required=True, help='architecture target platform')
    parser.add_argument ('-b', required=True, help='binaries directory')
    parser.add_argument ('-o', required=True, help='output directory')
    return parser.parse_args()

def main():
    args = getArgumentsCMD()
    print('arguments received', args)
    
    print('Copy binaries... ', end='')
    files = os.listdir(args.b)
    for file_name in files:
        full_file_name = os.path.join(args.b, file_name)
        if os.path.isfile(full_file_name):
            shutil.copy(full_file_name, args.o)
    print('SUCCESS!')
    
if __name__ == '__main__':
    main()
