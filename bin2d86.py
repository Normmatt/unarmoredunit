import sys
import os

def bin_to_asm(input_file, output_file, name):
    with open(input_file, 'rb') as bin_file, open(output_file, 'w') as asm_file:
        byte = bin_file.read(1)
        asm_file.write(f"{name}	DSEG	'FAR_DATA' PARA\n\n");
        asm_file.write(f"	EVEN\n");
        asm_file.write(f"{name}_char_adr_::\n");
        while byte:
            asm_file.write(f"\tDB 0x{byte.hex().upper()}\n")
            byte = bin_file.read(1)
        asm_file.write(f"\n\n\tEND\n");

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python bin2d86.py input.bin")
        sys.exit(1)

    input_file = sys.argv[1]
    name = os.path.splitext(input_file)[0]
    output_file = name + ".d86"
    bin_to_asm(input_file, output_file, name)
    print(f"Output saved to {output_file}")
