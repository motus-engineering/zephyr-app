'''emulate.py

West extension for device emulation in renode.'''

from textwrap import dedent            # just for nicer code indentation

from west.commands import WestCommand  # your extension must subclass this
from west import log                   # use this for user output

# from os import path, chmod, listdir, environ
import os

import stat
import subprocess
from fnmatch import fnmatch

from pyrenode3.wrappers import Analyzer, Emulation, Monitor
from devicetree import dtlib
from dts2repl import dts2repl # Create repl files for renode from device tree files
from argparse import Namespace

import time

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

        return parser # gets stored as self.parser

    def do_run(self, args, unknown_args):
        # This gets called when the user runs the command, e.g.:        
        #   $ west emulate <action>

        root_dir = '/workspaces/'
        output_dir = root_dir + 'zephyr-app/build/zephyr/'
       
        #Set up emulator
        e = Emulation()
        board_mach = e.add_mach("my board")
        board_mach.load_elf(output_dir + 'zephyr.elf')

        #Generate and load .repl file for board from built device tree
        with open(output_dir + 'platform.repl', "w") as repl_file:
            repl_file.write(dts2repl.generate(Namespace(filename=(output_dir + 'zephyr.dts'))))
        board_mach.load_repl(output_dir + 'platform.repl')

        # Get console port from built device tree and show analyzer output
        board_dt = dtlib.DT(filename=(output_dir + 'zephyr.dts'))
        dt_chosen = board_dt.get_node('/chosen')
        if dt_chosen.props.get('zephyr,console'):
            console_node = dt_chosen.props.get('zephyr,console').to_path()
            console_node_name = console_node.name
            if console_node.labels:
                console_node_name = console_node.labels[0] #If we're using a label

            Analyzer(board_mach.sysbus.get_child(console_node_name)).Show()
                
            # e.CreateUartPtyTerminal("console_term", "/tmp/" + console_node_name)
            # e.Connector.Connect(board_mach.sysbus.get_child(console_node_name).internal, e.externals.console_term)
                
            # e.CreateServerSocketTerminal(3456, "console_server")
            # e.Connector.Connect(board_mach.sysbus.get_child(console_node_name).internal, e.externals.console_server)

        
        #Start emulation and let it run indefinitely
        e.StartAll()
        while 1:
            time.sleep(1)

