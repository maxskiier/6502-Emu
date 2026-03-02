import configparser
from pathlib import Path

repo_root = Path(__file__).parent.parent
input_file = repo_root / "csv" / "opcodes.csv"
output_ini = repo_root / "opcodes.ini"

config = configparser.ConfigParser()

def extract_last_number(s):
    for token in reversed(s.split()):
        if token.isdigit() or token == '*':
            return token
    return s.strip()  # fallback

with open(input_file) as f:
    lines = f.readlines()

for line in lines:
    line = line.strip()
    if not line:
        continue

    # remove comments at the end
    line = line.split('#', 1)[0].strip()

    # split line into columns (take at least 5)
    parts = line.split(None, 4)
    if len(parts) < 5:
        continue

    opcode_hex = parts[0].strip()
    mnemonic = parts[1].strip()
    addrmode = parts[2].strip()
    bytes_count = extract_last_number(parts[4])
    cycles = extract_last_number(parts[3])

    unofficial = '1' if cycles == '*' else '0'

    config[opcode_hex] = {
        "name": mnemonic,
        "mode": addrmode,
        "bytes": bytes_count,
        "cycles": cycles,
        "unofficial": unofficial
    }

with open(output_ini, "w") as f:
    config.write(f)

print(f"INI file generated: {output_ini}")
