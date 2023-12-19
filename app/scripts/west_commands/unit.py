'''unit.py

West extension for running app unit tests.'''

from textwrap import dedent            # just for nicer code indentation

from west.commands import WestCommand  # your extension must subclass this
from west import log                   # use this for user output

from dts2repl import dts2repl # Create repl files for renode from device tree files
from argparse import Namespace

from os import path
import subprocess

class Unit(WestCommand):

    def __init__(self):
        super().__init__(
            'unit',  # gets stored as self.name
            'runs the app unit tests',  # self.help
            # self.description:
            dedent('''
            Application Unit Test runner.

            This command runs the app unit tests and creates a coverage report.
            '''))

    def do_add_parser(self, parser_adder):
        # This is a bit of boilerplate, which allows you full control over the
        # type of argparse handling you want. The "parser_adder" argument is
        # the return value of an argparse.ArgumentParser.add_subparsers() call.
        parser = parser_adder.add_parser(self.name,
                                         help=self.help,
                                         description=self.description)

        # Add some example options using the standard argparse module API.
        # parser.add_argument('dir', help='directory')

        return parser # gets stored as self.parser

    def do_run(self, args, unknown_args):
        # This gets called when the user runs the command, e.g.:
        #
        #   $ west unit

        # From the flattened device tree in the build output, create
        # a .repl file for emulating the board in renode.
        # with open("boards/my_board.repl", "w") as repl_file:
        #     repl_file.write(dts2repl.generate(Namespace(filename="./build/zephyr/zephyr.dts")))

        subprocess.run(['west', 'twister', '-cnv', '--coverage', '--gcov-tool', 'gcovr', '--coverage-tool', 'gcovr', '--coverage-formats', 'txt', '--board-root', './app', '--platform', './app_nucleo_l476rg', '-T', 'app/tests/', '-O', 'build/twister'], check=True)
        subprocess.run(['gcovr', '-f', 'app', '-e', 'app/tests', '--txt', 'build/twister/coverage/coverage.txt', '--xml', 'build/twister/coverage/coverage.xml', '.'], check=True)
        subprocess.run(['cat', 'build/twister/coverage/coverage.txt'], check=True)