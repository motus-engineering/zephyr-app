'''emulate.py

West extension for device emulation in renode.'''

from textwrap import dedent            # just for nicer code indentation

from west.commands import WestCommand  # your extension must subclass this
from west import log                   # use this for user output

from os import path, chmod, listdir, environ

import stat
import subprocess
from fnmatch import fnmatch

from glob import glob
from pyrenode3.wrappers import Analyzer, Emulation, Monitor

class Emulate(WestCommand):

    def __init__(self):
        super().__init__(
            'emulate',  # gets stored as self.name
            'launches a renode emulation',  # self.help
            # self.description:
            dedent('''
            Renode emulation.

            This command will create a renode emulation and run the built firmware.
            '''))

    def do_add_parser(self, parser_adder):
        # This is a bit of boilerplate, which allows you full control over the
        # type of argparse handling you want. The "parser_adder" argument is
        # the return value of an argparse.ArgumentParser.add_subparsers() call.
        parser = parser_adder.add_parser(self.name,
                                         help=self.help,
                                         description=self.description)

        # # Add options using the standard argparse module API.
        parser.add_argument('action', help=(
            'test - setup and run robot framework tests, ' +
            'debug - load binaries and setup a gdb server, or ' + 
            'run - load binaries and run'))

        return parser # gets stored as self.parser

    def do_run(self, args, unknown_args):
        # This gets called when the user runs the command, e.g.:        
        #   $ west emulate <action>


        #Identify the target of the last build
        board = ''
        board_dir = ''
        with open('./build/CMakeCache.txt', 'r', encoding='utf-8') as f:
            for line in f:
                name, sep, var = line.partition("=")
                name = name.strip()
                if name == 'BOARD:STRING':
                    board = var.strip()
                elif name == 'BOARD_DIR:PATH':
                    board_dir = var.strip()

        if not board or not board_dir:
            log.inf('No valid build')
            return
        else:
            log.inf('Found board=' + board + ' and board_dir=' + board_dir)

        #Set up emulator
        e = Emulation()
        m = Monitor()
        board_mach = e.add_mach(board)
        board_mach.load_elf('./build/zephyr/zephyr.elf')

        #Look for renode support files for the board...
        support_files = path.join(board_dir, 'support')
        if path.exists(support_files):
            if glob(path.join(support_files, '*.resc')):
                log.inf('Found renode script in ' + str(support_files))
                board_resc = glob(path.join(support_files, '*.resc'))[0]
                board_mach.load_resc(board_resc)
            elif glob(path.join(support_files, '*.repl')):
                log.inf('No renode scripts found in ' + str(support_files) + '. Using platform description')
                board_repl = glob(path.join(support_files, '*.repl'))[0]
                board_mach.load_repl(board_repl)
            else:
                log.inf('Missing renode platform description (*.repl) in ' + str(support_files) + 
                        '. A .repl file can be generated from the flattened device tree for the built platform using \'dts2repl ./build/zephyr/zephyr.dts\'')
                ExecuteCommand('quit')
                return

        # Analyzer(stm32l072.sysbus.usart2).Show()
        e.StartAll()

        if path.exists(args.action) is False or args.action == 'run':
            log.inf("Running build on Renode machine...")
            #Start emulator and load/run .elf file
        elif args.action == 'test':
            log.inf("Running robot framework tests on Renode machine...")
            #Look for robot file
        elif args.action == 'debug':
            log.inf("Starting GDB server on Renode machine...")
            #Setup gdb server
        else:
            log.inf("Bad arg")

        log.inf('Done')
