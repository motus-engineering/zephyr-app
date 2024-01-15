'''emulate.py

West extension for device emulation in renode.'''

from textwrap import dedent            # just for nicer code indentation

from west.commands import WestCommand  # your extension must subclass this
from west import log                   # use this for user output

from pyrenode3.wrappers import Analyzer, Emulation
from devicetree import dtlib
from dts2repl import dts2repl # Create repl files for renode from device tree files
from argparse import Namespace

import glob

root_dir = '/workspaces/zephyr-app/'
build_dir = root_dir + 'build/'
bin_dir = build_dir + 'zephyr/'

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
    
    def _load_platform(self):
        #Parse the zephyr CMakeCache.txt output to find the platform name and path
        #CMakeCache.txt has line entries of the form <PROPERTY NAME>:<PROPERTY TYPE>=<PROPERTY VALUE>
        platform_name = ''
        platform_path = ''
        platform_file = ''
        with open(build_dir + 'CMakeCache.txt', 'r') as cmake_cache_file:
            cmake_cache = cmake_cache_file.read()
            cmake_cache = cmake_cache.splitlines()
            for line in cmake_cache:
                if line.startswith('BOARD:STRING'):
                    platform_name = line.split('=', 1)[1]
                if line.startswith('BOARD_DIR:PATH'):
                    platform_path = line.split('=', 1)[1]
                if platform_name and platform_path:
                    log.inf('Found ' + platform_name + ' from ' + platform_path)
                    break #Found both. Stop looking

        #Look for a platform description in the board's support files
        #If none exists, we can generate a basic one from the flattened device tree
        platform_files = glob.glob(platform_path + '/support/*.repl')
        if platform_files:
            platform_file = platform_files[0]
            log.inf('Found ' + platform_file)
        else:
            platform_file = bin_dir + 'platform.repl'
            with open(platform_file, 'w') as repl_file:
                repl_file.write(dts2repl.generate(Namespace(filename=(bin_dir + 'zephyr.dts'))))
                log.inf('Generated ' + platform_file + ' from device tree')

        return platform_name, platform_file
        
    def do_run(self, args, unknown_args):
        # This gets called when the user runs the command, e.g.:        
        #   $ west emulate <action>

        log.inf('Preparing platform')
        platform_name, platform_file = self._load_platform()
        
        # Get assigned console port from flattened device tree
        console_node_name = ''
        board_dt = dtlib.DT(filename=(bin_dir + 'zephyr.dts'))
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
            board_mach_name = platform_name + '_' + str(x)
            # Create a board instance
            board_mach = e.add_mach(board_mach_name)
            
            # Load platform description
            board_mach.load_repl(platform_file)

            # If we're debugging, start GDB server. Clients can connect with gdb-multiarch.
            if args.execution == 'debug':
                board_mach.StartGdbServer(3333)

            # Load executable
            board_mach.load_elf(bin_dir + 'zephyr.elf')

            # Show analyzer output from the emulated board
            if console_node_name:
                Analyzer(board_mach.sysbus.get_child(console_node_name)).Show()
                    
                # e.CreateUartPtyTerminal('console_term', '/tmp/' + console_node_name)
                # e.Connector.Connect(board_mach.sysbus.get_child(console_node_name).internal, e.externals.console_term)
                    
                # e.CreateServerSocketTerminal(3456, 'console_server')
                # e.Connector.Connect(board_mach.sysbus.get_child(console_node_name).internal, e.externals.console_server)
        
            board_mach.EnableProfiler(bin_dir + '/' + board_mach_name + '_Profiler.log')

        log.inf('Starting emulation') 

        # Don't start execution if we're debugging. The debugger client can control this
        if args.execution == 'debug':
            log.inf('Use the \'Renode Debug\' launch target to start debugging on the emulated machine') 
        else: 
            # Start all boards and let them run indefinitely
            e.StartAll()

        log.inf('Running emulator. Find run logs for each emulated machine in ' + bin_dir +
                '. Logs cannot be parsed unless emulation is cleanly terminated ' + 
                '(i.e. don\'t interrupt this session with Ctrl+C. Press ENTER to stop.)')

        # Stop emulation on keyboard input 
        input()
        log.inf('Stopping emulation')

        # Explicit shutdown to make sure all active logs are terminated properly
        e.Dispose()

        log.inf('Done')

