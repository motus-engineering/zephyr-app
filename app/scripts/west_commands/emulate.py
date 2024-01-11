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

        parser.add_argument('-e', '--execution', help='<debug> start a debug server or <run> to run application (default)')
        parser.add_argument('-i', '--instances', help='Number board instances to emulate')

        return parser # gets stored as self.parser

    def do_run(self, args, unknown_args):
        # This gets called when the user runs the command, e.g.:        
        #   $ west emulate <action>

        root_dir = '/workspaces/'
        output_dir = root_dir + 'zephyr-app/build/zephyr/'

        log.inf('Preparing platform')

        # Generate platform description file (.repl) from flattened device tree
        with open(output_dir + 'platform.repl', "w") as repl_file:
            repl_file.write(dts2repl.generate(Namespace(filename=(output_dir + 'zephyr.dts'))))

        # Get assigned console port from flattened device tree
        console_node_name = ''
        board_dt = dtlib.DT(filename=(output_dir + 'zephyr.dts'))
        dt_chosen = board_dt.get_node('/chosen')
        if dt_chosen.props.get('zephyr,console'):
            console_node = dt_chosen.props.get('zephyr,console').to_path()
            console_node_name = console_node.name
            if console_node.labels:
                console_node_name = console_node.labels[0] #If we're using a label

        # Set up emulator
        e = Emulation()

        # If we're setting up a debug server, only emulate one device.
        machine_count = 1
        if args.instances and not args.execution == 'debug':
            machine_count = int(args.instances)
        
        log.inf('Generating ' + str(machine_count) + ' instances')
        for x in range(machine_count):
            board_mach_name = 'B' + str(x)
            # Create a board instance
            board_mach = e.add_mach(board_mach_name)
            
            # Load platform description
            board_mach.load_repl(output_dir + 'platform.repl')

            # If we're debugging, start GDB server. Clients can connect with gdb-multiarch.
            if args.execution == 'debug':
                board_mach.StartGdbServer(3333)

            # Load executable
            board_mach.load_elf(output_dir + 'zephyr.elf')

            # Show analyzer output from the emulated board
            if console_node_name:
                Analyzer(board_mach.sysbus.get_child(console_node_name)).Show()
                    
                # e.CreateUartPtyTerminal("console_term", "/tmp/" + console_node_name)
                # e.Connector.Connect(board_mach.sysbus.get_child(console_node_name).internal, e.externals.console_term)
                    
                # e.CreateServerSocketTerminal(3456, "console_server")
                # e.Connector.Connect(board_mach.sysbus.get_child(console_node_name).internal, e.externals.console_server)
        
            board_mach.EnableProfiler(output_dir + '/' + board_mach_name + '_Profiler.log')

        log.inf('Starting emulation') 

        # Don't start execution if we're debugging. The debugger client can control this
        if args.execution == 'debug':
            log.inf('Use the \'Renode Debug\' launch target to start debugging on the emulated machine') 
        else: 
            # Start all boards and let them run indefinitely
            e.StartAll()

        log.inf('Running emulator. Find run logs for each emulated machine in ' + output_dir +
                '. Logs cannot be parsed unless emulation is cleanly terminated ' + 
                '(i.e. don\'t interrupt this session with Ctrl+C. Press ENTER to stop.)')

        # Stop emulation on keyboard input 
        input()
        log.inf('Stopping emulation')

        # Explicit shutdown to make sure all active logs are terminated properly
        e.Dispose()

        log.inf('Done')

