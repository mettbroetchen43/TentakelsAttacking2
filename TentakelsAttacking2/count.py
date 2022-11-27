#
# Purpur Tentakel
# count config
# 17.11.2022
#

import count_config as cc
import os

directories: int = 0
files: int = 0
lines: int = 0
lines_ot_comments: int = 0
characters: int = 0
characters_out_comments: int = 0


def print_directory_or_file(filename: str, layer: int) -> None:
    to_print: str = " " * layer * 4
    to_print += "-> "
    to_print += filename
    print(to_print)


def count_files(file: str, path: str, layer: int):
    _, tail = os.path.splitext(file)
    if tail not in cc.file_endings:
        return

    print_directory_or_file(file, layer)


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


def load_files(path: str, layer: int = 0) -> None:
    for filename in os.listdir(path):
        next_path: str = os.path.join(path, filename)

        if os.path.isfile(next_path):
            count_files(filename, next_path, layer + 1)
            continue

        if os.path.isdir(next_path):
            if not is_valid_file_in_directory(next_path):
                continue

            print_directory_or_file(filename, layer)
            load_files(next_path, layer + 1)
            continue


if __name__ == "__main__":
    load_files(os.getcwd())
    input()
