'''st-clt.py

West extension for installing the ST CLT package.'''

from textwrap import dedent            # just for nicer code indentation

from west.commands import WestCommand  # your extension must subclass this
from west import log                   # use this for user output

from os import path, chmod, listdir
import stat
import subprocess
from fnmatch import fnmatch

class STCLT(WestCommand):

    def __init__(self):
        super().__init__(
            'st-clt',  # gets stored as self.name
            'installs the ST CLT package',  # self.help
            # self.description:
            dedent('''
            STM32CubeCLT Installation.

            This command will install the ST CLT package from the provided path.
            The STM32CubeCLT can be downloaded from https://www.st.com/en/development-tools/stm32cubeclt.html
            '''))

    def do_add_parser(self, parser_adder):
        # This is a bit of boilerplate, which allows you full control over the
        # type of argparse handling you want. The "parser_adder" argument is
        # the return value of an argparse.ArgumentParser.add_subparsers() call.
        parser = parser_adder.add_parser(self.name,
                                         help=self.help,
                                         description=self.description)

        # Add options using the standard argparse module API.
        parser.add_argument('clt_path', help='path of the ST CLT zip file')

        return parser # gets stored as self.parser

    def do_run(self, args, unknown_args):
        # This gets called when the user runs the command, e.g.:
        #
        #   $ west st-clt <file>
        if path.exists(args.clt_path) is False:
            log.inf('Invalid CLT zip file path provided.')
        else:
            # Obtain the filename of installer the zip
            info = subprocess.run(['unzip', '-Z1', args.clt_path],
                                  capture_output=True,
                                  check=True,
                                  encoding='ascii')
            clt_sh = path.join(path.expanduser('~/st/'), info.stdout.strip())

            # unzip the installer and make it executable
            subprocess.run(['unzip', '-od', path.expanduser('~/st/'), args.clt_path], check=True)
            chmod(clt_sh, stat.S_IRUSR | stat.S_IXUSR)

            # extract the contents of the installer to avoid manual prompts
            subprocess.run([clt_sh, '--noexec', '--keep', '--target', path.expanduser('~/st/')],
                           check=True)

            # remove any previous installations of the CLT
            for file in listdir(path.expanduser('/opt/st/')):
                if fnmatch(file, 'stm32cubeclt*'):
                    log.inf(f'Found previous clt installation: {file}. Removing it...')
                    subprocess.run(['sudo', 'rm', '-r', path.join(path.expanduser('/opt/st/'), file)], check=True)   

            # install the STLINK GDB server, programming and other ST utilities
            for file in listdir(path.expanduser('~/st/')):
                if fnmatch(file, 'st-stlink-server*.deb') or fnmatch(file, 'st-stm32cubeclt*.deb'):
                    log.inf(f'Installing: {file}')
                    subprocess.run(['sudo', 'dpkg-deb', '-x', path.join(path.expanduser('~/st/'), file), '/'], check=True)

            # clean up
            log.inf('Cleaning up files.')
            subprocess.run(['sudo', 'rm', '-r', path.expanduser('~/st/')], check=True)

            # remove the version string from the path           
            for file in listdir(path.expanduser('/opt/st/')):
                if fnmatch(file, 'stm32cubeclt*'):
                    log.inf(f'Using clt installation: {file}')
                    subprocess.run(['sudo', 'mv', path.join(path.expanduser('/opt/st/'), file), path.expanduser('/opt/st/stm32cubeclt')], check=True)    

            log.inf('Done')
