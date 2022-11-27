#
# Purpur Tentakel
# count config
# 17.11.2022
#

import count_config as cc
import os

directories: int = 0
files: int = 0

global_lines: int = 0
code_lines: int = 0
comment_lines: int = 0

global_characters: int = 0
code_characters: int = 0
comment_characters: int = 0

block_comment: bool = False


def print_directory_or_file(filename: str, layer: int) -> None:
    to_print: str = " " * layer * 1
    to_print += "-> "
    to_print += filename
    print(to_print)


def print_result() -> None:
    print("counted directory: " + os.getcwd())
    print("-----")
    print("directories:        " + str(directories))
    print("-----")
    print("files:              " + str(files))
    print("-----")
    print("global_lines:       " + str(global_lines))
    print("code_lines:         " + str(code_lines))
    print("comment_lines:      " + str(comment_lines))
    print("-----")
    print("global_characters:  " + str(global_characters))
    print("code_characters:    " + str(code_characters))
    print("comment_characters: " + str(comment_characters))


def is_valid_file_in_directory(path: str) -> bool:
    for filename in os.listdir(path):
        next_path: str = os.path.join(path, filename)

        if os.path.isdir(next_path):
            valid: bool = is_valid_file_in_directory(next_path)
            if valid:
                return True
            continue

        if os.path.isfile(next_path):
            _, tail = os.path.splitext(next_path)
            if tail in cc.file_endings:
                return True

    return False


def is_check_comment(line: str, dummy_list: list[str, ...], index: int = 0) -> bool:
    try:
        for i in range(len(dummy_list)):
            if line[index + i] != dummy_list[i]:
                return False
        return True
    except IndexError:
        return False


def count_characters(line: str) -> None:
    global block_comment
    global global_characters
    global code_characters
    global comment_characters

    line_comment: bool = block_comment
    for i in range(len(line)):

        if not line_comment:
            line_comment = is_check_comment(line, cc.single_line_comment, i)

        if block_comment:
            result: bool = is_check_comment(line, cc.multi_line_comment_end, i)
            if result:
                block_comment = False
        else:
            result: bool = is_check_comment(line, cc.multi_line_comment_begin, i)
            if result:
                block_comment = True

        global_characters += 1
        if line_comment or block_comment:
            comment_characters += 1
        else:
            code_characters += 1


def count_line(line: str) -> None:
    global global_lines
    global code_lines
    global comment_lines
    line = line.strip()

    if len(line) == 0:
        return

    global_lines += 1
    if block_comment:
        comment_lines += 1
    elif is_check_comment(line, cc.single_line_comment):
        comment_lines += 1
    elif is_check_comment(line, cc.multi_line_comment_begin):
        comment_lines += 1
    else:
        code_lines += 1

    count_characters(line)


def count_file(file: str, path: str, layer: int):
    global files

    _, tail = os.path.splitext(file)
    if tail not in cc.file_endings:
        return

    files += 1
    print_directory_or_file(file, layer)

    f = open(path, "r")

    for line in f:
        count_line(line)

    f.close()


def load_files_and_directories(path: str, layer: int = 0) -> None:
    global directories

    for filename in os.listdir(path):
        next_path: str = os.path.join(path, filename)

        if os.path.isfile(next_path):
            count_file(filename, next_path, layer + 1)
            continue

        if os.path.isdir(next_path):
            if not is_valid_file_in_directory(next_path):
                continue

            print_directory_or_file(filename, layer)
            directories += 1
            load_files_and_directories(next_path, layer + 1)
            continue


if __name__ == "__main__":
    load_files_and_directories(os.getcwd())
    print("\n" * 3)
    print_result()
    input()
