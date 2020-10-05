import os
import subprocess
import shutil
from enum import Enum
import argparse

dms = True

def do_module_select():
	global dms
	dms = False




parser = argparse.ArgumentParser(description='Builds the DFK')
parser.add_argument('--all', dest='all', action='store_const', const=do_module_select, default='', help="builds all")

args = parser.parse_args()

if args.all != '':
	args.all()


def buildFail(msg=""):
	print("\n{}\n\nBuild Failed!".format(msg))
	exit()


CWD=os.getcwd()
ENVS = "CC=clang++ CFLAGS=\"-std=c++11 -target x86_64-unknown-elf -O3 -ffreestanding -fno-rtti -fno-exceptions -nostdlib -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -Wall\" LD=ld.lld KINCLUDE=" + CWD + "/include/ STDLIBINC="+ CWD + "/cstdlib/include STDLIBOBJ=$(PWD)/cstdlib/src/cstdlib.o"

MAX_BOOTSTRAP_SIZE = 0x300000 
MAX_KERNEL_SIZE =    0x400000

KERNEL_LOCATION = 0x400000
MODULE_LOCATION = 0x800000

def check_command(cmd):
	make_process = subprocess.Popen(cmd + " --version;", shell=True, stderr=subprocess.DEVNULL, stdout=subprocess.DEVNULL)
	if make_process.wait() != 0:
		print("{} not in path!\n".format(cmd))
		exit()

def which_check(cmd):
	make_process = subprocess.Popen("which -s " + cmd, shell=True, stderr=subprocess.DEVNULL, stdout=subprocess.DEVNULL)
	if make_process.wait() != 0:
		print("{} not in path!\n".format(cmd))
		exit()

def make(target, dir, doEnv=True):
	cmd_str = ""
	if doEnv:
		cmd_str = "make -C {} {} -e {}".format(dir, target, ENVS)
	else:
		cmd_str = "make -C {} {}".format(dir, target)

	make_process = subprocess.Popen(cmd_str, shell=True)
	if make_process.wait() != 0:
		buildFail() #make should print its own errors

def cmd_exec(cmd):
	make_process = subprocess.Popen(cmd, shell=True)
	if make_process.wait() != 0:
		buildFail() #make should print its own errors






check_command("clang++")
check_command("ld.lld")
check_command("nasm")
check_command("make")
which_check("cat")
which_check("dd")
which_check("mv")










class Module(Enum):
	vga = 1
	ramdisk = 2
	stupidfs = 3

chosen = list()

def module_select():
	global chosen

	the_input = input('clean the build system?\n[Y/n]:')
	if len(the_input) == 0 or the_input[0] != 'n':
		make("clean", ".")
		print("\n\n\n");	

	while True:
		print("Select Modules:")
		for item in Module:
			print('{}: {}'.format(item.value, item.name))
		print("'d' for done | 'c' for clear")
		choice = input("$")
		
		if len(choice) == 0:
			continue

		if choice[0] == 'd':
			print(chosen)
			choice = input("Confirm [y/N]:")
			if len(choice) == 0 or choice[0] != 'y':
				continue
			else:
				break

		if choice[0] == 'c':
			chosen.clear()

		c_val = 0;
		
		try:
			c_val = int(choice)
		except Exception as e:
			continue

		if c_val not in chosen:
			chosen.append(c_val)

	try:
		os.mkdir(build)
	except Exception as e:
			i = 6

if dms == True:
	module_select()
else:
	make("clean", ".")
	for x in Module:
		chosen.append(x.value)
		
		

make("vga", "modules/") ##temporary
make("kernel", ".")


for it in chosen:
	the_name = Module(it).name
	make(the_name, "modules/")
	os.replace("modules/{}/{}.ko".format(the_name, the_name),"build/" + the_name + ".ko")



make("bootstrap", ".")



os.replace("src/kernel", "build/kernel")
os.replace("src/bootstrap/bootstrap", "build/bootstrap")
shutil.copyfile("src/bootstrap/mbr.sys", "build/mbr.sys")

cmd_exec("dd if=/dev/zero of=build/disk.img count=128 bs=0x100000")
cmd_exec("dd if=build/mbr.sys of=build/disk.img conv=notrunc")
cmd_exec("dd if=build/bootstrap of=build/disk.img bs=512 seek=16 conv=notrunc")

#kernel is at 4M mark
cmd_exec("dd if=build/kernel of=build/disk.img bs=1 oseek=0x400000 conv=notrunc")

DISK_OFFSET=0x800000

module_count = len(chosen)

#header looks like this
#struct header{
#uint64_t module_count;
#void** module_ptr_array;	
#}
# So we could have 3 modules, with each pointing to their offsets

SECTOR_SIZE = 512

header_size = (module_count + 1) * 8 
if SECTOR_SIZE > 512:
	print("The build system doesn't support the amount of modules you have")
	buildFail()

DISK_OFFSET += SECTOR_SIZE


size_list = list()

for it in chosen:
	size_list.append(DISK_OFFSET)
	the_name = Module(it).name
	cmd_exec("dd if=build/{}.ko of=build/disk.img bs=1 oseek={} conv=notrunc".format(the_name, DISK_OFFSET))
	next_offset = os.path.getsize("build/{}.ko".format(the_name))
	next_offset += SECTOR_SIZE - (next_offset % SECTOR_SIZE)
	DISK_OFFSET += next_offset

size_list.append(DISK_OFFSET);

header_bytes = bytes()
header_bytes += module_count.to_bytes(8, byteorder='little')
for it in size_list:
	header_bytes += it.to_bytes(8, byteorder='little')

header_file = open("build/module_header.bin", "wb")
header_file.write(header_bytes)
header_file.close()

cmd_exec("dd if=build/module_header.bin of=build/disk.img bs=1 oseek=0x800000 conv=notrunc")

if os.path.getsize("build/bootstrap") >= MAX_BOOTSTRAP_SIZE:
	buildFail("bootstrap binary is too big!")

if os.path.getsize("build/kernel") >= MAX_KERNEL_SIZE:
	buildFail("kernel binary is too big!")

print ('\n[{}]'.format(', '.join(hex(x) for x in size_list)))
print("\n\nDONE!")



#[0x800200, 0x802a00, 0x804c00]














